import cv2
import serial
import pyautogui
import mediapipe as mp

try:
    arduino = serial.Serial('COM9', 9600)  # Ensure correct COM port
except serial.SerialException:
    print("Could not open serial port. Please check the connection.")
    exit()

mp_hands = mp.solutions.hands
hands = mp_hands.Hands(static_image_mode=False, max_num_hands=2,
                       min_detection_confidence=0.5, min_tracking_confidence=0.5)

cap = cv2.VideoCapture(0)

last_brightness = 0
finger_count_stable = 0
stable_count_threshold = 5  # Start with threshold 5

def count_fingers(hand_landmarks):
    """Function to count the number of extended fingers."""
    finger_tips = [
        mp_hands.HandLandmark.THUMB_TIP,
        mp_hands.HandLandmark.INDEX_FINGER_TIP,
        mp_hands.HandLandmark.MIDDLE_FINGER_TIP,
        mp_hands.HandLandmark.RING_FINGER_TIP,
        mp_hands.HandLandmark.PINKY_TIP
    ]

    finger_pips = [
        mp_hands.HandLandmark.THUMB_IP,
        mp_hands.HandLandmark.INDEX_FINGER_PIP,
        mp_hands.HandLandmark.MIDDLE_FINGER_PIP,
        mp_hands.HandLandmark.RING_FINGER_PIP,
        mp_hands.HandLandmark.PINKY_PIP
    ]

    count = 0
    for tip, pip in zip(finger_tips, finger_pips):
        if hand_landmarks.landmark[tip].y < hand_landmarks.landmark[pip].y:  
            count += 1
    return count

while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to capture frame. Exiting...")
        break

    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = hands.process(frame_rgb)

    if results.multi_hand_landmarks:
        for hand_landmarks, hand_classification in zip(results.multi_hand_landmarks, results.multi_handedness):
            hand_label = hand_classification.classification[0].label

            if hand_label == 'Left':
                # Left hand controls brightness
                finger_count = count_fingers(hand_landmarks)

                if finger_count == finger_count_stable:
                    stable_count_threshold -= 1
                else:
                    finger_count_stable = finger_count
                    stable_count_threshold = 5  # Reset threshold if finger count changes

                if stable_count_threshold == 0:
                    if finger_count_stable == 0:
                        brightness = 0   
                    elif finger_count_stable == 1:
                        brightness = 70
                    elif finger_count_stable == 2:
                        brightness = 100
                    elif finger_count_stable == 3:
                        brightness = 150
                    elif finger_count_stable == 4:
                        brightness = 253 
                    elif finger_count_stable == 5:
                        brightness = 0

                    if brightness != last_brightness:
                        try:
                            arduino.write(f"{brightness}\n".encode())
                        except serial.SerialException:
                            print("Error writing to serial port.")
                        last_brightness = brightness

            elif hand_label == 'Right':
                # Right hand controls volume based on finger count
                finger_count = count_fingers(hand_landmarks)

                if finger_count == 2:
                    pyautogui.press('volumeup')
                elif finger_count == 3:
                    pyautogui.press('volumedown')

            mp.solutions.drawing_utils.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

    else:
        try:
            arduino.write(f"{last_brightness}\n".encode())
        except serial.SerialException:
            print("Error writing to serial port.")

    cv2.imshow('Hand Gesture & Brightness Control', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()
