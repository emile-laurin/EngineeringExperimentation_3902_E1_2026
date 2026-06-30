#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_VL53L0X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define IR 7

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Global variables and pin definitions
// Define the pins for the HC-SR04 sensor
const int trigPin5 = 4; // Pin that triggers the ultrasonic pulse
const int echoPin5 = 2; // Pin that receives the echo signal

// Variables to store the pulse duration and calculated distance
float duration5, distance5;
int detection = HIGH; // no obstacles

void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);

  // Setup function: runs once at startup
  // Configure the trigger pin as an OUTPUT and the echo pin as an INPUT
  pinMode(trigPin5, OUTPUT); // Set trigger pin as output
  pinMode(echoPin5, INPUT);  // Set echo pin as input
  pinMode(IR, INPUT); // Set IR sensor pin as input

  //Initialize the sensor
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1); // Stop program if sensor cannot be initialized
  }

  // OLED Setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
     Serial.println("SSD1306 Allocation failed");
     while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {
  // Main loop: continuously measures distance

  // Ensure the trigger pin is LOW to start
  digitalWrite(trigPin5, LOW);
  delayMicroseconds(2); // Short delay to allow sensor stabilization

  // Trigger the sensor by sending a HIGH pulse for 10 microseconds
  digitalWrite(trigPin5, HIGH);
  delayMicroseconds(10); // Pulse duration
  digitalWrite(trigPin5, LOW);

  // Read the duration of the echo pulse (in microseconds)
  duration5 = pulseIn(echoPin5, HIGH);

  // Calculate the distance (cm) using the speed of sound (0.0343 cm/us)
  // Dividing by 2 accounts for the round-trip distance
  distance5 = (duration5 * 0.0343) / 2;

  // Output the measured distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance5);

  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // Pass in 'true' to get debug data printout

  if (measure.RangeStatus != 4) { // Phase failures have incorrect data
    Serial.print("Distance: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
  }
  else {
    Serial.println("out of range");
  }

  // Output the IR readings
  Serial.println(digitalRead(IR));
  detection = digitalRead(IR);
  if(detection == LOW){
    Serial.print("Obstacle");
  }
  else{
    Serial.print("No obstacle");
  }

  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,0);
  display.print("US: ");
  display.print(distance5);
  display.println(" cm");

  display.setCursor(0,16);
  display.println("ToF: ");
  display.print(measure.RangeMilliMeter);
  display.println(" mm");

  display.setCursor(0,32);
  if(detection == LOW){
    display.println("Obstacle");
  }
  else{
    display.println("No obstacle");
  }

  display.display();
  
  // Delay to avoid flooding the serial output
  delay(500);
}
