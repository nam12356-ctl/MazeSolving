# Arduino Wall Following Robot

This project involves building a wall-following robot using ultrasonic sensors and an Arduino board. The robot autonomously navigates along a wall, avoiding obstacles and adjusting its direction as needed.

## Components Required:

- **Arduino Uno** or any compatible Arduino board
- **HC-SR04 Ultrasonic Sensors**
- **DC Motors** (controlled via L298N motor driver or similar)
- **Power Supply** (battery or adapter)
- **Jumper wires, wheels, robot chassis**

## Wiring Connections:

### Ultrasonic Sensors:
- **Front Trig**: Pin 7
- **Front Echo**: Pin 4
- **Left Trig**: Pin 3
- **Left Echo**: Pin 2
- **Right Trig**: Pin 13
- **Right Echo**: Pin 12

### Motor Control:
- **ENA**: Pin 6
- **IN1**: Pin 11
- **IN2**: Pin 10
- **IN3**: Pin 9
- **IN4**: Pin 8
- **ENB**: Pin 5
![image](https://github.com/user-attachments/assets/82013939-ddde-4d5c-8f3a-49374c680720)
## Instructions:

1. Download and install **Arduino IDE** if you haven't already.
2. Connect the Arduino board to your computer and select the correct board and port in Arduino IDE.
3. Open the `wall_following.ino` file in the Arduino IDE.
4. Upload the code to the Arduino board.
5. Power on the robot and place it on the ground to start testing.

## License

This code is licensed under the **MIT License** - See the full details at [LICENSE](LICENSE).
