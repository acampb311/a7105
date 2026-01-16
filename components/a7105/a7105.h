#pragma once

#include <cstdint>
#include "a7105_defs.h"
#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace a7105 {

class A7105Component : public Component,
                       public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST,spi::CLOCK_POLARITY_LOW,
                              spi::CLOCK_PHASE_LEADING,spi::DATA_RATE_1KHZ> {
  public:
    A7105Component();

    void setup() override;
    void loop() override;
    void dump_config() override;

    // a7105_component.h
    void send_payload(std::initializer_list<uint8_t> id, std::initializer_list<uint8_t> data);

  protected:
    A7105State state_;

    void write_(std::initializer_list<uint8_t> list);
    void write_(Mode mode);
    void write_(Strobe cmd);
    void write_(Register reg);
    void write_(Register reg, uint8_t value);
    uint8_t read_(Register reg);
};


}  // namespace a7105
}  // namespace esphome
