int sensor2 = 2; // sensor pin
int val2; // 0: Magnetic field detected, 1: No magnetic field detected

void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
  pinMode(sensor2, INPUT); // set sensor pin as input
}

void loop() {
  val2 = digitalRead(sensor2); // Read the sensor

  if(val2==1) {
    Serial.println("Magnet Not Detected");
  }
  else {
    Serial.println("Magnet Detected");
  }

  delay(100);
}