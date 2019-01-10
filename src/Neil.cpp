#include <Arduino.h>
#include <Wire.h>
#include "Neil.h"
#include "sensor.h"
#include "actuator.h"
#include "controller.h"


float dt, roll, pitch, yaw;
float front_servo_angle,right_servo_angle, rear_servo_angle, left_servo_angle;


void setup() {
  IMU_Setup();
  servo_setup();
  Serial.begin(115200);
  delay(500);
}

void loop() {
  float StartTime = micros(); //start the timer to calculate looptime


  IMU_Read();
  comp_filter();
  controller();
  servo_move();

  //Serial.print(dt,3);
  //Serial.print(" , ");
  //Serial.print(roll);
  // Serial.print(" , ");
  Serial.print(pitch);
  Serial.print(" , ");
  Serial.println(right_servo_angle);

  float EndTime = micros();
  dt = (EndTime - StartTime); //calculate the time between gyro reading values for the complemenatary filter
  dt = (dt) / 1000000; //convert to seconds
}
