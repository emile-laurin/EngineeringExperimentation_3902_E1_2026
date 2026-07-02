#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu2;

void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize MPU at I2C address 2 (change this to your MPU's actual address)!
  if (!mpu2.begin(0x68)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a2, g2, temp2;
  mpu2.getEvent(&a2, &g2, &temp2);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a2.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a2.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a2.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g2.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g2.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g2.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp2.temperature);
  Serial.println(" degC");
  delay(500);
}