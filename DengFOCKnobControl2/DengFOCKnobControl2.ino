#include "DengFOC.h"
#define _PI 3.1415926f
#define MODE 1

void dententMode(void);

int motorPP = 7;
int sensorDIR = 1;

float zeroAngle = 0;

void setup() {

  Serial.begin(115200);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  DFOC_Vbus(12.6);
  DFOC_alignSensor(motorPP, sensorDIR);
  zeroAngle = DFOC_M0_Angle();

}

float angleRange = 180;
float Kp = 5;

void loop() {

  runFOC();
  float angle = DFOC_M0_Angle();
  float halfAngleRange = angleRange / 2;
  //There goes into radian system
  float limitRange = halfAngleRange / 360.0f * 2 * _PI; //f reprensents float
  float upperLimit = zeroAngle + limitRange;
  float lowerLimit = zeroAngle - limitRange;

  if (angle < upperLimit && angle > lowerLimit) {
    if (MODE == 0) {
      DFOC_M0_setTorque(0);
    } else if (MODE == 1) {
      detentMode();
    }
  

  } else {
    if (angle > upperLimit) {
      DFOC_M0_setTorque(Kp * (upperLimit - angle));
    }
    if (angle < lowerLimit) {
      DFOC_M0_setTorque(Kp * (lowerLimit - angle));
    }
  }
}

float detentKp = 6;

void detentMode(void) {
  float attractor_distance = 30.0f * _PI / 180.0; //Turn angle to radian system
  float target = round(DFOC_M0_Angle() / attractor_distance) * attractor_distance;
  DFOC_M0_setTorque(detentKp * (target - DFOC_M0_Angle()));
}
