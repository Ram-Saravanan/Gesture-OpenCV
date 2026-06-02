# Hand Gesture Controlled Volume and LED Brightness System

A computer vision project that enables touchless control of system volume and LED brightness using hand gestures. The system uses MediaPipe for hand tracking, OpenCV for video processing, and Arduino for hardware control.

## Features

- Real-time hand gesture recognition
- System volume control using left-hand gestures
- LED brightness control using right-hand gestures
- Python-Arduino serial communication
- PWM-based brightness adjustment

## Tech Stack

- Python
- OpenCV
- MediaPipe
- PyAutoGUI
- PySerial
- Arduino Uno

## Gesture Mapping

### Right Hand (LED Brightness)

| Gesture | Brightness |
|----------|------------|
| Fist | 0% |
| 1 Finger | 25% |
| 2 Fingers | 50% |
| 3 Fingers | 75% |
| 4 Fingers | 100% |

### Left Hand (Volume Control)

| Gesture | Action |
|----------|---------|
| 1 Finger Up | Volume Up |
| 2 Fingers Up | Volume Down |

## Demo

Music Control <img width="1119" height="673" alt="image" src="https://github.com/user-attachments/assets/bb21b187-34bb-4a0b-a0fb-3ae23e9a752a" />

Brightness Control <img width="1308" height="719" alt="image" src="https://github.com/user-attachments/assets/47a4912e-67d9-4949-ba3e-c77cf205e0f1" />

Hardware Components <img width="1280" height="720" alt="image" src="https://github.com/user-attachments/assets/68ea555f-d25e-4d9f-91da-9b03f174556d" />


## Run

```bash
pip install -r requirements.txt
python main.py
