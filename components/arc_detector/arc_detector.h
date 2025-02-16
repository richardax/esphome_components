#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

namespace esphome {
namespace arc_detector {

class ArcDetector : public Component, public sensor::Sensor {
 public:
  void setup() override;
  void loop() override;
  
  void set_pin(uint8_t pin) { pin_ = pin; }
  void set_threshold(uint32_t threshold) { threshold_ = threshold; }

 private:
  uint8_t pin_;
  uint32_t threshold_ = 500;
  uint32_t prev_sample_ = 0;
  esp_adc_cal_characteristics_t adc_chars_;
  
  void init_adc();
  uint32_t read_adc();
};

}  // namespace arc_detector
}  // namespace esphome

