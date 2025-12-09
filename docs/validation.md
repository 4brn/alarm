# Validation

**Student Name:** Aleksandar Rangelov
**Student Number:** 572601

## Table of Contents

- [1. Requirements Validation](#1.%20Requirements%20Validation)
- [2. Functional Requirements](#2.%20Functional%20Requirements)
	- [2.1 Motion Detection](#2.1%20Motion%20Detection)
	- [2.2 Visual and Audible Alerts](#2.2%20Visual%20and%20Audible%20Alerts)
	- [2.3 System Status Display](#2.3%20System%20Status%20Display)
	- [2.4 Manual Arming/Disarming](#2.4%20Manual%20Arming/Disarming)
	- [2.5 Arming Countdown](#2.5%20Arming%20Countdown)
	- [2.6 False Trigger Prevention](#2.6%20False%20Trigger%20Prevention)
	- [2.7 Clear State Transitions](#2.7%20Clear%20State%20Transitions)
- [3. Non-Functional Requirements](#3.%20Non-Functional%20Requirements)
	- [3.1 Reliability](#3.1%20Reliability)
	- [3.2 Usability](#3.2%20Usability)
	- [3.3 Performance](#3.3%20Performance)
	- [3.4 Accessibility](#3.4%20Accessibility)
	- [3.5 Power Efficiency](#3.5%20Power%20Efficiency)
- [4. User Stories Validation](#4.%20User%20Stories%20Validation)
	- [4.1 Room Protection](#4.1%20Room%20Protection)
	- [4.2 Visual Feedback](#4.2%20Visual%20Feedback)
	- [4.3 Exit Time](#4.3%20Exit%20Time)
	- [4.4 Intrusion Deterrent](#4.4%20Intrusion%20Deterrent)
	- [4.5 Quick Disarming](#4.5%20Quick%20Disarming)
- [5. Validation Summary](#5.%20Validation%20Summary)
	- [5.1 Requirement Fulfillment](#5.1%20Requirement%20Fulfillment)
	- [5.2 Success Criteria](#5.2%20Success%20Criteria)

## 1. Requirements Validation

This document validates that the implemented system meets the original project requirements defined in the analysis phase.

## 2. Functional Requirements

### 2.1 Motion Detection

**Requirement:** Detect motion when system is armed

**Status:** Validated

**Evidence:**
- PIR sensor successfully detects movement in coverage area
- Detection range adequate for room-sized spaces (4-5 meters)
- System only monitors motion when in ARMED state
- Clear visual feedback (LED) during detection

---

### 2.2 Visual and Audible Alerts

**Requirement:** Provide visual and audible alerts when triggered

**Status:** Validated

**Evidence:**
- Buzzer produces loud, attention-grabbing alarm (alternating 880/1320 Hz)
- LED flashes synchronized with audio
- Alarm continues until manually disarmed

---

### 2.3 System Status Display

**Requirement:** Display system status on LCD screen

**Status:** Validated

**Evidence:**
- Current state always visible on LCD
- Clear instructions provided for each state
- Motion detection feedback shown in real-time
- Countdown timers display correctly

---

### 2.4 Manual Arming/Disarming

**Requirement:** Allow manual arming and disarming via button

**Status:** Validated

**Evidence:**
- Single button controls all state transitions
- Context-aware functionality (different behavior per state)
- Confirmation feedback for all actions
- Simple, intuitive operation

---

### 2.5 Arming Countdown

**Requirement:** Implement countdown timer before arming

**Status:** Validated

**Evidence:**
- 5-second countdown provides exit time
- Visual countdown on LCD (5-4-3-2-1)
- Audio beep each second
- Final confirmation when armed

---

### 2.6 False Trigger Prevention

**Requirement:** Prevent false triggers with detection delay

**Status:** Validated

**Evidence:**
- 5-second sustained detection requirement
- Effectively filters sensor reset behavior (3-second reset + 2-second margin)
- Brief movements do not trigger alarm
- No false alarms during testing period

---

### 2.7 Clear State Transitions

**Requirement:** Maintain clear state transitions between modes

**Status:** Validated

**Evidence:**
- Three distinct states: DISARMED, ARMED, TRIGGERED
- Explicit state variable controls system behavior
- Predictable transitions with clear triggers
- No unexpected state changes or errors

---

## 3. Non-Functional Requirements

### 3.1 Reliability

**Requirement:** Consistent motion detection without false positives

**Status:** Validated

**Evidence:**
- False trigger prevention algorithm effective
- No false alarms during multiple test sessions
- Sustained detection requirement filters environmental noise
- System stable over multiple arm/disarm cycles

**Limitation:** Long-term reliability (24+ hours) not tested

---

### 3.2 Usability

**Requirement:** Simple one-button operation for arm/disarm functionality

**Status:** Validated

**Evidence:**
- Single button interface easy to understand
- Clear instructions displayed for each action
- Minimal learning curve (< 1 minute to understand)
- No confusion about system operation

**User Feedback:** Interface intuitive for shared living space context

---

### 3.3 Performance

**Requirement:** Immediate response to motion detection events

**Status:** Validated

**Evidence:**
- Motion detected within sensor capabilities (~1 second)
- LED provides immediate visual feedback
- Alarm triggers after 5-second validation (by design)
- Button response within 100ms polling interval

**Acceptable:** 5-second delay intentional for false positive prevention

---

### 3.4 Accessibility

**Requirement:** Clear visual feedback through LCD display and LED

**Status:** Validated

**Evidence:**
- LCD messages readable from 2-3 meters
- LED visible in various lighting conditions
- Audio feedback provides redundant information
- Multi-modal feedback (visual + audio + text)

---

### 3.5 Power Efficiency

**Requirement:** Continuous operation as background monitoring system

**Status:** Partially Validated

**Evidence:**
- System runs continuously on USB power
- ESP32 power consumption acceptable
- No excessive heating during operation

**Limitation:** Battery backup not implemented;

---

## 4. User Stories Validation

### 4.1 Room Protection

**User Story:** "As a student, I want to arm my room when leaving, so my belongings are protected."

**Status:** Validated

**Evidence:**
- Arming sequence provides 5+ seconds to exit room
- Motion detection covers entry points effectively
- Alarm deters unauthorized entry
- Simple operation suitable for daily use

---

### 4.2 Visual Feedback

**User Story:** "As a resident, I want clear visual feedback on system status, so I know when the alarm is active."

**Status:** Validated

**Evidence:**
- LCD always displays current state
- "Armed" message clearly visible
- Motion detection shown on second LCD line
- No ambiguity about system status

---

### 4.3 Exit Time

**User Story:** "As a user, I want a countdown before arming, so I have time to exit the room."

**Status:** Validated

**Evidence:**
- 5-second countdown adequate for room exit
- Visual and audio countdown feedback
- Total exit time ~5.75 seconds including delays
- No users locked out during testing

---

### 4.4 Intrusion Deterrent

**User Story:** "As a shared space user, I want an audible alarm, so intruders are deterred and others are alerted."

**Status:** Validated

**Evidence:**
- Alarm loud enough to hear in adjacent rooms
- Alternating tone pattern attention-grabbing
- Continuous alarm until manually disarmed
- Effective deterrent for unauthorized entry

---

### 4.5 Quick Disarming

**User Story:** "As a roommate, I want easy disarming, so I can quickly disable false alarms."

**Status:** Validated

**Evidence:**
- Single button press disarms immediately
- Alarm stops within 200ms of button press
- Simple operation reduces frustration

**Future Enhancement:** PIN protection would improve security

---

## 5. Validation Summary

### 5.1 Requirement Fulfillment

| Category | Requirements | Validated | Percentage |
|----------|--------------|-----------|------------|
| Functional | 7 | 7 | 100% |
| Non-Functional | 5 | 4 | 80% |
| User Stories | 5 | 5 | 100% |
| **Total** | **17** | **16** | **94%** |

**Note:** Power efficiency partially validated due to lack of battery backup testing.

---

### 5.2 Success Criteria

**Project successfully meets its goals:**

- [x] **Functionality:** All core alarm system features working as designed
- [x] **Usability:** Simple, intuitive interface suitable for target users
- [x] **Reliability:** False trigger prevention effective, stable operation

**Overall Assessment:** The Student Accommodation Alarm System successfully meets all primary requirements for a basic security solution in shared living spaces.