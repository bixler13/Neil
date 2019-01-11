#include <Arduino.h>
#include <Wire.h>
#include "Neil.h"
#include "actuator.h"
#include "controller.h"

//#define USE_RAW
#define USE_DMP

float dt, roll, pitch, yaw;
float front_servo_angle,right_servo_angle, rear_servo_angle, left_servo_angle;

  #ifdef USE_RAW
    #include "sensor_raw.h"
  #endif

  #ifdef USE_DMP
    #include "sensor_dmp.h"
  #endif


void setup() {

  #ifdef USE_RAW
    IMU_Setup();
  #endif

  #ifdef USE_DMP
    dmpsetup();
  #endif

  servo_setup();
  Serial.begin(115200);
  delay(500);
}

void loop() {
  float StartTime = micros(); //start the timer to calculate looptime

  #ifdef USE_RAW
    IMU_Read();
    comp_filter();
  #endif

  #ifdef USE_DMP
    dmploop();
  #endif

  controller();
  servo_move();

  Serial.print(front_servo_angle);
  Serial.print(" , ");
  Serial.print(right_servo_angle);
  Serial.print(" , ");
  Serial.print(rear_servo_angle);
  Serial.print(" , ");
  Serial.println(left_servo_angle);

  float EndTime = micros();
  dt = (EndTime - StartTime); //calculate the time between gyro reading values for the complemenatary filter
  dt = (dt) / 1000000; //convert to seconds
}
