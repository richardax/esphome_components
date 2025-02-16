#include "arc_detector.h"
#include "esphome/core/log.h"

namespace esphome {
namespace arc_detector {

static const char *TAG = "arc_detector";

void ArcDetector::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Arc Detector...");
  init_adc();
}

void ArcDetector::loop() {
  uint32_t current_sample = read_adc();
  uint32_t delta = abs((int32_t)current_sample - (int32_t)prev_sample_);
  
  if (delta > threshold_) {
    ESP_LOGW(TAG, "Potential arc detected! Delta: %u", delta);
    publish_state(delta);
  }
  
  prev_sample_ = current_sample;
}

void ArcDetector::init_adc() {
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc_chars_);
}

uint32_t ArcDetector::read_adc() {
  uint32_t adc_reading = adc1_get_raw(ADC1_CHANNEL_0);
  return esp_adc_cal_raw_to_voltage(adc_reading, &adc_chars_);
}

}  // namespace arc_detector
}  // namespace esphome

