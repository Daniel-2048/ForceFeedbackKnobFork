#include "DengFOC.h"

int motorPP = 7;    //Pole pairs of the motor
int sensorDIR = 1;  //Direction of sensor

void setup() {

  Serial.begin(115200);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);  

  DFOC_Vbus(12.6);  //Voltage for motor
  DFOC_alignSensor(motorPP, sensorDIR);

}

float Kp = 3;

void loop() {

  runFOC();
  float attractorDistance = 30 * 3.1415926 / 180.0; //Turn angle to radian system
  float target = round(DFOC_M0_Angle() / attractorDistance) * attractorDistance;
  DFOC_M0_setTorque(Kp * (target - DFOC_M0_Angle()));

}