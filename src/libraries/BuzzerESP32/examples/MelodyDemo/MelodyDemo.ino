#include <BuzzerESP32.h>

BuzzerESP32 buzzer(25); // GPIO25

void setup() {
  buzzer.setTimbre(30); // 设置音色
}

void loop() {
  // 演奏《欢乐颂》片段
  buzzer.playTone(BuzzerESP32::NOTE_E4, 500);
  buzzer.playTone(BuzzerESP32::NOTE_E4, 500);
  buzzer.playTone(BuzzerESP32::NOTE_F4, 500);
  buzzer.playTone(BuzzerESP32::NOTE_G4, 500);
  
  delay(1000);
  
  // 和弦演示
  buzzer.setFrequency(330); // E4
  delay(300);
  buzzer.setFrequency(392); // G4
  delay(300);
  buzzer.stop();
  
  delay(2000);
}