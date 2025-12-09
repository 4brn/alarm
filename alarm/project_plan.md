# Project Plan

**Student name**: Aleksandar Rangelov
**Student number**: 572601

## Table of Content

- [1. Introduction](#1.%20Introduction)
- [2. Objective](#2.%20Objective)
- [3. Main question](#3.%20Main%20question)
- [4. MoSCoW method](#4.%20MoSCoW%20method)
	- [4.1 Must have](#4.1%20Must%20have)
	- [4.2 Should have](#4.2%20Should%20have)
	- [4.3 Could have](#4.3%20Could%20have)
	- [4.4 Won't have](#4.4%20Won't%20have)
- [5. SWOT Analysis](#5.%20SWOT%20Analysis)
	- [5.1 Strengths](#5.1%20Strengths)
	- [5.2 Weaknesses](#5.2%20Weaknesses)
	- [5.3 Opportunities](#5.3%20Opportunities)
	- [5.4 Threats](#5.4%20Threats)
- [6. Stakeholders](#6.%20Stakeholders)
	- [6.1 PI matrix](#6.1%20PI%20matrix)
- [7. Planning](#7.%20Planning)
	- [7.1 Analysis](#7.1%20Analysis)
	- [7.2 Design](#7.2%20Design)
	- [7.3 Realisation](#7.3%20Realisation)
- [8. Conclusion](#8.%20Conclusion)


## 1. Introduction

The aim of the project is to create an alarm system for students, victims of stealing and invasion of personal space in their rooms. The provided solution will allow for motion detection and audio alarming of unauthorized access. 

## 2. Objective

> The main objective is to create a lightweight and user-friendly alarm system.

The system will:

- **Detect motion**: Detect motion using a motion sensor
- **Minimize device size & weight**: Lightweight and small device would allow for its usage in tight, small spaces like wardrobes, fridges and cabinets, as well ass rooms and halls.
- **Maximize simplicity and user Experience**: Intuitive dispaly information and sinble button operations allow for a seamless easy use of the device

## 3. Main question

> How to detect unauthorized access in environments varying in size?

## 4. MoSCoW method

### 4.1 Must have

- Motion detection
- Audio siren
- Arm and disarm funcitonality

### 4.2 Should have

- Display of information
- Compact size
- Efficient power delivery

### 4.3 Could have

- Wireless control 
- Notifications
- Volume control

### 4.4 Won't have

- industry standard PCB usage

## 5. SWOT Analysis

### 5.1 Strengths

- Real-time motion detection
- Compact size
- Ease of use
- Ease of assembly
- Low power draw
- Versatile usability

### 5.2 Weaknesses

- Lack of functionality
- Single device design
- Basic information visualization

### 5.3 Opportunities

- Add more metric functionality
- Lower size footprint
- Improve user usage & experience

### 5.4 Threats

- Short circuits
- Crashes

## 6. Stakeholders

### 6.1 PI matrix

![](PIMatrix.png)

## 7. Planning

Each estimation includes buffer time for unexpected issues, research and learning. 

### 7.1 Analysis

| **Task**                  | **Estimated Time** |
| ------------------------- | ------------------ |
| Collect requirements      | -                  |
| Research microcontrollers | 1 h                |
| Research sensors          | 1 h                |
| Documentation             | 4 h                |
| Total                     | 6 h                |

### 7.2 Design

| **Task**             | **Estimated Time** |
| -------------------- | ------------------ |
| Design PCB structure | 1 h                |
| Design alarm logic   | 4 h                |
| Documentation        | 3 h                |
| Total                | 8 h                |

### 7.3 Realisation

| **Task**                          | **Estimated Time** |
| --------------------------------- | ------------------ |
| Set up project                    | 1 h                |
| Wire sensors                      | 2 h                |
| Implement all sensor functinality | 5 h                |
| Implement state machine           | 3 h                |
| Refine implementation             | 4 h                |
| Test on local machine             | 2 h                |
| Fix bugs                          | 2 h                |
| Documentation                     | 5 h                |
| Total                             | 24 h               |

## 8. Conclusion

This project will result in a proof-of-concept alarm system while developing valuable skills in embedded systems. The 4-week timeline is aggressive but achievable with proper time management. The system will serve as a foundational tool for ongoing embedded systems products and can be extended with additional features in the future.