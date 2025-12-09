# Realisation

**Student Name:** Aleksandar Rangelov
**Student Number:** 572601

## Table of Contents 

- [1. Introduction](#1.%20Introduction)
- [2. Development Environment](#2.%20Development%20Environment)
	- [2.1 Required Software](#2.1%20Required%20Software)
	- [2.2 Hardware Requirements](#2.2%20Hardware%20Requirements)
	- [2.3 System Requirements](#2.3%20System%20Requirements)
- [3. Realisation](#3.%20Realisation)
	- [3.1 Development Phases](#3.1%20Development%20Phases)
		- [3.1.1 Project Setup & Research](#3.1.1%20Project%20Setup%20&%20Research)
		- [3.1.2 Hardware Assembly](#3.1.2%20Hardware%20Assembly)
		- [3.1.3 Software Development](#3.1.3%20Software%20Development)
		- [3.1.4 Testing & Refinement](#3.1.4%20Testing%20&%20Refinement)
	- [3.2 Realisation Decisions](#3.2%20Realisation%20Decisions)
- [4. Hardware Architecture](#4.%20Hardware%20Architecture)
	- [4.1 Component Assembly](#4.1%20Component%20Assembly)
		- [4.1.1 Pin Connections](#4.1.1%20Pin%20Connections)
	- [4.2 Physical Setup](#4.2%20Physical%20Setup)
- [5. Software Architecture](#5.%20Software%20Architecture)
	- [5.1 Project Structure](#5.1%20Project%20Structure)
	- [5.2 Code Organization](#5.2%20Code%20Organization)
- [6. Code Implementation](#6.%20Code%20Implementation)
	- [6.1 Pin and State Definitions](#6.1%20Pin%20and%20State%20Definitions)
	- [6.2 Component Initialization](#6.2%20Component%20Initialization)
	- [6.3 State Machine Implementation](#6.3%20State%20Machine%20Implementation)
	- [6.4 Button Detection](#6.4%20Button%20Detection)
	- [6.5 Audio Feedback System](#6.5%20Audio%20Feedback%20System)
	- [6.6 Disarmed State Handler](#6.6%20Disarmed%20State%20Handler)
	- [6.7 Armed State Handler](#6.7%20Armed%20State%20Handler)
	- [6.8 Triggered State Handler](#6.8%20Triggered%20State%20Handler)
- [7. Configuration](#7.%20Configuration)
	- [7.1 Timing Parameters](#7.1%20Timing%20Parameters)
	- [7.2 Audio Frequencies](#7.2%20Audio%20Frequencies)
	- [7.3 Pin Reassignment](#7.3%20Pin%20Reassignment)
- [8. Deployment Guide](#8.%20Deployment%20Guide)
	- [8.1 Initial Setup](#8.1%20Initial%20Setup)
	- [8.2 Hardware Assembly](#8.2%20Hardware%20Assembly)
	- [8.3 Software Upload](#8.3%20Software%20Upload)
	- [8.4 Deployment](#8.4%20Deployment)



## 1. Introduction

This document describes the technical implementation of the Student Accommodation Alarm System - a security solution for shared living spaces. It covers the development environment setup, implementation approach, key code structures, hardware assembly, and deployment procedures.

## 2. Development Environment

### 2.1 Required Software

| Software | Version | Purpose |
|----------|---------|---------|
| Arduino IDE | 2.0+ | Development environment and code upload |
| ESP32 Board Package | Latest | ESP32 microcontroller support |
| LiquidCrystal_I2C Library | Latest | LCD display control |
| BuzzerESP32 Library | Latest | Buzzer interaction |

### 2.2 Hardware Requirements

- **Microcontroller:** ESP32 development board
- **Sensors:** PIR motion sensor
- **Output Devices:** 16x2 LCD display (I2C) , active buzzer, LED
- **Input Device:** Tactile push button
- **Power Supply:** USB cable or external 5V power source
- **Miscellaneous:** Breadboard, jumper wires, resistors

### 2.3 System Requirements

- Computer with USB port for programming
- Arduino IDE with ESP32 support configured
- USB cable compatible with ESP32 board
- Stable power supply (5V, 500mA minimum)

## 3. Realisation

> Components are a subject to change because of the use of a ESP32 development kit, not suitable mass production.

### 3.1 Development Phases

#### 3.1.1 Project Setup & Research

- [x] Research suitable microcontroller platforms
- [x] Select ESP32 for future expandability
- [x] Identify required sensors and components from development kit
- [x] Set up Arduino IDE with ESP32 board support
- [x] Install necessary libraries (LiquidCrystal_I2C, BuzzerESP32)

#### 3.1.2 Hardware Assembly

- [x] Connect motion sensor to GPIO 16
- [x] Connect push button to GPIO 14
- [x] Connect LED indicator to GPIO 12
- [x] Connect buzzer to GPIO 25
- [x] Wire LCD display via I2C (SDA/SCL)
- [x] Test individual components
- [x] Verify all connections and pin configurations

#### 3.1.3 Software Development

- [x] Implement state machine structure (3 states)
- [x] Create state handler functions
- [x] Implement motion detection logic
- [x] Add false trigger prevention algorithm
- [x] Create arming sequence with countdown
- [x] Implement alarm trigger and audio patterns
- [x] Add LCD display messages for each state
- [x] Create button press detection function
- [x] Implement LED indicator control

### 3.2 Realisation Decisions

**State Machine Pattern**

A finite state machine was chosen to ensure predictable behavior and easy debugging. Each state has a dedicated handler function, making the code modular and maintainable. This pattern also simplifies future feature additions, such as additional states for entry delays or maintenance modes.

**5-Second Detection Delay**

After initial testing, false triggers were common due to the PIR sensor's 3-second reset time. The 5-second debounced detection requirement (3-second sensor reset + 2-second margin) effectively eliminates false positives from brief movements, shadows, or sensor fluctuations while maintaining acceptable response time for genuine intrusions.

**Single Button Interface**

Rather than implementing multiple buttons or a keypad, a single-button interface was chosen for simplicity. The button's function is context-aware (changes based on current state), reducing hardware complexity and user confusion. This decision aligns with the current scope while maintaining full functionality. Of course a keypad will be the obvious future improvement, but for the time being, a button is sufficient.

**Hardcoded Configuration**

All timing parameters and pin assignments are defined as preprocessor constants rather than runtime configuration. This decision prioritizes code clarity and simplicity over flexibility. In future updates, parameters will be configurable.

## 4. Hardware Architecture

### 4.1 Component Assembly

#### 4.1.1 Pin Connections

**Motion Sensor (PIR):**
- VCC to 5V
- GND to GND
- OUT to GPIO 16

**Push Button:**
- Positive (+) to GPIO 14
- Negative (-) to GND

**LED Indicator:**
- Anode (+) to GPIO 12
- Cathode (-) to GND

**Buzzer:**
- Positive (+) to GPIO 25
- Negative (-) to GND

**LCD Display (I2C):**
- VCC to 5V
- GND to GND
- SDA to GPIO 21 (ESP32 default I2C SDA)
- SCL to GPIO 22 (ESP32 default I2C SCL)

### 4.2 Physical Setup

![](Wiring.excalidraw.png)

## 5. Software Architecture

### 5.1 Project Structure

```
alarm-system/
├── alarm.ino                 # Main Arduino sketch
├── docs/                     # Documentation
├── libraries/                # Libraries
└── README.md
```

### 5.2 Code Organization

**alarm.ino** - Single file containing:
- Library includes
- Pin definitions
- Constant definitions
- State definitions
- Global variables
- Helper functions
- State handler functions
- Setup function
- Main loop

## 6. Code Implementation

### 6.1 Pin and State Definitions

```cpp
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
```

- Definitions provide clear, readable constants
- Centralized configuration makes adjustments easy

### 6.2 Component Initialization

```cpp
// LCD screen initialization
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Buzzer initialization
BuzzerESP32 buzzer(buzzerPin);

void setup() {
    Serial.begin(9600);
    
    lcd.init();
    lcd.backlight();
    
    pinMode(detectorPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
}
```

- LCD initialized with I2C address and dimensions
- Serial communication enabled for debugging
- All GPIO pins configured before main loop
- Buzzer initialized with dedicated library

### 6.3 State Machine Implementation

```cpp
int state = STATE_DISARMED; // State machine variable

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
    delay(100); // 100ms polling interval
}
```

- Single state variable controls system behavior
- Switch statement routes to appropriate handler
- Main loop runs continuously at 10Hz
- Each state handler is self-contained

### 6.4 Button Detection

```cpp
boolean buttonPressed(int pin) {
    if (digitalRead(pin) == 0) {
        return true;
    }
    return false;
}
```

- Simple wrapper function for button state
- Active-low logic (pressed = 0)
- Used by all state handlers
- Future enhancement: implement proper debouncing

### 6.5 Audio Feedback System

```cpp
void tripleBeep() {
    // Buzzer beeps 3 times in quick succession
    for (int i = 0; i < 3; i++) {
        buzzer.playTone(NOTE_BEEP, 50);
        delay(10);
    }
}
```

- Reusable function for confirmation feedback
- Called during arming and disarming
- Short duration prevents annoyance
- Consistent user experience

### 6.6 Disarmed State Handler

```cpp
void handleDisarmed() {
    lcd.clear();
    lcd.print("Press To Arm");

    if (buttonPressed(buttonPin)) {
        tripleBeep();
        delay(250);
        
        // LCD screen countdown
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
        
        state = STATE_ARMED; // State transition
    }
}
```

- Displays instruction to user
- Monitors button for arming request
- Provides 5-second exit countdown
- Audio and visual feedback during countdown
- Confirmation tone when armed
- Explicit state transition at end

### 6.7 Armed State Handler

```cpp
void handleArmed() {
    lcd.setCursor(0, 1); // Move to second line

    // Motion detection with false trigger prevention
    if (digitalRead(detectorPin) == 1) {
        lcd.print("Motion Detected");
        digitalWrite(ledPin, HIGH);

        delay(detectionDelay); // 5-second sustained detection

        digitalWrite(ledPin, LOW);
        if (digitalRead(detectorPin) == 1) {
            state = STATE_TRIGGERED; // Trigger alarm
        }
    }
    lcd.print("                "); // Clear line
}
```

- Continuously monitors motion sensor
- Displays detection on second LCD line
- LED provides immediate visual feedback
- 5-second delay prevents false triggers
- Re-checks sensor after delay
- Triggers alarm only if motion persists
- Clears status message when no motion

### 6.8 Triggered State Handler

```cpp
void handleTriggered() {
    lcd.clear();
    lcd.print("Alarm Triggered");
    lcd.setCursor(0, 1);
    lcd.print("Press to disarm");

    // Continuous alarm loop
    do {
        digitalWrite(ledPin, HIGH);
        buzzer.playTone(NOTE_LOW, 100);

        digitalWrite(ledPin, LOW);
        buzzer.playTone(NOTE_HIGH, 100);
    } while (!buttonPressed(buttonPin));

    state = STATE_DISARMED; // Disarm system

    tripleBeep();
    lcd.clear();
    lcd.print("Disarmed");
    delay(2000);
}
```

- Displays alarm status and disarm instruction
- Alternating tones create attention-grabbing pattern
- LED flashes synchronized with audio
- Loops continuously until button pressed
- Immediate state transition to disarmed
- Confirmation feedback (beep + display)
- 2-second message display before returning to main loop

## 7. Configuration

### 7.1 Timing Parameters

All timing values can be adjusted by modifying the constant definitions:

```cpp
#define detectionDelay 5000      // Motion detection delay (ms)
#define btnPressDebounce 10      // Button debounce delay (ms)
```

**Recommended Ranges:**
- Detection Delay: 3000-10000ms (balance false positives vs. response time)
- Button Debounce: 10-50ms (depends on button quality)
- Arming Countdown: Modify loop in `handleDisarmed()` (currently 5 seconds)

### 7.2 Audio Frequencies

Buzzer tones can be customized:

```cpp
#define NOTE_LOW 880      // Lower alarm tone (Hz)
#define NOTE_HIGH 1320    // Higher alarm tone (Hz)
#define NOTE_BEEP 1000    // System beep tone (Hz)
```

**Guidelines:**
- Use frequencies between 500-2000 Hz for best audibility
- Ensure sufficient difference between LOW and HIGH for distinction
- Test actual buzzer capabilities (some buzzers have limited range)

### 7.3 Pin Reassignment

If using different GPIO pins, update all pin definitions:

```cpp
#define detectorPin 16    // Motion sensor
#define ledPin 12         // LED indicator
#define buzzerPin 25      // Buzzer (must be PWM-capable)
#define buttonPin 14      // Push button
```

**Important:** GPIO 25 (buzzer) must support PWM output for tone generation.

## 8. Deployment Guide

### 8.1 Initial Setup

**Step 1: Install Arduino IDE**
- Download from [arduino.cc](https://www.arduino.cc/en/software)
- Install ESP32 board support via Board Manager

**Step 2: Install Libraries**
```
Arduino IDE →  Tools →  Manage Libraries
- Search: "LiquidCrystal I2C"
- Search: "BuzzerESP32"
- Install both libraries
```

**Step 3: Configure Board Settings**
```
Tools →  Board →  ESP32 Arduino →  ESP32 Dev Module
Tools →  Port →  [Select appropriate COM port]
Tools →  Upload Speed →  115200
```

### 8.2 Hardware Assembly

**Step 1: Connect Power**
- Connect ESP32 to computer via USB (for initial testing)

**Step 2: Wire Components**
- Follow pin connection diagram in Section 4.1.1
- Double-check all connections before powering on
- Ensure I2C LCD address matches code (default: 0x27)

**Step 3: Test Individual Components**
- Upload simple test sketches for each component
- Verify LCD displays text correctly
- Confirm motion sensor triggers
- Test buzzer produces sound
- Check LED illuminates

### 8.3 Software Upload

**Step 1: Open Project**
```
Arduino IDE →  File →  Open →  alarm.ino
```

**Step 2: Compile Code**
```
Sketch →  Verify/Compile (Ctrl+R)
```

**Step 3: Upload to ESP32**
```
Sketch →  Upload (Ctrl+U)
```

**Step 4: Monitor Serial Output (Optional)**
```
Tools →  Serial Monitor
Set baud rate: 9600
```

### 8.4 Deployment

**Step 1: Mount Hardware**
- Position motion sensor covering desired detection area
- Mount LCD display in visible location
- Place button within easy reach
- Secure all wiring to prevent disconnection

**Step 2: Power Supply**
- For permanent installation, use external 5V power supply
- Ensure power supply provides minimum 500mA
- Consider battery backup for power outages

**Step 3: Initial Testing**
```
1. Power on system (should display "Press To Arm")
2. Press button to arm (countdown should begin)
3. Wait for "Armed" confirmation
4. Trigger motion sensor
5. Wait 5 seconds (LED should illuminate)
6. Alarm should sound
7. Press button to disarm
```

**Step 4: Fine-Tuning**
- Test detection range and coverage
- Verify timing parameters meet requirements
