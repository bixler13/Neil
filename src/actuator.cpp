#include <servo.h>
#include "actuator.h"
#include "Neil.h"


Servo servo_front;
Servo servo_right;
Servo servo_rear;
Servo servo_left;


void servo_setup(){
  servo_front.attach(front_servo_pin);
  servo_right.attach(right_servo_pin);
  servo_rear.attach(rear_servo_pin);
  servo_left.attach(left_servo_pin);
}

void servo_move(){
  servo_front.write(front_servo_angle + front_servo_trim);
  servo_right.write(right_servo_angle + right_servo_trim);
  servo_rear.write(rear_servo_angle + rear_servo_trim);
  servo_left.write(left_servo_angle + left_servo_trim);
}
