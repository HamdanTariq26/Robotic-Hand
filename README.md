# 🎮 Gesture Controlled Robotic Arm (MPU6050 + Arduino)

This project implements a **gesture-controlled robotic arm** using an Arduino, an MPU6050 accelerometer/gyroscope sensor, and multiple servo motors. The arm movements are controlled by tilting the sensor, while a button controls the gripper.

---

## 📌 Features

- 🎯 Real-time gesture control using MPU6050
- 🦾 4-DOF robotic arm control:
  - Forward / Backward
  - Up / Down
  - Left / Right
  - Gripper control (open/close via button)
- ⚡ Smooth servo movement (filtered transitions)
- 🔄 Continuous sensor reading via I2C (Wire library)

---

## 🧠 Working Principle

The system reads **accelerometer data from MPU6050**, converts it into angular orientation, and maps those angles to servo positions.

- Tilting the sensor changes X, Y, Z orientation
- Each axis controls a specific servo motor
- A push button toggles the gripper state

---

## 🛠️ Hardware Requirements

- Arduino Uno / Nano
- MPU6050 Accelerometer + Gyroscope
- 4 × Servo Motors
- Push Button
- Jumper Wires
- External Power Supply (recommended for servos)

---

## 🔌 Pin Configuration

| Component | Arduino Pin |
|-----------|------------|
| Servo 1 (Forward/Backward) | 4 |
| Servo 2 (Up/Down) | 3 |
| Servo 3 (Gripper) | 2 |
| Servo 4 (Left/Right) | 5 |
| Button | 8 |
| MPU6050 | SDA/SCL (A4/A5 on Uno) |

---

## 📦 Libraries Used

- `Wire.h` → I2C communication with MPU6050  
- `Servo.h` → Servo motor control  

---

## ⚙️ How It Works

### 1. Sensor Initialization
- MPU6050 is initialized over I2C (address `0x68`)
- Gyroscope/accelerometer values are read continuously

### 2. Angle Mapping
Raw sensor values are mapped into angular values:

- X-axis → Left/Right movement
- Y-axis → Up/Down movement
- Z-axis → Forward/Backward movement

### 3. Servo Control
Each angle is converted into servo position (0–180° range)

### 4. Smooth Motion
Servo movement is smoothed using incremental steps to avoid jerks.

### 5. Gripper Control
- Button pressed → Gripper closes
- Button released → Gripper opens

---

## 🚀 Code Structure

- `setup()` → Initializes sensors and servos  
- `loop()` → Reads sensor data and updates servo positions  
- `updateMPU()` → Reads and processes MPU6050 data  
- `moveSmooth()` → Smoothly transitions servo positions  

---

## 📷 Project Overview

> A gesture-based robotic arm system that mimics human hand movements using sensor orientation.

---

## 🔧 Possible Improvements

- Add wireless control (Bluetooth / ESP module)
- Implement PID-based smooth control
- Add inverse kinematics for precise movement
- Upgrade to 6-DOF robotic arm

---

## 📜 License

This project is open-source and free to use for educational purposes.

---

## 👨‍💻 Author

Developed as a robotics and embedded systems learning project using Arduino and sensor-based control systems.
