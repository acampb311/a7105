#include "a7105.h"
#include <cstdint>
#include "a7105_defs.h"
#include "esphome/core/log.h"

namespace esphome::a7105 {

static constexpr uint8_t BUS_READ = 0b01000000;
static constexpr uint8_t BUS_WRITE = 0b00000000;
static constexpr uint8_t CONTROL_REGISTER = 0b00000000;
static constexpr uint8_t STROBE = 0b10000000;

static const char *TAG = "a7105";

A7105Component::A7105Component() {
  memset(&this->state_, 0, sizeof(this->state_));

  this->state_.DATA_MODE = 1;
  this->state_.ARSSI = 1;
  this->state_.FIFO_END_POINTER = 0x03; // think this turns into a 4 byte payload (this val + 1)
  this->state_.FIFO_POINTER_MARGIN = 0x03;
  this->state_.CKO_OUTPUT_ENABLED = 1;
  this->state_.CKO_PIN_OUTPUT_MODE = CkoPinOutputModeType::FIFO_POINTER_FLAG;
  this->state_.GIO1_PIN_OUTPUT_ENABLED = 1;
  this->state_.GIO2_PIN_OUTPUT_ENABLED = 1;
  this->state_.GIO2_FUNCTION = Gpio2FunctionType::SDO;
  this->state_.CRYSTAL_OSCILLATOR_SELECT = 1;
  this->state_.SYS_CLOCK_DIV_SELECT = SystemClockDividerType::DIV_2;
  this->state_.DATA_RATE_DIVISION_SELECTION = 0x13;
  this->state_.PLL_I = 0x50;
  this->state_.PLL_CHANNEL_STEP = 0b1111;
  this->state_.CRYSTAL_FREQ_DOUBLER_SELECT = 1;
  this->state_.PLL_III = 0x4B;
  this->state_.PLL_V = 0x02;
  this->state_.FREQ_DEVIATION_POWER_SETTING = 0b110;
  this->state_.TX_MODULATION_ENABLED = 1;
  this->state_.FREQ_DEVIATION_SETTING = 0b1011;
  this->state_.PDV = 0b01;
  this->state_.PLL_TO_WPLL_DELAY = PllToWpllDelayType::MICRO_SEC_70;
  this->state_.WPLL_TO_TX_DELAY = WpllToTxDelayType::MICRO_SEC_60;
  this->state_.BPF_BANDWIDTH_SELECT = 1;
  this->state_.RXSM0 = 1;
  this->state_.RXSM1 = 1;
  this->state_.MANUAL_VGA_CALIBRATE = 1;
  this->state_.RSSI_THRESHOLD = 0x32;
  this->state_.RSSI_MEASUREMENT_MODE = 1;
  this->state_.RSSI_MEASUREMENT_SELECT = 1;
  this->state_.RSSI_MARGIN = RssiMarginType::TWENTY;
  this->state_.PREAMBLE_LENGTH = PreambleLengthType::BYTES_4;
  this->state_.ID_LENGTH = IdLengthType::BYTES_4;
  this->state_.CRC_SELECT = 1;
  this->state_.PREAMBLE_PATTERN_LENGTH = PreamblePatternLengthType::BITS_16;
  this->state_.ID_CODE_ERROR_TOLERANCE = IdCodeErrorToleranceType::BITS_1;
  this->state_.DEMODULATOR_DC_EST_AVG_MODE = 1;
  this->state_.VCO_TUNING_VOLTAGE_LOWER_THRESHOLD = VoltageLowerThresholdLevelType::V_0_4;
  this->state_.VCO_TUNING_VOLTAGE_UPPER_THRESHOLD = VoltageUpperThresholdLevelType::VDD_A_MINUS_1_3V;
  this->state_.TBG = 0b111;
  this->state_.PAC = 0b11;
  this->state_.SLF = 0b111;
  this->state_.DEMODULATOR_DC_EST_MODE = DemodulatorDcEstModeType::PREAMBLE_HOLD_MODE;
  this->state_.RX_DEM_TEST_II = 0x80;
  this->state_.CHARGE_PUMP_CURRENT_SETTING = ChargePumpCurrentType::MILLI_AMP_2_0;
  this->state_.XCP = 0b01;
  this->state_.NSDO = 1;
  this->state_.PRIC = 0b01;
  this->state_.PMPE = 1;
  this->state_.VCO_TEST_I = 0x18;
  this->state_.RX_GAIN_II = 0x80;
  this->state_.RX_GAIN_IV = 0x0A;
  this->state_.IFAT = 0b00000001;
  this->state_.RSCALE = 0x0F;
}

void A7105Component::setup() {

  this->spi_setup(); // Required to initialize this SPI device

  for (uint8_t i = 0; i <= static_cast<uint8_t>(Register::RSCALE); i++) {
    if (i == static_cast<uint8_t>(Register::FIFO_DATA) ||
        i == static_cast<uint8_t>(Register::ID_DATA) ||
        i == static_cast<uint8_t>(Register::IF_CALIBRATION_II)) {
      continue;
    }

    this->write_(static_cast<Register>(i));
  }

  this->write_(Mode::STANDBY);

  this->write_(Register::CALIBRATION_CONTROL, 0x01);
  this->read_(Register::CALIBRATION_CONTROL); // 0x42 0x00
  this->read_(Register::IF_CALIBRATION_I); // 0x62 0x00
  this->write_(Register::VCO_CURRENT_CALIBRATION, 0x13); // 0x24 0x13
  this->write_(Register::VCO_SINGLE_BAND_CALIBRATION_II, 0x3B); // 0x26 3B
  this->write_(Register::PLL_I, 0x00); // 0x0f 00
  this->write_(Register::CALIBRATION_CONTROL, 0x02); // 2 2
  this->read_(Register::CALIBRATION_CONTROL); // 0x42 0x00
  this->read_(Register::VCO_SINGLE_BAND_CALIBRATION_I); // 0x65 ?
  this->write_(Register::PLL_I, 0xA0); // 0x0f a0
  this->write_(Register::CALIBRATION_CONTROL, 0x02); // 2 2
  this->read_(Register::CALIBRATION_CONTROL); // 0x42 0x00
  this->read_(Register::VCO_SINGLE_BAND_CALIBRATION_I); // 0x65 ?

  this->write_(Mode::STANDBY);

}

void A7105Component::loop() {

}

void A7105Component::dump_config() {
  ESP_LOGCONFIG(TAG, "Empty SPI component");
}

void A7105Component::send_payload(std::initializer_list<uint8_t> id,
                                  std::initializer_list<uint8_t> data) {
  this->write_(Mode::STANDBY);
  this->write_(id);
  this->write_(Register::PLL_I, 0x4E); //channel
  this->write_(Strobe::FIFO_WRITE_PTR_RESET);
  this->write_(data);
  this->write_(Mode::TX);
}

void A7105Component::write_(std::initializer_list<uint8_t> list) {
  this->enable();
  this->write_array(list.begin(), list.size());
  this->disable();
}

void A7105Component::write_(Strobe cmd) {
  this->enable();
  this->write(static_cast<uint8_t>(cmd), 4);
  this->disable();
}

void A7105Component::write_(Mode mode) {
  this->enable();
  this->write(static_cast<uint8_t>(mode), 4);
  this->disable();
}

void A7105Component::write_(Register reg) {
  uint8_t index = static_cast<uint8_t>(reg);
  this->enable();
  this->write((index | BUS_WRITE) << 8 | this->state_.regs()[index], 16);
  this->disable();
}

void A7105Component::write_(Register reg, uint8_t value) {
  uint8_t index = static_cast<uint8_t>(reg);
  this->enable();
  this->write((index | BUS_WRITE) << 8 | value, 16);
  this->disable();
}

uint8_t A7105Component::read_(Register reg) {
  uint8_t index = static_cast<uint8_t>(reg);
  this->enable();
  this->write_byte(index | BUS_READ);
  auto current = this->transfer_byte(0);
  this->disable();

  return current;
}

} // namespace esphome::a7105
