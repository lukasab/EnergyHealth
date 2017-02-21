byte aRainPin = A1;
byte dRainPin = 6;

void setup() {
  pinMode(aRainPin, INPUT);
  pinMode(dRainPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int aSensorValue = analogRead(aRainPin);
  byte dSensorValue = digitalRead(dRainPin);
  Serial.print("Analog Value: ");
  Serial.println(aSensorValue);
  Serial.print("Digital Value: ");
  Serial.println(dSensorValue);
  delay(300);
}
