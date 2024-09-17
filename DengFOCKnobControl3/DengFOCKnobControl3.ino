#include "DengFOC.h"
#define MODE 1

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
  if(MODE == 0)
    smoothMode();
  else if(MODE == 1)
    dampMode();

}

void smoothMode() {
  float Ksmooth = 0.052;
  DFOC_M0_setTorque(Ksmooth * DFOC_M0_Velocity());
}

void dampMode() {
  float Kdamp = 0.4;
  DFOC_M0_setTorque(Kdamp * -1 * DFOC_M0_Velocity());  
}