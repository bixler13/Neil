#ifndef NEIL_H
#define NEIL_H

#define front_servo_pin  4
#define right_servo_pin  5
#define rear_servo_pin   6
#define left_servo_pin   7

#define front_servo_trim 0
#define right_servo_trim 0
#define rear_servo_trim 0
#define left_servo_trim 0

#define PPM_pin 3

#define pitch_p 1
#define pitch_i 1
#define pitch_d .1

#define roll_p 1
#define roll_i 1
#define roll_d .1

#define yaw_p .5
#define yaw_i 1
#define yaw_d .1

extern float dt, roll, pitch, yaw;
extern float front_servo_angle, right_servo_angle, rear_servo_angle, left_servo_angle;

extern float throttle_input, pitch_input, roll_input, yaw_input, mode_input, mode;


#endif
