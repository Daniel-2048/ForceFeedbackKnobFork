#include "DengFOC.h"
#include "DFOC_RGB.h"

#define _PI 3.1415926f

#define MODE 1

//New void
void detentMode(void);

//Alignment value
int motorPP = 7;
int sensorDIR = 1;

//Set zero angle
float zeroAngle = 0;

//Define the function
DFOC_RGB RGB = DFOC_RGB();

void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  DFOC_Vbus(12.6);
  DFOC_alignSensor(motorPP, sensorDIR);
  //set zero angle as the centre of the total angle
  zeroAngle = 3.1415926;

  RGB.begin();
}

void loop() {
  runFOC();

  float angleRange = 360;
  float Kp = 5;
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

  RGB.bri_Adj(angle, 255, 255, 255);
}

void detentMode(void) {
  float detentKp = 20;
  float attractorDistance = 6.0f * _PI / 180.0; //Turn angle to radian system
  float target = round(DFOC_M0_Angle() / attractorDistance) * attractorDistance;
  DFOC_M0_setTorque(detentKp * (target - DFOC_M0_Angle()));
}
