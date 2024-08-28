This is a Hand gesure based OpenCV project that simulates volume control and led brightness control (with arduino interface)

OpenCV, Mediapipe and PyAutoGUI are the main python libraries I used for this project.
- OpenCV for video detection
- Mediapipe for hand gesture detection
- PyAutoGUI for simulating control

This code assigns right hand gestures for led brightness control 
- hands closed, 1, 2, and 3 fingers corresponds to 25% 50% 75% and 100% brightness of the led.
- Led on arduino ~9 pwm pin

The left hand gestures for volume control 
- 1 finger up increases the volume
- 2 fingers up decreases the volume
