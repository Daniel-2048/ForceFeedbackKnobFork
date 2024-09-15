#include "DengFOC.h"

int Sensor_DIR = 1;  //Direction of sensor
int Motor_PP = 7;    //Pole pairs of the motor

void setup() {

  Serial.begin(115200);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);  

  DFOC_Vbus(12.6);  //Voltage for motor
  DFOC_alignSensor(Motor_PP, Sensor_DIR);

}

float Kp = 3;

void loop() {

  runFOC();
  float attractor_distance = 30 * 3.1415926 / 180.0; //Turn angle to radian system
  float target = round(DFOC_M0_Angle() / attractor_distance) * attractor_distance;
  DFOC_M0_setTorque(Kp * (target - DFOC_M0_Angle()));

}