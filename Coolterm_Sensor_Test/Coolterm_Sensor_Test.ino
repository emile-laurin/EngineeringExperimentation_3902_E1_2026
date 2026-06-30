

// Global variables and pin definitions
// Define the pins for the HC-SR04 sensor
const int trigPin2 = 4; // Pin that triggers the ultrasonic pulse
const int echoPin2 = 2; // Pin that receives the echo signal

// Variables to store the pulse duration and calculated distance
float duration2, distance2;


void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
  // Setup function: runs once at startup
  // Configure the trigger pin as an OUTPUT and the echo pin as an INPUT
  pinMode(trigPin2, OUTPUT); // Set trigger pin as output
  pinMode(echoPin2, INPUT);  // Set echo pin as input

  Serial.print("Time in Milliseconds");
  Serial.print(",");
  Serial.println("Distance: ");
}


void loop() {
  // Main loop: continuously measures distance

  // Ensure the trigger pin is LOW to start
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2); // Short delay to allow sensor stabilization

  // Trigger the sensor by sending a HIGH pulse for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Pulse duration
  digitalWrite(trigPin2, LOW);

  // Read the duration of the echo pulse (in microseconds)
  duration2 = pulseIn(echoPin2, HIGH);

  // Calculate the distance (cm) using the speed of sound (0.0343 cm/us)
  // Dividing by 2 accounts for the round-trip distance
  distance2 = (duration2 * 0.0343) / 2;

  // Output the measured distance to the Serial Monitor

  Serial.print(millis());
  Serial.print(";");
  Serial.println(distance2);

  // Short delay before the next measurement
  delay(100);
}