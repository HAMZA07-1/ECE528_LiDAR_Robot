# Autonomous LiDAR-Based Navigation Robot

**ECE 528/L – Robotics and Embedded Systems (Final Project)**  
**Instructor:** Aaron Nanas  
**Authors:** Hamza Sulehria, Leo Issaghoulian  
**California State University, Northridge**  
**Department of Electrical and Computer Engineering**

---

## Introduction

This project implements an autonomous mobile robot that combines embedded motor control with LiDAR-based obstacle detection. The robot uses the TI-RSLK MAX platform with the MSP432 microcontroller for low-level motor control and a Raspberry Pi 4 for high-level LiDAR processing and navigation decisions.

The project demonstrates a modular robotics architecture where the Raspberry Pi acts as the perception and decision-making layer, while the MSP432 acts as the real-time motion control layer.

---

## System Overview

The robot is divided into two main subsystems.

### Raspberry Pi LiDAR Subsystem

- Interfaces with the RPLIDAR C1 sensor through USB
- Reads 360-degree LiDAR scan data
- Divides scan data into front, left, and right detection zones
- Applies threshold-based navigation logic
- Sends movement commands to the MSP432 through UART

### MSP432 Embedded Control Subsystem

- Receives movement commands from the Raspberry Pi
- Controls the TI-RSLK motors using PWM and GPIO
- Executes robot movements such as forward, left, right, reverse, turn-around, and stop
- Uses the TI-RSLK motor control framework from the ECE 528 motor control lab

---

## Demo Summary

The current demo was tested in a controlled three-wall enclosure instead of a full maze. The robot detects nearby walls using LiDAR and makes simple navigation decisions.

Current behavior:

- Move forward when the front path is clear
- Turn when an obstacle is detected
- Stop or reverse when needed
- Demonstrate basic autonomous wall-avoidance behavior

Full maze testing is planned as a future improvement.

---

## Command Protocol

The Raspberry Pi sends single-character UART commands to the MSP432.

| Command | Action |
|--------|--------|
| F | Move Forward |
| L | Turn Left |
| R | Turn Right |
| B | Reverse |
| U | Turn Around |
| S | Stop |

---

## Hardware Components

| Component | Purpose |
|----------|---------|
| TI-RSLK MAX Robot | Robot chassis, motors, and MSP432 platform |
| MSP432P401R LaunchPad | Low-level embedded motor control |
| Raspberry Pi 4 | LiDAR processing and navigation logic |
| RPLIDAR C1 | 360-degree distance sensing |
| DC Motors | Robot movement |
| Battery Pack | Robot power |
| Jumper Wires | UART and ground connections |

---

## UART Wiring

| Signal | MSP432 Pin | Raspberry Pi Pin | Description |
|--------|------------|------------------|-------------|
| MSP432 TX | P3.2 | GPIO15 / RXD | MSP432 to Raspberry Pi |
| MSP432 RX | P3.3 | GPIO14 / TXD | Raspberry Pi to MSP432 |
| GND | GND | GND | Shared ground |

---

## Block Diagram

Image placeholder:

`images/block_diagram.png`

![Block Diagram](images/block_diagram.png)

---

## State Diagram

Image placeholder:

`images/state_diagram.png`

![State Diagram](images/state_diagram.png)

---

## Repository Structure

```text
ECE528_LiDAR_Robot/
├── README.md
├── ece-528l-motor-control-HAMZA07-1-main/
│   └── Complete MSP432 Code Composer Studio project
├── raspberry_pi/
│   ├── lidar_navigation.py
│   └── test_uart.py
├── images/
│   ├── block_diagram.png
│   └── state_diagram.png
├── report/
│   └── Final report files
└── demo/
    └── Demo links and notes

Then push the update:

```bash
git add README.md
git commit -m "Improve README formatting and project documentation"
git push

hamzasulehria@Hamzas-MacBook-Pro-5 ECE528_Final_Project % 

