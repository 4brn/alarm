#include <BuzzerESP32.h>
#include <LiquidCrystal_I2C.h>

#define detectorPin 16
#define ledPin 12
#define buzzerPin 25
#define buttonPin 14

#define NOTE_LOW 880
#define NOTE_HIGH 1320
#define NOTE_BEEP 880

#define btnPressDebounce 10

#define STATE_DISARMED 0
#define STATE_ARMED 1
#define STATE_TRIGGERED 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
BuzzerESP32 buzzer(buzzerPin);

int state = STATE_DISARMED;
boolean alarmTriggered = false;
int detectionDelay = 5000;  // 5 seconds

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(detectorPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  switch (state) {
    case STATE_DISARMED:

      lcd.clear();
      lcd.print("Press To Arm");

      if (buttonPressed(buttonPin, btnPressDebounce)) {
        tripleBeep();
        delay(250);

        lcd.clear();
        lcd.print("Arming in ");
        for (int i = 5; i >= 1; i--) {
          lcd.setCursor(10, 0);
          lcd.print(i);
          buzzer.playTone(NOTE_BEEP, 50);
          delay(1000);
        }

        lcd.clear();
        lcd.print("Armed");
        buzzer.playTone(NOTE_BEEP, 500);

        state = STATE_ARMED;
      }

      break;

    case STATE_ARMED:
      lcd.setCursor(0, 1);
      if (digitalRead(detectorPin) == 1) {
        lcd.print("Motion Detected");

        digitalWrite(ledPin, HIGH);
        delay(4000);
        digitalWrite(ledPin, LOW);

        if (digitalRead(detectorPin) == 1) {
          state = STATE_TRIGGERED;
        }
      } else {
        lcd.print("               ");
      }

      break;

    case STATE_TRIGGERED:
      lcd.clear();
      lcd.print("Alarm Triggered");
      lcd.setCursor(0, 1);
      lcd.print("Press to disarm");

      do {
        digitalWrite(ledPin, HIGH);
        buzzer.playTone(NOTE_LOW, 100);

        digitalWrite(ledPin, LOW);
        buzzer.playTone(NOTE_HIGH, 100);
      } while (buttonPressed(buttonPin, btnPressDebounce) == false);

      state = STATE_DISARMED;
      tripleBeep();
      lcd.clear();
      lcd.print("Disarmed");

      delay(2000);
      break;
  }

  delay(200);
}

void tripleBeep() {
  for (int i = 0; i < 3; i++) {
    buzzer.playTone(NOTE_BEEP, 50);
    delay(10);
  }
}

boolean buttonPressed(int pin, int debounce) {
  if (digitalRead(pin) == 0) {
    delay(debounce);
    if (digitalRead(pin) == 0) {
      return true;
    }
  }

  return false;
}
