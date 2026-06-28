#include <Servo.h>


Servo myservo2;  // create servo object to control a servo
int pos2 = 0;    // variable to store the servo position


void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
  myservo2.attach(3);

  myservo2.write(90);
}


void loop() {
 
}