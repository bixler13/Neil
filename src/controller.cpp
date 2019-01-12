#include "Neil.h"
#include <arduino.h>
#include "controller.h"
#include "functions.h"

float pitch_error, pitch_error_old, roll_error, roll_error_old, yaw_error, yaw_error_old;
float pitch_command, roll_command, yaw_command;

float pitch_P, pitch_I, pitch_I_old, pitch_D;
float roll_P, roll_I, roll_I_old, roll_D;
float yaw_P, yaw_I, yaw_I_old, yaw_D;

float pitch_servo_angle, roll_servo_angle, yaw_servo_angle;

void controller(){

if (mode == 3){
  pitch_command = mapFloat(pitch_input, -1000, 1000, -25, 25);
  roll_command = mapFloat(roll_input, -1000, 1000, -25, 25);
  yaw_command = mapFloat(yaw_input, -1000, 1000, -25, 25);


}

else {
  pitch_command = 0;
  roll_command = 0;
  yaw_command = 0;
}

///////////////////////////pitch axis///////////////////////////////////
pitch_error = pitch_command - pitch;

pitch_P = pitch_p * pitch_error;

pitch_I = pitch_i * ((pitch_error * dt) + pitch_I_old);
pitch_I_old = pitch_I;

pitch_D = pitch_d*((pitch_error_old - pitch_error) / dt);
pitch_error_old = pitch_error;

pitch_servo_angle = pitch_P + pitch_I + pitch_D;

left_servo_angle = mapFloat(-1 * pitch_servo_angle, -45, 45, 20, 150);
right_servo_angle = mapFloat(pitch_servo_angle, -45, 45, 20, 150);

///////////////////////roll axis////////////////////////////////////
roll_error = roll_command - roll;

roll_P = roll_p * roll_error;

roll_I = roll_i * ((roll_error * dt) + roll_I_old);
roll_I_old = roll_I;

roll_D = roll_d*((roll_error_old - roll_error) / dt);
roll_error_old = roll_error;

roll_servo_angle = roll_P + roll_I + roll_D;

front_servo_angle = mapFloat(-1 * roll_servo_angle, -45, 45, 20, 150);
rear_servo_angle = mapFloat(roll_servo_angle, -45, 45, 20, 150);

//////////////////////yaw axis/////////////////////////////////////
yaw_error = yaw_command - yaw;
left_servo_angle = left_servo_angle + yaw_error;
right_servo_angle = right_servo_angle + yaw_error;
front_servo_angle = front_servo_angle + yaw_error;
rear_servo_angle = rear_servo_angle + yaw_error;

left_servo_angle = constrain(left_servo_angle *yaw_p, 20, 150);
right_servo_angle = constrain(right_servo_angle *yaw_p, 20, 150);
front_servo_angle = constrain(front_servo_angle *yaw_p, 20, 150);
rear_servo_angle = constrain(rear_servo_angle *yaw_p, 20, 150);

}
