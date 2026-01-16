#pragma once

#include <sys/types.h>
#include <cinttypes>
#include <cstdint>

namespace esphome::a7105 {

enum class Strobe : uint8_t {
  SLEEP                = 0b1000,
  IDLE                 = 0b1001,
  STANDBY              = 0b1010,
  PLL                  = 0b1011,
  RX                   = 0b1100,
  TX                   = 0b1101,
  FIFO_WRITE_PTR_RESET = 0b1110,
  FIFO_READ_PTR_RESET  = 0b1111,
};

enum class Mode : uint8_t {
  SLEEP = 0b1000,
  IDLE = 0b1001,
  STANDBY = 0b1010,
  PLL = 0b1011,
  RX = 0b1100,
  TX = 0b1101,
};

enum class Register : uint8_t {
  MODE = 0x00,
  MODE_CONTROL_I = 0x01,
  CALIBRATION_CONTROL = 0x02,
  FIFO_I = 0x03,
  FIFO_II = 0x04,
  FIFO_DATA = 0x05,
  ID_DATA = 0x06,
  RC_OSC_I = 0x07,
  RC_OSC_II = 0x08,
  RC_OSC_III = 0x09,
  CKO_PIN_CONTROL = 0x0A,
  GIO1_PIN_CONTROL_I = 0x0B,
  GIO1_PIN_CONTROL_II = 0x0C,
  CLOCK = 0x0D,
  DATA_RATE = 0x0E,
  PLL_I = 0x0F,
  PLL_II = 0x10,
  PLL_III = 0x11,
  PLL_IV = 0x12,
  PLL_V = 0x13,
  TX_I = 0x14,
  TX_II = 0x15,
  DELAY_I = 0x16,
  DELAY_II = 0x17,
  RX = 0x18,
  RX_GAIN_I = 0x19,
  RX_GAIN_II = 0x1A,
  RX_GAIN_III = 0x1B,
  RX_GAIN_IV = 0x1C,
  RSSI_THRESHOLD = 0x1D,
  ADC_CONTROL = 0x1E,
  CODE_I = 0x1F,
  CODE_II = 0x20,
  CODE_III = 0x21,
  IF_CALIBRATION_I = 0x22,
  IF_CALIBRATION_II = 0x23,
  VCO_CURRENT_CALIBRATION = 0x24,
  VCO_SINGLE_BAND_CALIBRATION_I = 0x25,
  VCO_SINGLE_BAND_CALIBRATION_II = 0x26,
  BATTERY_DETECT = 0x27,
  TX_TEST = 0x28,
  RX_DEM_TEST_I = 0x29,
  RX_DEM_TEST_II = 0x2A,
  CHARGE_PUMP_CURRENT = 0x2B,
  CYRSTAL_TEST = 0x2C,
  PLL_TEST = 0x2D,
  VCO_TEST_I = 0x2E,
  VCO_TEST_II = 0x2F,
  IFAT = 0x30,
  RSCALE = 0x31,
  FILTER_TEST = 0x32,
};

enum class RscClockType : uint8_t {
  FSYNC_DIV8 = 0b00,
  FSYNC_DIV16 = 0b01,
  FSYNC_DIV32 = 0b10,
  FSYNC_DIV64 = 0b11,
};

enum class CkoPinOutputModeType : uint8_t {
    DCK_IN_TX_RCK_IN_RX = 0b0000,
    // DCK_IN_TX_RCK_IN_RX = 0b0001,
    FIFO_POINTER_FLAG = 0b0010,
    // 0b0011 internal use only
    FSYNC = 0b0100,
    FSYNC_DIV2 = 0b0101,
    FSYNC_DIV4 = 0b0110,
    FSYNC_DIV8 = 0b0111,
    // 0b1xxx RESERVED
};

enum class Gpio1FunctionType : uint8_t {
  /// Wait until TX or RX finished
  WTR = 0b0000,
  /// (TX) end of access code / (RX) Frame Sync
  EOAC_OR_FSYNC = 0b0001,
  /// (TX) TX modulation enable / (RX) Carrier Detect
  TMEO_OR_CD = 0b0010,
  // Preamble Detect Output
  PMDO = 0b0011,
  // 0b0100 RESERVED
  // In phase demodulator input
  DMII = 0b0101,
  // 4 wires SPI data out
  SDO = 0b0110,
  // In/Out (Direct Mode)
  TRXD = 0b0111,
  RXD = 0b1000,
  TXD = 0b1001,
  // In phase demodulator external input
  EXDIO = 0b1010,
  // External FSYNC input in RX direct mode
  EXTERNAL_FSYNC_INPUT = 0b1011,
  // 0b11xx Inhibited.
};

enum class Gpio2FunctionType : uint8_t {
  /// Wait until TX or RX finished
  WTR = 0b0000,
  /// (TX) end of access code / (RX) Frame Sync
  EOAC_OR_FSYNC = 0b0001,
  /// (TX) TX modulation enable / (RX) Carrier Detect
  TMEO_OR_CD = 0b0010,
  // Preamble Detect Output
  PMDO = 0b0011,
  // 0b0100 RESERVED
  // Quadrature phase demodulator input (DMIQ)
  DMIQ = 0b0101,
  // 4 wires SPI data out
  SDO = 0b0110,
  // In/Out (Direct Mode)
  TRXD = 0b0111,
  RXD = 0b1000,
  TXD = 0b1001,
  // Quadrature phase demodulator external input
  EXDI1 = 0b1010,
  // External FSYNC input in RX direct mode
  EXTERNAL_FSYNC_INPUT = 0b1011,
  // 0b11xx Inhibited.
};

enum class SystemClockDividerType : uint8_t {
  NO_DIV = 0b00,
  DIV_2 = 0b01,
  // DIV_2 = 0b10
  DIV_4 = 0b11,
};

enum class MovingAverageType : uint8_t {
  NOT_AVERAGED = 0b00,
  TWO_BIT_AVERAGE = 0b01,
  FOUR_BIT_AVERAGE = 0b10,
  EIGHT_BIT_AVERAGE = 0b11,
};

enum class PllToWpllDelayType : uint8_t {
  MICRO_SEC_50 = 0b001,
  MICRO_SEC_70 = 0b010,
  MICRO_SEC_90 = 0b011,
  MICRO_SEC_110 = 0b100,
};

enum class WpllToTxDelayType : uint8_t {
  MICRO_SEC_20 = 0b00,
  MICRO_SEC_40 = 0b01,
  MICRO_SEC_60 = 0b10,
  MICRO_SEC_80 = 0b11,
};

enum class RssiMeasurementDelayType : uint8_t {
  MICRO_SEC_10 = 0b000,
  MICRO_SEC_20 = 0b001,
  MICRO_SEC_30 = 0b010,
  MICRO_SEC_40 = 0b011,
  MICRO_SEC_50 = 0b100,
  MICRO_SEC_60 = 0b101,
  MICRO_SEC_70 = 0b110,
  MICRO_SEC_80 = 0b111,
};

enum class AgcSettlingDelayType : uint8_t {
  MICRO_SEC_10 = 0b00,
  MICRO_SEC_20 = 0b01,
  MICRO_SEC_30 = 0b10,
  MICRO_SEC_40 = 0b11,
};

enum class XtalSettlingDelayType : uint8_t {
  MICRO_SEC_200 = 0b000,
  MICRO_SEC_400 = 0b001,
  MICRO_SEC_600 = 0b010,
  MICRO_SEC_800 = 0b011,
  MILLI_SEC_1_0 = 0b100,
  MILLI_SEC_1_5 = 0b101,
  MILLI_SEC_2_0 = 0b110,
  MILLI_SEC_2_5 = 0b111,
};

enum class LnaGainType : uint8_t {
  DB_24 = 0b000,
  DB_18 = 0b001,
  DB_12 = 0b010,
  DB_6 = 0b011,
};

enum class MixerGainType : uint8_t {
  DB_24 = 0b00,
  DB_18 = 0b01,
  DB_12 = 0b10,
  DB_6 = 0b11,
};

enum class RssiMarginType : uint8_t {
  FIVE = 0b00,
  TEN = 0b01,
  FIFTEEN = 0b10,
  TWENTY = 0b11,
};

enum class PreambleLengthType : uint8_t {
  BYTES_1 = 0b00,
  BYTES_2 = 0b01,
  BYTES_3 = 0b10,
  BYTES_4 = 0b11,
};

enum class IdLengthType : uint8_t {
  BYTES_2 = 0b0,
  BYTES_4 = 0b1,
};

enum class PreamblePatternLengthType : uint8_t {
  BITS_0 = 0b00,
  BITS_4 = 0b01,
  BITS_8 = 0b10,
  BITS_16 = 0b11,
};

enum class IdCodeErrorToleranceType : uint8_t {
  BITS_0 = 0b00,
  BITS_1 = 0b01,
  BITS_2 = 0b10,
  BITS_3 = 0b11,
};

enum class DigitalVcoTuningVoltageType : uint8_t {
  VT_VTL_VTH = 0b00,
  VTL_VT_VTH = 0b01,
  NOT_USED   = 0b10,
  VTL_VTH_VT = 0b11,
};

enum class VoltageUpperThresholdLevelType : uint8_t {
  VDD_A_MINUS_0_6V = 0b000, // VDD_A - 0.6V
  VDD_A_MINUS_0_7V = 0b001,
  VDD_A_MINUS_0_8V = 0b010,
  VDD_A_MINUS_0_9V = 0b011,
  VDD_A_MINUS_1_0V = 0b100,
  VDD_A_MINUS_1_1V = 0b101,
  VDD_A_MINUS_1_2V = 0b110,
  VDD_A_MINUS_1_3V = 0b111,
};

enum class VoltageLowerThresholdLevelType : uint8_t {
  V_0_1 = 0b000, // 0.1 Volts
  V_0_2 = 0b001,
  V_0_3 = 0b010,
  V_0_4 = 0b011,
  V_0_5 = 0b100,
  V_0_6 = 0b101,
  V_0_7 = 0b110,
  V_0_8 = 0b111,
};

enum class ChargePumpCurrentType : uint8_t {
  MILLI_AMP_0_5 = 0b00, // 0.5mA
  MILLI_AMP_1_0 = 0b01,
  MILLI_AMP_1_5 = 0b10,
  MILLI_AMP_2_0 = 0b11,
};

enum class DemodulatorDcEstModeType : uint8_t {
  FIX_MODE = 0b00,
  PREAMBLE_HOLD_MODE = 0b01,
  AVG_AND_HOLD_MODE = 0b10,
  PAYLOAD_AVG_MODE = 0b11,
};

enum class VoltageSettingNonSleepType : uint8_t {
  V_2_1 = 0b00,
  V_2_0 = 0b01,
  V_1_9 = 0b10,
  V_1_8 = 0b11,
};

enum class BatteryVoltageDetectThresholdType : uint8_t {
  V_2_0 = 0b000, // 0.1 Volts
  V_2_1 = 0b001,
  V_2_2 = 0b010,
  V_2_3 = 0b011,
  V_2_4 = 0b100,
  V_2_5 = 0b101,
  V_2_6 = 0b110,
  V_2_7 = 0b111,
};

struct __attribute__((packed)) A7105State {
  // Byte array accessors for bulk SPI transfers
  uint8_t *regs() { return reinterpret_cast<uint8_t *>(this); }
  const uint8_t *regs() const { return reinterpret_cast<const uint8_t *>(this); }

