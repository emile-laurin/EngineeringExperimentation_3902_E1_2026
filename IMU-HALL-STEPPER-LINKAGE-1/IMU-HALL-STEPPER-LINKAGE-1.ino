#include <Stepper.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu2;

//1.8 degree step angle = 200 steps per revolution

const int StepsPerRev = 200;

//Initializing Stepper Library
//(steps,AIN1,AIN2,BIN1,BIN2)
Stepper nema17Stepper(StepsPerRev,5,4,6,7);

//Number of rotations - 15rpm for 3 mins - 45 rotations

//Define the time in milliseconds

const long duration = 3*60*1000; //180000 milliseconds

int sensor2 = 9; // sensor pin
int val2; // 0: Magnetic field detected, 1: No magnetic field detected

void setup() {
  // put your setup code here, to run once:

  //Set the motor speed in rpm
  nema17Stepper.setSpeed(15); //15 rpm

  Serial.begin(9600);
  Serial.println("NEMA 17 is initialized with TB6612");

  pinMode(sensor2, INPUT); //Hall Effect Sensor - set sensor pin as input

  while(!Serial)
  delay(10); //Will pause Zero, Leonardo, etc. until console opens up

  Serial.println("Adafruit MPU6050 test!");

  //Try to initialize MPU at I2C address 2
  if (!mpu2.begin(0x68)) {
    Serial.println("Failed to find MPU6050 chip");
    while(1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 found!");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("3 minute cycle starting");

  long startTime=millis();

  Serial.println("Time, Hall Effect, RotX, RotY, RotZ");

  while(millis()-startTime < duration)
  {
    Serial.print(millis());
    nema17Stepper.step(1);

    Serial.print(",");

    val2 = digitalRead(sensor2); //Read the sensor

    Serial.print(val2);

    sensors_event_t a2, g2, temp2;
    mpu2.getEvent(&a2, &g2, &temp2);

    Serial.print(",");
    Serial.print(g2.gyro.x);
    Serial.print(",");
    Serial.print(g2.gyro.y);
    Serial.print(",");
    Serial.println(g2.gyro.z);

    delay(10);
  }
}