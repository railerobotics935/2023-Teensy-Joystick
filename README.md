# 2023-Teensy-Joystick

Application to use a Teensy 4.0 as custom joystick controller for the robot. The Teensy connects through USB to the robot control laptop and is recognized by the dashboard as a generic HID joystick controller.

## Materials:

1) Teensy 4.0 board
2) Teensyduino (Arduino with Teensy extensions)
3) Custom made Joystick, uses 4 potentiometers (5 kOhm each) from a Logitech joystick and 2 switches

## Teensyduino/Arduino configuration:

1) Open "2023-Teensy-Joystick.ino" in the Arduino environment
2) Select "Teensy 4.0" as "Board" in the tools menu
3) Configure "USB Type" in tools menu as: "Keyboard + Mouse + Joystick" or "Serial + Keyboard + Mouse + Joystick"
4) Connect Teensy to PC USB port, select the serial port of the Teensy and upload the sketch
