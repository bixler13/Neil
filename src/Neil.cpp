#include <Arduino.h>
#include <Wire.h>
#include "Neil.h"
#include "sensor_raw.h"
#include "sensor_dmp.h"
#include "actuator.h"
#include "controller.h"



float dt, roll, pitch, yaw;
float front_servo_angle,right_servo_angle, rear_servo_angle, left_servo_angle;


void setup() {
  //IMU_Setup();
  servo_setup();
  dmpsetup();
  Serial.begin(115200);
  delay(500);
}

void loop() {
  float StartTime = micros(); //start the timer to calculate looptime


  //IMU_Read();
  //comp_filter();
  dmploop();
  controller();
  servo_move();

  Serial.print(dt,3);
  Serial.print(" , ");
  Serial.print(yaw);
  Serial.print(" , ");
  Serial.print(pitch);
  Serial.print(" , ");
  Serial.println(roll);

  float EndTime = micros();
  dt = (EndTime - StartTime); //calculate the time between gyro reading values for the complemenatary filter
  dt = (dt) / 1000000; //convert to seconds
}
