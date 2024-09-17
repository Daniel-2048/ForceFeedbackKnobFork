#include "DengFOC.h"
#define _PI 3.1415926f
#define Mode 1

int motorPP = 7;
int sensorDIR = 1;

void setup() {

  Serial.begin(115200);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  DFOC_Vbus(12.6);
  DFOC_alignSensor(motorPP, sensorDIR);

}

void loop() {

  runFOC();
  

}
