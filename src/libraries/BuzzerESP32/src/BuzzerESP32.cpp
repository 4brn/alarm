#include "BuzzerESP32.h"

BuzzerESP32::BuzzerESP32(uint8_t pin, 
                       ledc_channel_t channel,
                       ledc_timer_t timer,
                       uint32_t base_freq,
                       uint8_t duty_resolution,
                       bool active_high) :
  _pin(pin), _channel(channel), _timer(timer),
  _base_freq(base_freq), _duty_res(duty_resolution),
  _active_state(active_high) {
  _setupPWM();
}

void BuzzerESP32::_setupPWM() {
  // 配置定时器
  ledc_timer_config_t timer_conf = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = static_cast<ledc_timer_bit_t>(_duty_res),
    .timer_num = _timer,
    .freq_hz = _base_freq,
    .clk_cfg = LEDC_AUTO_CLK
  };
  ledc_timer_config(&timer_conf);

  // 配置通道
  ledc_channel_config_t ch_conf = {
    .gpio_num = _pin,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = _channel,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = _timer,
    .duty = 0,
    .hpoint = 0
  };
  ledc_channel_config(&ch_conf);
}

void BuzzerESP32::playTone(uint32_t freq, uint32_t duration_ms) {
  if(freq == 0) {
    stop();
    return;
  }

  ledc_set_freq(LEDC_LOW_SPEED_MODE, _timer, freq);
  
  uint32_t duty = (1 << _duty_res) / 2;
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _channel, _active_state ? duty : (1 << _duty_res) - duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _channel);

  if(duration_ms > 0) {
    delay(duration_ms);
    stop();
  }
}

void BuzzerESP32::stop() {
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _channel, _active_state ? 0 : (1 << _duty_res));
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _channel);
}

void BuzzerESP32::setTimbre(uint8_t duty_percent) {
  duty_percent = constrain(duty_percent, 1, 99);
  uint32_t duty = (duty_percent * (1 << _duty_res)) / 100;
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _channel, _active_state ? duty : (1 << _duty_res) - duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _channel);
}

void BuzzerESP32::setFrequency(uint32_t freq) {
  ledc_set_freq(LEDC_LOW_SPEED_MODE, _timer, freq);
}