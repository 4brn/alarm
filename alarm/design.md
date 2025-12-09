# Design

**Student Name:** Aleksandar Rangelov
**Student Number:** 572601

## Table of Contents

- [1. System Architecture](#1.%20System%20Architecture)
	- [1.1 Components](#1.1%20Components)
		- [1.1.1 Input Components](#1.1.1%20Input%20Components)
			- [1.1.1.1 Motion Sensor (PIR)](#1.1.1.1%20Motion%20Sensor%20(PIR))
			- [1.1.1.2 Push Button](#1.1.1.2%20Push%20Button)
		- [1.1.2 Output Components](#1.1.2%20Output%20Components)
			- [1.1.2.1 LCD Display (16x2 I2C)](#1.1.2.1%20LCD%20Display%20(16x2%20I2C))
			- [1.1.2.2 Buzzer](#1.1.2.2%20Buzzer)
			- [1.1.2.3 LED Indicator](#1.1.2.3%20LED%20Indicator)
- [2. State Machine Design](#2.%20State%20Machine%20Design)
	- [2.1 State Definitions](#2.1%20State%20Definitions)
		- [2.1.1 STATE_DISARMED (0)](#2.1.1%20STATE_DISARMED%20(0))
		- [2.1.2 STATE_ARMED (1)](#2.1.2%20STATE_ARMED%20(1))
		- [2.1.3 STATE_TRIGGERED (2)](#2.1.3%20STATE_TRIGGERED%20(2))
	- [2.2 Arming Sequence](#2.2%20Arming%20Sequence)
- [3. Timing and Delays](#3.%20Timing%20and%20Delays)
	- [3.1 Critical Timing Parameters](#3.1%20Critical%20Timing%20Parameters)
	- [3.2 False Trigger Prevention Algorithm](#3.2%20False%20Trigger%20Prevention%20Algorithm)
- [4. Data Flow](#4.%20Data%20Flow)
	- [4.1 Input Processing](#4.1%20Input%20Processing)
	- [4.2 Output Control](#4.2%20Output%20Control)
- [5. User Interface](#5.%20User%20Interface)
	- [5.1 Audio Feedback](#5.1%20Audio%20Feedback)
	- [5.2 LED Indicators](#5.3%20LED%20Indicators)
- [6. Conclusion](#6.%20Conclusion)


## 1. Architecture

The Student Accommodation Alarm System consists of an embedded system, controlled by a state machine. The system operates as a standalone device with local input/output components, requiring no network connectivity or dependencies.

**Components:**

- **Microcontroller (ESP32):**
  - State management and control logic
  - Sensor input processing
  - Output device control

- **Input Devices:**
  - Motion sensor (PIR)
  - Button

- **Output Devices:**
  - LCD display
  - Buzzer
  - LED indicator

This diagram provides a high-level overview of the system architecture:

![](Architecture.excalidraw.png)

In short, the user arms the system via button press, the motion sensor continuously monitors for movement, and upon detection, the system triggers visual and audible alarms until manually disarmed.

### 1.1 Components

Components are divided into 2 types:
- Input components
- Output components

#### 1.1.1 Input Components

##### 1.1.1.1 Motion Sensor (PIR)

> Passive Infrared sensor that detects motion by measuring changes in infrared radiation levels.

**Key Characteristics:**

- Connected to GPIO pin 16 with INPUT_PULLUP mode 
- Digital output: HIGH voltage when motion detected, LOW otherwise
- 3-second reset period after detection
- Wide-angle coverage for room monitoring

**Detection Behavior:**

- Continuous monitoring when system is armed
- Signal remains HIGH during motion presence
- Requires sustained detection (5 seconds) to trigger alarm
- Prevents false positives from brief movements or sensor resets

##### 1.1.1.2 Push Button

> Single tactile button for all user interactions (arm/disarm).

**Key Characteristics:**

- Connected to GPIO pin 14 with INPUT_PULLUP mode
- Reads HIGH voltage when released and LOW when pressed
- Single button simplifies user interface
- Contextual function based on current system state

**Functions by State:**

- **Disarmed:** Press to initiate arming sequence
- **Armed:** No function
- **Triggered:** Press to disarm and silence alarm

#### 1.1.2 Output Components

##### 1.1.2.1 LCD Display (16x2 I2C)

> Character-based display for system status and user instructions.

**Key Characteristics:**

- 16 columns × 2 rows character display
- I2C communication (address 0x27)
- Backlight for visibility in low light envoronments

**Display States:**

- **Disarmed:** "Press To Arm"
- **Arming:** Countdown from 5 to 1
- **Armed:** "Armed"
- **Triggered:** "Alarm Triggered" and "Press to disarm"

##### 1.1.2.2 Buzzer

> Active buzzer for audible alerts and feedback.

**Key Characteristics:**

- Connected to GPIO pin 25 (PWM capable)
- Multiple frequency support for different alert types
- Duration-controlled tone generation

**Audio Patterns:**

- **System Beep (1000 Hz):** Status confirmations
- **Triple Beep:** Arming/disarming confirmation
- **Alarm Pattern:** Alternating low (880 Hz) and high (1320 Hz) tones

##### 1.1.2.3 LED Indicator

> Visual indicator for motion detection and alarm status.

**Key Characteristics:**

- Connected to GPIO pin 12
- Simple ON/OFF control
- Provides silent visual feedback

**Behavior:**

- Illuminates during motion detection (armed state)
- Flashes during alarm (triggered state)
- Off during disarmed state

## 2. State Machine Design

The system operates as a finite state machine with three distinct states. This design ensures predictable behavior and clear state transitions.

![](State_Machine.excalidraw.png)

### 2.1 State Definitions

States:
- STATE_DISARMED (0)
- STATE_ARMED (1)  
- STATE_TRIGGERED (2)

#### 2.1.1 STATE_DISARMED (0)

**Description:** System inactive, all monitoring disabled.

**Entry Conditions:**
- System startup (default state)
- User presses button while in triggered state

**Behavior:**
- Display "Press To Arm" message
- Continuously poll button for arming request
- All sensors inactive
- No alarms active

**Exit Conditions:**
- Button press initiates arming sequence

#### 2.1.2 STATE_ARMED (1)

**Description:** Active monitoring mode

**Entry Conditions:**
- Successful completion of arming countdown

**Behavior:**
- Display "Armed" on LCD
- Continuous motion sensor monitoring
- Display "Motion Detected" when motion sensed
- LED indicator activates during motion detection
- 5-second sustained detection required for alarm trigger

**Exit Conditions:**
- Motion detected for 5+ continuous seconds, which triggers alarm

#### 2.1.3 STATE_TRIGGERED (2)

**Description:** Alarm active, awaiting user intervention.

**Entry Conditions:**
- Sustained motion detection while armed

**Behavior:**
- Display "Alarm Triggered" and "Press to disarm"
- Continuous alternating audio alarm (880 Hz ↔  1320 Hz)
- Flashing LED synchronized with audio
- Button monitoring for disarm request

**Exit Conditions:**
- Button press: returns to disarmed state

### 2.2 Arming Sequence

Special transition sequence from disarmed to armed with user feedback:

1. **Button Press Detection:** System detects button press in disarmed state
2. **Confirmation:** Triple beep indicates arming initiated
3. **Countdown:** 5-second visual countdown on LCD with audio feedback
4. **Armed Confirmation:** Long beep and "Armed" display
5. **State Change:** Transition to armed state

This sequence provides exit time and clear feedback to prevent user lockout.

## 3. Timing and Delays

### 3.1 Critical Timing Parameters

| Parameter | Value | Purpose |
|-----------|-------|---------|
| Detection Delay | 5000ms | Prevent false triggers from sensor reset |
| Arming Countdown | 5 seconds | User exit time |
| Button Debounce | 10ms | Eliminate mechanical bounce |
| Main Loop Delay | 100ms | Reasonable polling frequency |
| Triple Beep Delay | 10ms | Spacing between confirmation beeps |

### 3.2 False Trigger Prevention Algorithm

```
Step 1: Motion detected
Step 2: LED indicator activates
Step 3: Wait 5000ms
Step 4: Check motion again
Step 5:
	If motion is still detected, triger alarm
	OR
    If not motion detected, return to monitoring (false positive avoided)
```

This algorithm accounts for:
- 3-second sensor reset time
- Brief environmental changes (shadows, temperature fluctuations)
- Passing motion (person walking by doorway)
- 2-second safety margin beyond sensor reset

## 4. Data Flow

### 4.1 Input Processing

**Input Characteristics:**
- Digital inputs only (HIGH/LOW)
- Polled every 100ms in main loop

### 4.2 Output Control

**Output Control:**
- State-specific output
- multi-output feedback (audio + visual + display)

## 5. User Interface

### 5.1 Audio Feedback

**Single Beep:**
- Frequency: 1000 Hz
- Duration: 50ms
- Usage: Countdown beeps, status confirmations

**Triple Beep:**
- Pattern: Three rapid beeps with 10ms spacing
- Usage: Arming initiated, system disarmed

**Alarm Pattern:**
- Pattern: Alternating 880 Hz and 1320 Hz tones
- Duration: 100ms each tone
- Continuous loop until disarmed
- Creates attention-grabbing alternating pitch

### 5.2 LED Indicators

| State | LED Behavior | Meaning |
|-------|--------------|---------|
| Disarmed | OFF | System inactive |
| Armed (no motion) | OFF | Monitoring, no detection |
| Armed (motion) | ON | Motion detected, validation in progress |
| Triggered | FLASHING | Alarm active |


## 6. Conclusion

The design prioritizes **simplicity, reliability, and user experience**:

- **State Machine:** Clear separation of operational modes ensures predictable behavior
- **False Positive Prevention:** 5-second sustained detection algorithm prevents unnecessary alarms
- **Multi-Modal Feedback:** Visual (LCD + LED), audible (buzzer), and textual feedback ensure user awareness
- **Single-Button Operation:** Minimalist interface reduces user error and hardware complexity
- **Timing Optimization:** Carefully tuned delays balance responsiveness with reliability

The modular embedded design allows **future enhancements** (wireless connectivity, multiple zones, remote monitoring, component housing) without fundamental architectural changes. The current implementation serves as a solid foundation for a future development of the student accommodation security system.