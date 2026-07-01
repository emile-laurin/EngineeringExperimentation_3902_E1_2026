#include <Stepper.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

//1.8 degree step angle = 200 steps per revolution

const int StepsPerRev = 1000;
int sensor2 = 9; // sensor pin
int val2; // 0: Magnetic field detected, 1: No magnetic field detected

// Define the pins for the HC-SR04 sensor
const int trigPin2 = 8; // Pin that triggers the ultrasonic pulse
const int echoPin2 = 9; // Pin that receives the echo signal

// Variables to store the pulse duration and calculated distance
float duration2, distance2;

//Initializing Stepper Library
//(steps,AIN1,AIN2,BIN1,NIN2)
Stepper nema17Stepper(StepsPerRev,5,4,6,7);

void setup() {
  // put your setup code here, to run once:

  // Configure the trigger pin as an OUTPUT and the echo pin as an INPUT
  pinMode(trigPin2, OUTPUT); // Set trigger pin as output
  pinMode(echoPin2, INPUT);  // Set echo pin as input

  //Set motor speed in rmp
  nema17Stepper.setSpeed(10);

  Serial.begin(9600);
  Serial.println("NEMA 17 is initialized with TB6612");

  pinMode(sensor2, INPUT); // set sensor pin as input
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("Moving CW");
  nema17Stepper.step(StepsPerRev);

  val2 = digitalRead(sensor2); // Read the sensor

  if(val2==1) {
    Serial.println("Magnet Not Detected");
  }
  else {
    Serial.println("Magnet Detected");
  }

  // Ensure the trigger pin is LOW to start
  digitalWrite(trigPin2, LOW);

  // Trigger the sensor by sending a HIGH pulse for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin2, LOW);

  // Read the duration of the echo pulse (in microseconds)
  duration2 = pulseIn(echoPin2, HIGH);

  // Calculate the distance (cm) using the speed of sound (0.0343 cm/us)
  // Dividing by 2 accounts for the round-trip distance
  distance2 = (duration2 * 0.0343) / 2;

  // Output the measured distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance2);
}
