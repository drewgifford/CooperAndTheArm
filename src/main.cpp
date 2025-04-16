#include <Arduino.h>
#include "claw/ClawComponent.h"
#include "elbow/ElbowComponent.h"

#include <Servo.h>

Servo servo;

ClawComponent claw;
ElbowComponent elbow;

int clawMaxAngle = 165;
int clawMinAngle = 65;
int clawAngle = clawMinAngle;

bool open = false;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  
  delay(500);
  claw.setup(9);
  elbow.setup(6);
  

}




void loop() {
  

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}