#include <BuzzerESP32.h>
#include <LiquidCrystal_I2C.h>

// All pin connections
#define detectorPin 16
#define ledPin 12
#define buzzerPin 25
#define buttonPin 14

// Buzzer frequencies
#define NOTE_LOW 880
#define NOTE_HIGH 1320
#define NOTE_BEEP 1000

// Delays
#define btnPressDebounce 10
#define detectionDelay 5000

// Different alarm states
#define STATE_DISARMED 0
#define STATE_ARMED 1
#define STATE_TRIGGERED 2

int state = STATE_DISARMED; // State machine

// LCD screen initializaton
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Buzzer initialization
BuzzerESP32 buzzer(buzzerPin);


void tripleBeep() {
    // Buzzer beeps 3 times in quick succession
    for (int i = 0; i < 3; i++) {
        buzzer.playTone(NOTE_BEEP, 50);
        delay(10);
    }
}

boolean buttonPressed(int pin) {
    if (digitalRead(pin) == 0) {
        return true;
    }

    return false;
}

// Disarmed state handler 
void handleDisarmed() {
    lcd.clear();
    lcd.print("Press To Arm");

    if (buttonPressed(buttonPin)) {
        tripleBeep();

        // LCD screen countdown
        delay(250);
        for (int i = 5; i >= 1; i--) {
            buzzer.playTone(NOTE_BEEP, 50);

            lcd.clear();
            lcd.print("Arming in ");
            lcd.print(i);

            delay(1000);
        }

        lcd.clear();
        lcd.print("Armed");
        buzzer.playTone(NOTE_BEEP, 500);

        // STATE CHANGE
        state = STATE_ARMED;
    }
}

// Armed state handler
void handleArmed() {
    lcd.setCursor(0, 1);

    // Motion detection
    // Motion sensor takes 3 seconds to reset after motion detection.
    // Therefore 4 sec error margin eliminates accidental alarm triggers.
    if (digitalRead(detectorPin) == 1) {
        lcd.print("Motion Detected");
        digitalWrite(ledPin, HIGH);

        delay(detectionDelay);

        digitalWrite(ledPin, LOW);
        if (digitalRead(detectorPin) == 1) {
            // STATE CHANGE
            state = STATE_TRIGGERED;
        }
    } 
    lcd.print("                ");
}

// Triggered state handler
void handleTriggered() {
    // Alarm trigger LCD message
    lcd.clear();
    lcd.print("Alarm Triggered");
    lcd.setCursor(0, 1);
    lcd.print("Press to disarm");

    // Audio and visual alarm
    // until button is pressed
    do {
        digitalWrite(ledPin, HIGH);
        buzzer.playTone(NOTE_LOW, 100);

        digitalWrite(ledPin, LOW);
        buzzer.playTone(NOTE_HIGH, 100);
    } while (!buttonPressed(buttonPin));

    state = STATE_DISARMED;

    tripleBeep();
    lcd.clear();
    lcd.print("Disarmed");

    delay(2000);
}

// ======== Main Loop ========

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
            handleDisarmed();
            break;
        case STATE_ARMED:
            handleArmed();
            break;
        case STATE_TRIGGERED:
            handleTriggered();
            break;
    }
    delay(100);
}
