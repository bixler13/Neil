#include "Neil.h"
#include <arduino.h>
#include "controller.h"
#include "functions.h"

float pitch_error, roll_error, yaw_error;
float pitch_command, roll_command, yaw_command;

float pitch_P, pitch_I, pitch_D;

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

//pitch axis
pitch_error = pitch_command - pitch;

pitch_P = p_pitch * pitch_error;

pitch_I = ((pitch_error * dt)+I_pitch_old);
pitch_I_new = I_pitch_old *i_pitch;

pitch_command = pitch_P + pitch_I + pitch_D;

left_servo_angle = mapFloat(-1 * pitch_command *pitch_p, -45, 45, 20, 150);
right_servo_angle = mapFloat(pitch_command *pitch_p, -45, 45, 20, 150);



//roll axis
roll_error = roll_command - roll;
front_servo_angle = mapFloat(-1 * roll_error *roll_p, -45, 45, 20, 150);
rear_servo_angle = mapFloat(roll_error *roll_p, -45, 45, 20, 150);

//yaw axis
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
