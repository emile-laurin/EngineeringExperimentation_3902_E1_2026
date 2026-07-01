#include <Stepper.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu2;

//1.8 degree step angle = 200 steps per revolution
const int StepsPerRev = 200;

//Initializing Stepper Library

//(steps,AIN1,AIN2,BIN1,NIN2)
Stepper nema17Stepper(StepsPerRev,5,4,6,7);

//Number of rotations - 15rmp for 3 mins - 45 rotations
//define the time in milliseconds

const long duration = 3*60*1000; //180000 milliseconds

//using micros()
//10 rotations per minute - so 1 rotation in 6 seconds
//15 rotations per minute - 1 rotation in 4 seconds - 4000ms
//4000ms / 200 steps = 20 ms per step

const long STEP_INTERVAL_MICROS=20000;

int sensor2 = 2; // sensor pi
int val2; // 0: Magnetic field detected, 1: No magnetic field detected

void setup() {
  // put your setup code here, to run once:

  //Set motor speed in rmp
  nema17Stepper.setSpeed(10);

// change baud rate - so that other processes don't slow down movement and data collection
  Serial.begin(115200);
  Serial.println("NEMA 17 is initialized with TB6612");

  pinMode(sensor2, INPUT); // set sensor pin as input

  // Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize MPU at I2C address 2 (change this to your MPU's actual address)!
  if (!mpu2.begin(2)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  //IMU Data Rate Change
  mpu2.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("3 minute cycle starting");
  long startTime=millis();
  Serial.println("Time (ms), Step_Count, Approx_Degree, Hall Effect, RotX, RotY, RotZ");

  int currentStepCount=0;
  long lastStepTimeMicros = micros();

  while (millis()- startTime < duration)
  {
    long currentMicros=micros();
    if(currentMicros-lastStepTimeMicros >= STEP_INTERVAL_MICROS)
    {
      lastStepTimeMicros += STEP_INTERVAL_MICROS;
      nema17Stepper.step(1);
      currentStepCount++;

      //calculating angular position

      float currentDegrees = currentStepCount * 1.8;

      if(currentStepCount >= StepsPerRev)
      {
        currentStepCount=0;
      }
      Serial.println(millis());
      Serial.print(",");

      //print step and angle data
      Serial.print(currentStepCount);
      Serial.print(",");
      Serial.print(currentDegrees,1);
      Serial.print(",");

      val2 = digitalRead(sensor2); // Read the sensor
      Serial.print(val2);
    }

  /* Get new sensor events with the readings */
  sensors_event_t a2, g2, temp2;
  mpu2.getEvent(&a2, &g2, &temp2);

  Serial.print(",");
  Serial.print(g2.gyro.x);
  Serial.print(",");
  Serial.print(g2.gyro.y);
  Serial.print(",");
  Serial.println(g2.gyro.z);
  }

  delay(5000);
}