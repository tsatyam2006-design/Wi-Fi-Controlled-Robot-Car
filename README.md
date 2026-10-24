# Wi-Fi-Controlled-Robot-Car

  Project: Wi-Fi Controlled Robot Car with Dual Motor Drivers
  
  Description:
  This project demonstrates how to build a Wi-Fi-controlled robot car using an ESP32, two L298N motor drivers, 
  and a simple web interface. The robot can move forward, backward, left, and right, and stop upon receiving 
  commands from the web interface.

  Features:
  1. Dual motor driver setup for controlling four DC motors.
  2. Speed control for motors using PWM signals.
  3. Web-based control interface for real-time commands over Wi-Fi.
  4. Easily extendable for additional functionalities like maze solving or line following.

  Components:
  - ESP32 microcontroller
  - Two L298N motor drivers
  - Four DC motors
  - Power supply
  - Wi-Fi connection
  
  Pins and Connections:
  
  Motor Driver 1:
  - ENA1, ENB1: Speed control for Right and Left motors (PWM pins)
  - IN_1_1, IN_2_1: Direction control for Right motor
  - IN_3_1, IN_4_1: Direction control for Left motor
  
  Motor Driver 2:
  - ENA2, ENB2: Speed control for Right and Left motors (PWM pins)
  - IN_1_2, IN_2_2: Direction control for Right motor
  - IN_3_2, IN_4_2: Direction control for Left motor

  Wi-Fi Details:
  - SSID: Wifi_Robot_Car
  - Password: 12345678
