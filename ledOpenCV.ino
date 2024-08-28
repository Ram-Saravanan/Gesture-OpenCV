int relayPin = 9;  // Pin connected to relay

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    if (command == "OFF") {
      digitalWrite(relayPin, LOW);  // Turn off the light
    } else {
      int brightness = command.toInt();
      analogWrite(relayPin, brightness);  // Adjust brightness
    }
  }
}
