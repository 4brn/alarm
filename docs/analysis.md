# Analysis

**Name:** Aleksandar Rangelov
**Student Number:** 572601

## Table of Contents

- [1. Project Description](#1.%20Project%20Description)
- [2. Requirements](#2.%20Requirements)
	- [2.1 Functional Requirements](#2.1%20Functional%20Requirements)
	- [2.2 Non-Functional Requirements](#2.2%20Non-Functional%20Requirements)
	- [2.3 User Stories](#2.3%20User%20Stories)
- [3. Technical Stack](#3.%20Technical%20Stack)
	- [3.1 Hardware Components](#3.1%20Hardware%20Components)
		- [3.1.1 ESP32 Microcontroller](#3.1.1%20ESP32%20Microcontroller)
		- [3.1.2 Motion Sensor (PIR)](#3.1.2%20Motion%20Sensor%20(PIR))
		- [3.1.3 LCD Display (I2C)](#3.1.3%20LCD%20Display%20(I2C))
		- [3.1.4 Buzzer Module](#3.1.4%20Buzzer%20Module)
		- [3.1.5 Additional Components](#3.1.5%20Additional%20Components)
	- [3.2 Software Architecture](#3.2%20Software%20Architecture)
		- [3.2.1 Arduino Framework](#3.2.1%20Arduino%20Framework)
		- [3.2.2 State Machine Design Pattern](#3.2.2%20State%20Machine%20Design%20Pattern)
		- [3.2.3 Libraries](#3.2.3%20Libraries)
	- [3.3 Key Algorithms](#3.3%20Key%20Algorithms)
		- [3.3.1 False Trigger Prevention](#3.3.1%20False%20Trigger%20Prevention)
		- [3.3.2 Arming Sequence](#3.3.2%20Arming%20Sequence)
- [4. Conclusion](#4.%20Conclusion)

## 1. Project Description

The Student Accommodation Alarm System is a security solution designed specifically for shared living spaces and student housing. The system utilizes an ESP32 microcontroller with integrated motion detection to provide basic intrusion detection capabilities through an audible alarm and visual indicators.

**Key Features:**

- Motion-based intrusion detection
- Visual feedback via LED indicator
- Audible alarm with buzzer
- LCD display for system status
- Simple arm/disarm functionality via button
- State-based operation (Disarmed, Armed, Triggered)

## 2. Requirements

### 2.1 Functional Requirements

1. Detect motion when system is armed
2. Provide visual and audible alerts when triggered
3. Display system status on LCD screen
4. Allow manual arming and disarming via button
5. Implement countdown timer before arming
6. Prevent false triggers with detection delay
7. Maintain clear state transitions between modes

### 2.2 Non-Functional Requirements

- **Reliability:** Consistent motion detection without false positives
- **Usability:** Simple one-button operation for arm/disarm functionality
- **Performance:** Immediate response to motion detection events
- **Accessibility:** Clear visual feedback through LCD display and LED
- **Power Efficiency:** Continuous operation as background monitoring system

### 2.3 User Stories

- As a student, I want to arm my room when leaving, so my belongings are protected.
- As a resident, I want clear visual feedback on system status, so I know when the alarm is active.
- As a user, I want a countdown before arming, so I have time to exit the room.
- As a shared space user, I want an audible alarm, so intruders are deterred and others are alerted.
- As a user, I want the device to be compact, so I can bring it with me when switching places.

## 3. Technical Analysis

### 3.1 Hardware Components

#### 3.1.1 ESP32 Microcontroller

> The ESP32 is a low-cost, low-power microcontroller with integrated Wi-Fi and Bluetooth capabilities.

- Sufficient GPIO pins for multiple sensors and outputs
- Built-in wireless capabilities for future expansion
- Low power consumption for continuous operation
- Wide community support and documentation

#### 3.1.2 Motion Sensor (PIR)

> Passive Infrared sensor for detecting movement.

- Detects infrared radiation changes from moving objects
- Wide detection angle suitable for room monitoring

**Note:** The specific sensor model is from a development kit and is therefore unknown. Future iterations should identify exact specifications.

#### 3.1.3 LCD Display (I2C)

> 16x2 character LCD display using I2C communication protocol.

- Displays system status and countdown timers
- Clear visibility for user feedback
- Two-line display for status and instructions

#### 3.1.4 Buzzer Module

> Active buzzer for audible alerts.

- Capable of multiple tone frequencies
- PWM-controlled for varying sound patterns
- Low power consumption
- Clear audible range for alarm purposes

#### 3.1.5 Additional Components

- **LED Indicator:** Visual motion detection feedback
- **Button:** Used for arming and disarming 

### 3.2 Software Architecture

#### 3.2.1 Arduino Framework

> Standard Arduino framework for ESP32 development.

- Extensive library ecosystem
- Simple programming model
- Cross-platform IDE support
- Well-documented for beginners

#### 3.2.2 State Machine

The system implements a state machine with three distinct states:

- **Disarmed:** System inactive, waiting for arming command
- **Armed:** Active monitoring for motion detection
- **Triggered:** Alarm activated, awaiting disarm command

This approach provides:
- Clear separation of concerns
- Predictable behavior transitions
- Easy debugging and maintenance
- Straightforward future expansion

#### 3.2.3 Libraries

**LiquidCrystal_I2C**[^1]
> Library for controlling LCD displays via I2C protocol.

- Simplified LCD communication
- Reduced wiring complexity
- Standard text display functions

**BuzzerESP32**[^2]
> Library for tone generation on ESP32 buzzer.

- Multiple frequency support
- Duration control for tones
- Simple API for audio feedback

### 3.3 Key Algorithms

#### 3.3.1 False Trigger Prevention

The system implements a 5-second detection delay to prevent false alarms:

1. Initial motion detected LED indicator activates
2. 5-second delay period begins
3. After delay, motion sensor state is rechecked
4. Alarm triggers only if motion persists

This accounts for the sensor's 3-second reset time plus additional margin for reliability.

#### 3.3.2 Arming Sequence

5-second countdown with audio feedback:
- Provides exit time for the user
- Clear visual countdown on LCD
- Audible beeps at each second
- Confirmation tone when armed

## 4. Conclusion

The Student Accommodation Alarm System successfully demonstrates fundamental embedded systems concepts through a practical security application. The state machine architecture provides a solid foundation for future enhancements. The combination of motion detection, visual feedback, and audible alerts creates a basic but effective security solution suitable for shared living spaces.

[^1]: LiquidCrystal I2C Library. (n.d.). Retrieved from [Arduino Library Manager](https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/)
[^2]: BuzzerESP32 Library. (n.d.). Retrieved from [Arduino Library Manager](https://www.arduino.cc/reference/en/libraries/buzzeresp32/)