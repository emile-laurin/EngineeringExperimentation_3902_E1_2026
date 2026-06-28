void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
	pinMode(LED1_Pin, OUTPUT); // Set the LED anode pin as an output
}


void loop() {
  digitalWrite(LED1_Pin, HIGH); // Turn the LED on
  delay(1000); // Wait for 1 second
  digitalWrite(LED1_Pin, LOW); // Turn the LED off
  delay(1000); // Wait for 1 second before repeating
}
