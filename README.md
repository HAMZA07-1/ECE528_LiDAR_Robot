# Autonomous LiDAR-Based Navigation Robot

**ECE 528/L – Robotics and Embedded Systems (Final Project)**  
**Instructor:** Aaron Nanas  
**Authors:** Hamza Sulehria, Leo Issaghoulian  
**California State University, Northridge**  
**Department of Electrical and Computer Engineering**

---

## 1. Project Overview

This project presents the design and implementation of an autonomous mobile robot capable of performing obstacle detection and navigation using LiDAR-based sensing and embedded motor control.

The system integrates a **TI-RSLK MAX robotic platform (MSP432 microcontroller)** with a **Raspberry Pi 4** to achieve a layered control architecture. The Raspberry Pi performs high-level perception and decision-making using LiDAR data, while the MSP432 executes real-time motor control using PWM and GPIO signals.

The primary objective is to demonstrate a functional perception-to-actuation pipeline using real-time sensor input and embedded control.

---

## 2. System Architecture

The system is divided into two tightly coupled subsystems:

### 2.1 Raspberry Pi (High-Level Control Layer)

- Interfaces with the **RPLIDAR C1** sensor via USB  
- Acquires 360° polar scan data  
- Segments scan data into directional regions:
  - Front sector (0° ± threshold)
  - Left sector (~90°)
  - Right sector (~270°)
- Applies threshold-based decision logic to classify regions as **open** or **blocked**
- Generates navigation commands (`F, L, R, B, U, S`)
- Transmits commands to MSP432 via UART  

---

### 2.2 MSP432 (Low-Level Control Layer)

- Receives UART commands from Raspberry Pi  
- Controls DC motors using:
  - **PWM (Timer_A0)** for speed control  
  - **GPIO** for direction control  
- Executes discrete motion primitives:
  - Forward motion
  - Left turn
  - Right turn
  - Reverse
  - 180° turn (U-turn)
  - Stop
- Based on TI-RSLK MAX motor control framework (ECE 528 Lab 1)

---

## 3. Control Flow

The system operates in a continuous perception–action loop:

1. LiDAR acquires environment data  
2. Raspberry Pi processes scan and computes distances  
3. Navigation logic determines next action  
4. Command is sent via UART  
5. MSP432 executes motor command  
6. Loop repeats  

This architecture ensures separation between computational tasks and real-time control.

---

## 4. Navigation Algorithm

The navigation strategy is based on **threshold-based reactive control**:

- If front distance > threshold → **Move Forward**
- Else:
  - If right side more open → **Turn Right**
  - Else if left side more open → **Turn Left**
  - Else → **Turn Around**

This approach approximates wall-following behavior without requiring full SLAM or mapping.

---

## 5. Experimental Setup

Testing was conducted in a controlled environment:

- A **three-wall enclosure** was used to simulate obstacle constraints  
- The robot demonstrates:
  - Obstacle detection
  - Directional decision-making
  - Reactive navigation behavior  

> Full maze implementation is a future extension.

---

## 6. Hardware Components

| Component | Function |
|----------|----------|
| TI-RSLK MAX (MSP432) | Embedded motor control platform |
| MSP432P401R LaunchPad | Microcontroller |
| Raspberry Pi 4 | High-level processing |
| RPLIDAR C1 | 360° distance sensing |
| DC Motors | Locomotion |
| Battery Pack | Power supply |
| Jumper Wires | UART and ground connections |

---

## 7. UART Communication

| Signal | MSP432 Pin | Raspberry Pi Pin | Description |
|--------|------------|------------------|-------------|
| TX | P3.2 | GPIO15 (RXD) | MSP432 → Raspberry Pi |
| RX | P3.3 | GPIO14 (TXD) | Raspberry Pi → MSP432 |
| GND | GND | GND | Common reference |

Communication uses single-character command encoding.

---

## 8. Repository Structure

```text
ECE528_LiDAR_Robot/
├── README.md
├── ece-528l-motor-control-HAMZA07-1-main/
│   └── Complete MSP432 CCS project
├── raspberry_pi/
│   ├── lidar_navigation.py
│   └── test_uart.py
├── images/
│   ├── block_diagram.png
│   └── state_diagram.png
├── report/
│   └── Final report
└── demo/
    └── Demo links
