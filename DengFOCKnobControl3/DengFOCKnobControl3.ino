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
  
  if(Mode == 0) {
    smoothMode();
  } else if(Mode == 1) {
    dampMode();
  }

}

void smoothMode() {

  float Ksmooth = 4;
  DFOC_M0_setTorque(Ksmooth * DFOC_M0_Velocity());

}

void dampMode() {

  float Kdamp = 4;
  DFOC_M0_setTorque(Kdamp * -1 * DFOC_M0_Velocity());
      
}