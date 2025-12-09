# Advice

**Name:** Aleksandar Rangelov
**Student Number:** 572601

## Table of Contents

- [1. Future Enhancements](#1.%20Future%20Enhancements)
- [2. Configuration Optimization](#2.%20Configuration%20Optimization)
- [3. Code Improvements](#3.%20Code%20Improvements)

The foundation laid out with the completion of this project allows for several new features to be implemented. This document aims to list all some of the future features that could be implemented into the project.

### 1. Future Enhancements

**Wireless Connectivity:**
- Utilize ESP32's Wi-Fi for remote notifications
- Mobile app integration for arm/disarm
- Remote monitoring of alarm status
- SMS or email alerts when triggered

**Enhanced Security:**
- PIN code entry via keypad
- Multiple sensor zones
- Event logging to SD card
- Tamper detection
- 3d printed housing for sensors and central unit

**User Experience:**
- Adjustable sensitivity settings
- Customizable alarm tones
- Entry delay before alarm sounds
- Scheduled arming/disarming

### 2. Configuration Optimization

The current state of the project don't need configurable variables and delays for the different states of the alarm. However, here are the hardcoded values could could be made configurable:

- Detection delay duration (currently 5000ms)
- Arming countdown time (currently 5 seconds)
- Buzzer frequencies and patterns
- Button debounce timing

### 3. Code Improvements

- Implement proper button debouncing algorithm
- Add non-blocking delays for better responsiveness
- Extract magic numbers to named constants
- Add comprehensive error handling
- Implement watchdog timer for reliability

### 4. Conclusion

In conclusion, the platform built by this project allows for a plethora future enhancements. If the client is to upgrade their product, this should be the areas that he should improve.