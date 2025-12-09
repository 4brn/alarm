#ifndef BuzzerESP32_h
#define BuzzerESP32_h

#include "Arduino.h"
#include "driver/ledc.h"

class BuzzerESP32 {
public:
  // 构造函数
  BuzzerESP32(uint8_t pin, 
              ledc_channel_t channel = LEDC_CHANNEL_0,
              ledc_timer_t timer = LEDC_TIMER_0,
              uint32_t base_freq = 5000,
              uint8_t duty_resolution = 8,
              bool active_high = true);

  // 基础功能
  void playTone(uint32_t freq, uint32_t duration_ms = 0);
  void stop();
  
  // 高级控制
  void setTimbre(uint8_t duty_percent);
  void setFrequency(uint32_t freq);
  
  // 预设音调
  static const uint32_t NOTE_C4 = 262;
  static const uint32_t NOTE_D4 = 294;
  static const uint32_t NOTE_E4 = 330;
  static const uint32_t NOTE_F4 = 349;
  static const uint32_t NOTE_G4 = 392;
  static const uint32_t NOTE_A4 = 440;
  static const uint32_t NOTE_B4 = 494;

private:
  uint8_t _pin;
  ledc_channel_t _channel;
  ledc_timer_t _timer;
  uint32_t _base_freq;
  uint8_t _duty_res;
  bool _active_state;
  
  void _setupPWM();
};

#endif