  // 0x00
  union {
    uint8_t MODE;
    struct {
      // RX/TX state: Serviceable if TRER=1 (TRX is enabled)
      uint8_t TRX_STATUS : 1;
      // TRX is enabled
      uint8_t TRX_ENABLED : 1;
      // PLL is enabled
      uint8_t PLL_ENABLED : 1;
      // Crystal oscillator is enabled
      uint8_t INTERNAL_CRYSTAL_ENABLED : 1;
      // RF chip is enabled
      uint8_t RF_ENABLED : 1;
      // CRCF is read only, it is updated internally while receiving every packet.
      uint8_t CRC_PASS : 1;
      // FEC is read only, it is updated internally while receiving every packet.
      uint8_t FEC_PASS : 1;
      // Undefined bit
      uint8_t : 1;
    };
  };
  // 0x01
  union {
    uint8_t MODE_CONTROL_I;
    struct {
      // ADC measurement enable (Auto clear when done)
      uint8_t ADC_MEASUREMENT_ENABLED : 1;
      // Direct/FIFO mode select
      uint8_t DATA_MODE : 1;
      // FMT: Reserved for internal usage only. Shall be set to [0].
      uint8_t : 1;
      // WWSE: Reserved for internal usage only. Shall be set to [0].
      uint8_t : 1;
      // READ - DFCD (Data filter by CD): The received packet will be filtered out if CD is inactive.
      // WRITE - CD: Carrier detector signal.
      uint8_t CD : 1;
      // RF LO frequency will auto offset one IF frequency while entering RX mode.
      uint8_t AUTO_IF : 1;
      // Auto RSSI measurement while entering RX mode
      uint8_t ARSSI : 1;
      // Direct mode data pin control: In Direct mode, If DDPC=1, MCU delivers / receives raw data of packet via SDIO pin instead of GIO1 or GIO2 pin.
      uint8_t DDPC : 1;
    };
  };
  // 0x02
  union {
    uint8_t CALIBRATION_CONTROL;
    struct {
      // Filter Bank calibration enable (Auto clear when done).
      uint8_t FILTER_BANK_CALIBRATION_ENABLED : 1;
      // VCO Bank calibration enable (Auto clear when done).
      uint8_t VCO_BANK_CALIBRATION_ENABLED : 1;
      // VCO Current calibration enable (Auto clear when done).
      uint8_t VCO_CURRENT_CALIBRATION_ENABLED : 1;
      // Undefined bits
      uint8_t : 5;
    };
  };
  // 0x03
  union {
    uint8_t FIFO_I;
    struct {
      // FIFO End Pointer for TX FIFO and Rx FIFO
      uint8_t FIFO_END_POINTER : 8;
    };
  };
  // 0x04
  union {
    uint8_t FIFO_II;
    struct {
      // Used for Segment FIFO.
      uint8_t PACKET_SEGMENT_ADDRESS : 6;
      // FIFO Pointer Margin
      uint8_t FIFO_POINTER_MARGIN : 2;
    };
  };
  // 0x05
  uint8_t FIFO_DATA;
  // 0x06
  uint8_t ID_DATA;
  // 0x07
  const uint8_t RC_OSC_I = 0b00000000; // reserved for internal usage only
  // 0x08
  const uint8_t RC_OSC_II = 0b00000000; // reserved for internal usage only
  // 0x09
  union {
    uint8_t RC_OSC_III;
    struct {
      // TWWS_E: Enable TWWS function. Reserved for internal usage only.
      uint8_t : 1;
      // TSEL: Timer select for TWWS function. Reserved for internal usage only.
      uint8_t : 1;
      // RCOSC_E: RC-oscillator enable. Reserved for internal usage only
      uint8_t : 1;
      // Undefined bits
      uint8_t : 3;
      // BBCKS: Clock select for internal digital block Recommend BBCKS=[00]
      RscClockType CLOCK_SELECT : 2;
    };
  };
  // 0x0A
  union {
    uint8_t CKO_PIN_CONTROL;
    struct {
      // SCKI: SPI clock input invert.
      uint8_t CKO_INVERT_SPI_CLK_INPUT : 1;
      // CKOE: CKO pin Output Enable.
      uint8_t CKO_OUTPUT_ENABLED : 1;
      // CKOI: CKO pin output signal invert.
      uint8_t CKO_INVERT_OUTPUT : 1;
      // CKOS: CKO pin output select.
      CkoPinOutputModeType CKO_PIN_OUTPUT_MODE : 4;
      // ECKOE: External Clock Output Enable for CKOS [3:0]= [0100] ~ [0111].
      uint8_t ECKOE : 1;
    };
  };
  // 0x0B
  union {
    uint8_t GIO1_PIN_CONTROL_I;
    struct {
      // GIO1OE: GIO1pin output enable.
      uint8_t GIO1_PIN_OUTPUT_ENABLED : 1;
      // GIO1I: GIO1 pin output signal invert.
      uint8_t GIO1_INVERT_OUTPUT : 1;
      // GIO1S [3:0]: GIO1 pin function select.
      Gpio1FunctionType GIO1_FUNCTION : 4;
      // Undefined bits
      uint8_t : 2;
    };
  };
  // 0x0C
  union {
    uint8_t GIO2_PIN_CONTROL_II;
    struct {
      // GIO2OE: GIO2 pin Output Enable
      uint8_t GIO2_PIN_OUTPUT_ENABLED : 1;
      // GIO2I: GIO2 pin output signal invert.
      uint8_t GIO2_INVERT_OUTPUT : 1;
      // GIO2S [3:0]: GIO2 pin function select.
      Gpio2FunctionType GIO2_FUNCTION : 4;
      // Undefined bits
      uint8_t : 2;
    };
  };
  // 0x0D
  union {
    uint8_t CLOCK;
    struct {
      // XS: Crystal oscillator select. Recommend XS=[1]
      uint8_t CRYSTAL_OSCILLATOR_SELECT : 1;
      // CGS: Clock generator enable. Recommend CGS=[0]
      uint8_t CLOCK_GENERATOR_ENABLE : 1;
      // CSC [1:0]: system clock FSYCK divider select.
      SystemClockDividerType SYS_CLOCK_DIV_SELECT : 2;
      // GRC [3:0]: Clock generation reference counter.
      uint8_t CLOCK_GEN_REF_COUNTER: 4;
    };
  };
  // 0x0E
  // SDR [7:0]: Data rate division selection.
  // Data rate = FSYCK / 32 / (SDR [7:0]+1).
  uint8_t DATA_RATE_DIVISION_SELECTION;
  // 0x0F
  // CHN [7:0]: LO channel number select.
  uint8_t PLL_I;
  // 0x10
  union {
    uint8_t PLL_II;
    struct {
      uint8_t IP8 : 1;
      // CHR [3:0]: PLL channel step setting.
      uint8_t PLL_CHANNEL_STEP : 4;
      // RRC [1:0]: RF PLL reference counter setting.
      uint8_t RF_PLL_REF_COUNTER : 2;
      // DBL: Crystal frequency doubler selection. Recommend DBL=[1].
      // [0]: Disable. FXREF = FXTAL. [1]:Enable. FXREF =2 * FXTAL
      uint8_t CRYSTAL_FREQ_DOUBLER_SELECT : 1;
    };
  };
  // 0x11
  // LO FREQUENCY integer part
  uint8_t PLL_III;
  // 0x12
  // LO FREQUENCY fractional part
  uint8_t PLL_IV;
  // 0x13
  // LO FREQUENCY fractional part cont.
  uint8_t PLL_V;
  // 0x14
  union {
    uint8_t TX_I;
    struct {
      // FDP [2:0]: Frequency deviation power setting. Refer to control register (15h). Recommend FDP= [110].
      uint8_t FREQ_DEVIATION_POWER_SETTING : 3;
      // FS: Filter select. Recommend FS= [0]
      uint8_t FILTER_SELECT : 1;
      // TME: TX modulation enable
      uint8_t TX_MODULATION_ENABLED : 1;
      // TXDI: TX data invert. Recommend TXDI = [0].
      uint8_t TX_DATA_INVERT : 1;
      // TXSM [1:0]:Moving average for non-filter select. Recommend TXSM= [00]
      MovingAverageType TX_MOVING_AVERAGE: 2;
    };
  };
  // 0x15
  union {
    uint8_t TX_II;
    struct {
      // FD [4:0]: Frequency deviation setting.
      uint8_t FREQ_DEVIATION_SETTING : 5;
      // PDV [1:0]: Reserved for internal usage only. Shall be set to [01].
      uint8_t PDV : 2;
      // Undefined bit
      uint8_t : 1;
    };
  };
  // 0x16
  union {
    uint8_t DELAY_I;
    struct {
      // PDL [2:0]: Delay for TX settling from PLL to WPLL.
      PllToWpllDelayType PLL_TO_WPLL_DELAY : 3;
      // TDL [1:0]: Delay for TX settling from WPLL to TX.
      WpllToTxDelayType WPLL_TO_TX_DELAY : 2;
      // DPR [2:0]: Delay scale. Recommend DPR= [000].
      uint8_t DELAY_SCALE : 3;
    };
  };
  // 0x17
  union {
    uint8_t DELAY_II;
    struct {
      // RS_DLY [2:0]: RSSI measurement delay (10us ~ 80us). Recommend RS_DLY= [000].
      RssiMeasurementDelayType RSSI_MEASUREMENT_DELAY : 3;
      // AGC_D [1:0]: AGC delay settling Recommend AGC_D[1:0]= [00].
      AgcSettlingDelayType AGC_SETTLING_DELAY : 2;
      // WSEL [2:0]: XTAL settling delay setting (200us ~ 2.5ms). Recommend WSEL= [010].
      XtalSettlingDelayType XTAL_SETTLING_DELAY : 3;
    };
  };
  // 0x18
  union {
    uint8_t RX;
    struct {
      // ULS: RX Up/Low side band select.
      uint8_t LOW_SIDE_BAND_SELECT : 1;
      // BWS: BPF bandwidth select. Recommend BWS= [1].
      // [0]: 250KHz. [1]: 500KHz.
      uint8_t BPF_BANDWIDTH_SELECT : 1;
      // DMG: Reserved for internal usage only. Shall be set to [0].
      uint8_t DMG : 1;
      // RXDI: RX data output invert. Recommend RXDI= [0].
      uint8_t RX_DATA_INVERT : 1;
      // FC: Frequency compensation select.
      uint8_t FREQUENCY_COMPENSATION_SELECT : 1;
      // RXSM0: Reserved for internal usage only. Shall be set to [1].
      uint8_t RXSM0 : 1;
      // RXSM1: Reserved for internal usage only. Shall be set to [1].
      uint8_t RXSM1 : 1;
      // Undefined bit
      uint8_t : 1;
    };
  };
  // 0x19
  union {
    uint8_t RX_GAIN_I;
    struct {
      // LGS [2:0]: LNA gain. Recommend LGS= [000].
      LnaGainType LNA_GAIN : 3;
      // MGS [1:0]: Mixer gain. Recommend MGS= [00].
      MixerGainType MIXER_GAIN : 2;
      // IGC: Reserved for internal usage only. Shall be set to [0].
      uint8_t IGC : 1;
      // Undefined bit
      uint8_t : 1;
      // MVGS: Manual VGA calibrate. Recommend MVGS= [1].
      uint8_t MANUAL_VGA_CALIBRATE : 1;
    };
  };
  // 0x1A
  uint8_t RX_GAIN_II = 0x80; // reserved for internal usage only
  // 0x1B
  uint8_t RX_GAIN_III = 0x00; // reserved for internal usage only
  // 0x1C
  uint8_t RX_GAIN_IV = 0x0A; // reserved for internal usage only
  // 0x1D
  uint8_t RSSI_THRESHOLD;
  // 0x1E
  union {
    uint8_t ADC_CONTROL;
    struct {
      // CDM: RSSI measurement mode.
      // [0]: Single mode. [1]: Continuous mode.
      uint8_t RSSI_MEASUREMENT_MODE : 1;
      // RSS: RSSI measurement select.
      // [0]: Reserved for internal usage. [1]: RSSI or carrier-detect measurement.
      uint8_t RSSI_MEASUREMENT_SELECT : 1;
      // XADS: ADC input signal select.
      // [0]: Convert RSS signal. [1]: Reserved for internal usage.
      uint8_t ADC_INPUT_SIGNAL_SELECT : 1;
      // Undefined bit
      uint8_t : 1;
      // FSARS: ADC clock select. Recommend FSARS = [0].
      // [0]: 4MHz. [1]: 8MHz.
      uint8_t ADC_CLOCK_SELECT : 1;
      // ERSS: End for RSSI measurement
      // [0]: RSSI measurement continues until leave off RX mode.
      // [1]: RSSI measurement will end when carrier detected and ID code word received.
      uint8_t END_FOR_RSSI_MEASUREMENT : 1;
      // RSM [1:0]: RSSI margin = RTH – RTL. Recommend RSM = [11].
      RssiMarginType RSSI_MARGIN : 2;
    };
  };
  // 0x1F
  union {
    uint8_t CODE_I;
    struct {
      // PML [1:0]: Preamble length select. Recommend PML= [11].
      PreambleLengthType PREAMBLE_LENGTH : 2;
      // IDL: ID code length select. Recommend IDL= [1].
      IdLengthType ID_LENGTH : 1;
      // CRCS: CRC select.
      uint8_t CRC_SELECT : 1;
      // FECS: FEC select.
      uint8_t FEC_SELECT : 1;
      // WHTS: Data whitening (Data Encryption) select.
      uint8_t DATA_WHITENING_SELECT : 1;
      // No documentation
      uint8_t MCS : 1;
      // Undefined bit
      uint8_t : 1;
    };
  };
  // 0x20
  union {
    uint8_t CODE_II;
    struct {
      // PMD [1:0]: Preamble pattern detection length.
      PreamblePatternLengthType PREAMBLE_PATTERN_LENGTH : 2;
      // ETH [1:0]: ID code error tolerance. Recommend ETH = [01].
      IdCodeErrorToleranceType ID_CODE_ERROR_TOLERANCE : 2;
      // DCL [2:0]: Demodulator DC estimation average mode. Recommend DCL[2:0] = [001]
      uint8_t DEMODULATOR_DC_EST_AVG_MODE : 3;
      // Undefined bit
      uint8_t : 1;
    };
  };
  // 0x21
  union {
    uint8_t CODE_III;
    struct {
      // WS [6:0]: Data Whitening seed setting (data encryption key).
      uint8_t DATA_WHITENING_SEED : 7;
      // Undefined bit
      uint8_t : 1;
    };
  };
  // 0x22
  union {
    uint8_t IF_CALIBRATION_I;
    struct {
      // FB [3:0]: IF filter calibration value. (read)
      // MFB [3:0]: IF filter manual calibration value. (write)
      uint8_t FILTER_CALIBRATION_VALUE : 4;
      // FBCF: IF filter auto calibration flag. (read)
      // MFBS: IF filter calibration value select. Recommend MFBS = [0]. (write)
      uint8_t FILTER_CALIBRATION_FLAG : 1;
      // Undefined bits
      uint8_t : 3;
    };
  };
  // 0x23
  union {
    uint8_t IF_CALIBRATION_II;
    struct {
      // FCD [4:0]: IF filter calibration deviation from goal (Read only).
      uint8_t FILTER_CALIBRATION_DEVIATION : 5;
      // Undefined bits
      uint8_t : 3;
    };
  };
  // 0x24
  union {
    uint8_t VCO_CURRENT_CALIBRATION;
    struct {
      // VCB [3:0]: VCO current calibration value. (read)
      // VCOC [3:0]: VCO current manual calibration value. Recommend VCOC = [011] (write)
      uint8_t CURRENT_CALIBRATION : 4;
      // FVCC: VCO current auto calibration flag. (read)
      // MVCS: VCO current calibration value select. Recommend MVCS = [1]. (write)
      uint8_t CURRENT_CALIBRATION_FLAG : 1;
      // Undefined bits
      uint8_t : 3;
    };
  };
  // 0x25
  union {
    uint8_t VCO_SINGLE_BAND_CALIBRATION_I;
    struct {
      // VB [2:0]: VCO bank calibration value.
      uint8_t VCO_BANK_CALIBRATION_VALUE : 3;
      // VBCF: VCO band auto calibration flag.
      uint8_t VCO_BAND_AUTO_CALIBRATION_FLAG : 1;
      // DVT [1:0]: digital VCO tuning voltage output.
      DigitalVcoTuningVoltageType DIGITAL_VCO_TUNING_VOLTAGE : 2;
      // Undefined bits
      uint8_t : 2;
    } VCO_SINGLE_BAND_CALIBRATION_I_READ;
    struct {
      // MVB [2:0]: VCO band manual calibration value.
      uint8_t VCO_MANUAL_CALIBRATION_VALUE: 3;
      // MVBS: VCO bank calibration value select. Recommend MVBS = [0].
      uint8_t VCO_BANK_CALIBRATION_VALUE_SELECT: 1;
      // Undefined bits
      uint8_t : 4;
    } VCO_SINGLE_BAND_CALIBRATION_I_WRITE;
  };
  // 0x26
  union {
    uint8_t VCO_SINGLE_BAND_CALIBRATION_II;
    struct {
      // VTL [2:0]: VCO tuning voltage lower threshold level setting. Recommend VTL = [011].
      VoltageLowerThresholdLevelType VCO_TUNING_VOLTAGE_LOWER_THRESHOLD : 3;
      // VTH [2:0]: VCO tuning voltage upper threshold level setting. Recommend VTH = [111].
      VoltageUpperThresholdLevelType VCO_TUNING_VOLTAGE_UPPER_THRESHOLD : 3;
      // Undefined bits
      uint8_t : 2;
    };
  };
  // 0x27
  union {
    uint8_t BATTERY_DETECT;
    struct {
      // BDS: Battery detect select.
      uint8_t BATTERY_DETECT_SELECT : 1;
      // BVT [2:0]: Battery voltage detect threshold.
      BatteryVoltageDetectThresholdType BATTERY_VOLTAGE_DETECT_THRESHOLD : 3;
      // BDF: Battery detection flag.
      uint8_t BATTERY_DETECTION_FLAG : 1;
      // RGV [1:0]: VDD_D and VDD_A voltage setting in non-Sleep mode. Recommend RGV = [00].
      VoltageSettingNonSleepType RGV : 2;
      // RGS: VDD_D voltage setting in Sleep mode.
      uint8_t RGS : 1;
    };
  };
  // 0x28
  union {
    uint8_t TX_TEST;
    struct {
      // TBG [2:0]: TX Buffer Setting. [111]
      uint8_t TBG : 3;
      // PAC [1:0]: PA Current Setting. [10]
      uint8_t PAC : 2;
      // TXCS: TX Current Setting. [0]
      uint8_t TXCS : 1;
      // Undefined bits
      uint8_t : 2;
    };
  };
  // 0x29
  union {
    uint8_t RX_DEM_TEST_I;
    struct {
      // SLF [2:0]: Reserved for internal usage only. Shall be set to [111].
      uint8_t SLF : 3;
      // MLP [1:0]: Reserved for internal usage only. Shall be set to [00].
      uint8_t MLP : 2;
      // DCM [1:0]: Demodulator DC estimation mode.
      DemodulatorDcEstModeType DEMODULATOR_DC_EST_MODE : 2;
      // DMT: Reserved for internal usage only. Shall be set to [0].
      uint8_t DMT : 1;
    };
  };
  // 0x2A
  uint8_t RX_DEM_TEST_II; // DCV [7:0]: Demodulator fix mode DC value. Recommend DCV = [0x80].
  // 0x2B
  union {
    uint8_t CHARGE_PUMP_CURRENT;
    struct {
      // CPC [1:0]: Charge pump current setting. Recommend CPC = [11].
      ChargePumpCurrentType CHARGE_PUMP_CURRENT_SETTING : 2;
      // Undefined bits
      uint8_t : 6;
    };
  };
  // 0x2C
  union {
    uint8_t CYRSTAL_TEST;
    struct {
      // XCP [1:0]: Reserved for internal usage only. Shall be set to [01].
      uint8_t XCP : 2;
      // XCC: Reserved for internal usage only. Shall be set to [0].
      uint8_t XCC : 1;
      // DBD: Reserved for internal usage only. Shall be set to [0].
      uint8_t DBD : 1;
      // Undefined bits
      uint8_t : 4;
    };
  };
  // 0x2D
  union {
    uint8_t PLL_TEST;
    struct {
      // NSDO: Reserved for internal usage only. Shall be set to [1].
      uint8_t NSDO : 1;
      // SDPW: Reserved for internal usage only. Shall be set to [0].
      uint8_t SDPW : 1;
      // PRIC [1:0]: Reserved for internal usage only. Shall be set to [01].
      uint8_t PRIC : 2;
      // PRRC [1:0]: Reserved for internal usage only. Shall be set to [00].
      uint8_t PRRC : 2;
      // PMPE: Reserved for internal usage only. Shall be set to [1].
      uint8_t PMPE : 1;
      // Undefined bit
      uint8_t : 1;
    };
  };
  // 0x2E
  union {
    uint8_t VCO_TEST_I;
    struct {
      // VCBS: Reserved for internal usage only. Shall be set to [0].
      uint8_t VCBS : 1;
      // RLB [1:0]: Reserved for internal usage only. Shall be set to [00].
      uint8_t RLB : 2;
      // TLB [1:0]: Reserved for internal usage only. Shall be set to [11].
      uint8_t TLB : 2;
      // Undefined bits
      uint8_t : 3;
    };
  };
  // 0x2F
  union {
    uint8_t VCO_TEST_II;
    struct {
      // RFT [3:0]: RF analog pin configuration for testing. Recommend RFT= [0000].
      uint8_t RF_ANALOG_PIN_CONFIG : 4;
      // Undefined bits
      uint8_t : 4;
    };
  };
  // 0x30
  uint8_t IFAT = 0b00000001;
  // 0x31
  uint8_t RSCALE = 0x0F; // RSC [7:0]: Reserved for internal usage only. Shall be set to = [0x0F].
  // 0x32
  uint8_t FILTER_TEST = 0x00; // FT [7:0]: Reserved for internal usage only. Shall be set to = [0x00].
};

static_assert(sizeof(A7105State) == 0x33, "A7105State size mismatch");

}  // namespace esphome::a7105
