#include <Arduino.h>
#include <Wire.h>
#include "Neil.h"
#include "actuator.h"
#include "controller.h"
#include "rc_read.h"

//#define USE_RAW
#define USE_DMP


#define OUTPUT_IMU
//#define OUTPUT_SERVO
//#define OUTPUT_INPUT

float dt, roll, pitch, yaw;
float front_servo_angle,right_servo_angle, rear_servo_angle, left_servo_angle;

float throttle_input, pitch_input, roll_input, yaw_input, mode;

float tpa;

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

  #if defined(OUTPUT_IMU)  || defined(OUTPUT_INPUT) || defined(OUTPUT_SERVO)
    Serial.begin(115200);
  #endif

  rc_read_setup_ppm();
  servo_setup();
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

  rc_read_ppm();
  find_mode();
  controller();
  servo_move();

  #ifdef OUTPUT_INPUT
    Serial.print(mode);
    Serial.print(" , ");
    Serial.print(throttle_input);
    Serial.print(" , ");
    Serial.print(pitch_input);
    Serial.print(" , ");
    Serial.print(roll_input);
    Serial.print(" , ");
    Serial.println(yaw_input);
  #endif

  #ifdef OUTPUT_IMU
    Serial.print(roll);
    Serial.print(" , ");
    Serial.print(pitch);
    Serial.print(" , ");
    Serial.print(yaw);
    Serial.print(" , ");
    Serial.println(dt,3);
  #endif

  #ifdef OUTPUT_SERVO
    Serial.print(front_servo_angle);
    Serial.print(" , ");
    Serial.print(right_servo_angle);
    Serial.print(" , ");
    Serial.print(rear_servo_angle);
    Serial.print(" , ");
    Serial.println(left_servo_angle);
  #endif

  float EndTime = micros();
  dt = (EndTime - StartTime); //calculate the time between gyro reading values for the complemenatary filter
  dt = (dt) / 1000000; //convert to seconds
}
