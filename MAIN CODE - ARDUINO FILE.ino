#include <ADXL345.h>
#include <bma180.h>
#include <HMC58X3.h>
#include <ITG3200.h>
#include <MS561101BA.h>
#include <I2Cdev.h>
#include <MPU60X0.h>
#include <EEPROM.h>
//#define DEBUG
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
int raw_values[9];
//char str[512];
float ypr[3]; // yaw pitch roll
float val[9];
Servo servo1;
Servo servo2;
Servo servo3;
float old[3];
float apple[3];
int flag1;
int flag2;
// Set the FreeIMU object
FreeIMU my3IMU = FreeIMU();
void setup() {
Serial.begin(9600);
Wire.begin();
servo1.attach(8);
servo2.attach(9);
servo3.attach(10);
flag1=1;
flag2=1;
apple[0]=apple[1]=apple[2]=0;
old[0]=old[1]=old[2]=0;
delay(5);
my3IMU.init(); // the parameter enable or disable fast mode
delay(5);
}
void loop() {
my3IMU.getYawPitchRoll(ypr);
flag1 = analogRead(A0);
if (flag1<500)
{ flag2 = 1;
}
else
{
flag2 =0;
}
if(ypr[0]-old[0]<0.16 && ypr[0]-old[0]>-0.16)
{
Serial.print("Yaw: ");
Serial.print(apple[0]);
}
if((ypr[0]-old[0]<90 && ypr[0]-old[0]>=0.16) || (ypr[0]-old[0]>-90 && ypr[0]-old[0]<=-0.16))
{
Serial.print("Yaw: ");
apple[0]=apple[0]+ypr[0]-old[0];
Serial.print(apple[0]);
if(apple[0]>-90 && apple[0]<90)
{
if (flag2==1)
{ servo1.write(90+apple[0]);
}
else
{
servo1.write(90-apple[0]);
}
Serial.print("***");
}
}
if(ypr[0]-old[0]>=90 || ypr[0]-old[0]<=-90)
{
Serial.print("Yaw: ");
Serial.print(apple[0]);
}
if((ypr[1]-old[1])>0.12 || (-ypr[1]+old[1])>0.12)
{
Serial.print(" Pitch: ");
apple[1]=ypr[1];
Serial.print(apple[1]);
if (flag2==1)
{ servo2.write(92.5-apple[1]);
}
else
{
servo2.write(90+apple[1]);
}
}
else
{
Serial.print(" Pitch: ");
Serial.print(apple[1]);
}
if((ypr[2]-old[2])>0.12 || (-ypr[2]+old[2])>0.12)
{
Serial.print(" Roll: ");
apple[2]=ypr[2];
Serial.print(apple[2]);
if (flag2==1)
{ servo3.write(87+apple[2]);
}
else
{
servo3.write(87-apple[2]);
}
}
else
{
Serial.print(" Roll: ");
Serial.print(apple[2]);
}
old[0]=ypr[0];
old[1]=ypr[1];
old[2]=ypr[2];
Serial.print(" OYaw: ");
Serial.print(ypr[0]);
Serial.print(" OPitch: ");
Serial.print(ypr[1]);
Serial.print(" ORoll: ");
Serial.print(ypr[2]);
Serial.println("");
delay(10);
}
