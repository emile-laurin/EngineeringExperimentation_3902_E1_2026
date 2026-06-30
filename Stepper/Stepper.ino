#include <Stepper.h>

//1.8 degree step angle = 200 steps per revolution

const int StepsPerRev = 2000;

//Initializing Stepper Library
//(steps,AIN1,AIN2,BIN1,NIN2)
Stepper nema17Stepper(StepsPerRev,5,4,6,7);

void setup() {
  // put your setup code here, to run once:

  //Set motor speed in rmp
  nema17Stepper.setSpeed(10);

  Serial.begin(9600);
  Serial.println("NEMA 17 is initialized with TB6612");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("Moving CW");
  nema17Stepper.step(StepsPerRev);
  delay(1000); //pause for one second

  Serial.print("Moving CCW");
  nema17Stepper.step(-StepsPerRev);
  delay(1000);
}
