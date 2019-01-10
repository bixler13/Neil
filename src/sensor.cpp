#include <Wire.h>
#include <arduino.h>
#include "sensor.h"
#include "Neil.h"
#include "MPU6050.h"
#include "I2Cdev.h"


float AccX, AccY, AccZ, Temp, GyroX, GyroY, GyroZ;
float accyaw, accpitch,accroll, gyropitch, gyroyaw, gyroroll;

void IMU_Setup(){
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void IMU_Read(){
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,14,true);  // request a total of 14 registers
  AccX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AccY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AccZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyroX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyroY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyroZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    //convert the values to degs/sec
  GyroX = (GyroX/131);
  GyroY = (GyroY/131);
  GyroZ = (GyroZ/131);

  //calculate the angle the accelerometer thinks you are at
  accpitch =  atan(AccY / sqrt(sq(AccX) + sq(AccZ))) * 57.3;
  accroll = atan(AccX / sqrt(sq(AccY) + sq(AccZ))) * 57.3;

  //calulate the angle the gyro thinks you are at
  gyropitch = pitch + GyroX*dt;
  gyroroll  = roll - GyroY*dt;
  gyroyaw = yaw - GyroZ*dt;
}

void comp_filter(){
  pitch = .98 * gyropitch + .02 * accpitch;
  roll =  .98 * gyroroll + .02 * accroll;
  yaw = gyroyaw;
}

void DMP_setup(){
  Wire.begin();
  Wire.setClock(400000);
  //Fastwire::setup(400, true);
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);
  devStatus = mpu.dmpInitialize();
  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
  mpu.setDMPEnabled(true);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
  mpuIntStatus = mpu.getIntStatus();
  dmpReady = true;
  packetSize = mpu.dmpGetFIFOPacketSize();
}

void DMP(){

}
