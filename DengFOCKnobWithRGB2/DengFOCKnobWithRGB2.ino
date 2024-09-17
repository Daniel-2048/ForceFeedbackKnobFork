#include "DengFOC.h"
#include "DFOC_RGB.h"

#define _PI = 3.14159265758f
#define MODE 1

void detentMode(void);

int motorPP = 7;
int sensorDIR = 1;

void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  digitalMode(12, HIGH);

  DFOC_Vbus(12.6);
  DFOC_alignSensor(motorPP, sensorPP);

  RGB.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void detentMode(void) {
  float detentKp = 6;
  
  float attractorDistance = 30.0f * _PI / 180.0; //Turn angle to radian system
  float target = round(DFOC_M0_Angle() / attractorDistance) * attractorDistance;
  DFOC_M0_setTorque(detentKp * (target - DFOC_M0_Angle()));
}