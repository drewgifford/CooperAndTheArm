#include <Arduino.h>
#include "claw/ClawComponent.h"
#include "elbow/ElbowComponent.h"
#include "shoulder/ShoulderComponent.h"
#include "base/BaseComponent.h"

#include <Servo.h>

Servo servo;

ClawComponent claw;
ElbowComponent elbow;
ShoulderComponent shoulder;
BaseComponent base;

int clawMaxAngle = 165;
int clawMinAngle = 65;
int clawAngle = clawMinAngle;

bool open = false;

// put function declarations here:
int myFunction(int, int);

void setup() {

  Serial.begin(9600);


  // put your setup code here, to run once:
  
  delay(500);
  elbow.setup(6);
  shoulder.setup(5);
  base.setup(3);
  

}






void calibrateServos(){
  base.calibrate();
  shoulder.calibrate();
  elbow.calibrate();
  claw.calibrate();
}

void setAngles(String data){

  // 0 : Base
  // 1 : Shoulder
  // 2 : Elbow
  // 3 : Claw
  int angles[4];
  int index = 0;

  char *token = strtok((char*)data.c_str(), ",");

  while (token != NULL && index < 4){
    angles[index] = atoi(token);
    token = strtok(NULL, ",");

    index++;
  }

  // ensure all bits are read
  if(index != 4) return;
  base.setAngle(angles[0]);
  shoulder.setAngle(angles[1]);
  elbow.setAngle(angles[2]);
  claw.setAngle(angles[3]);

}

void loop() {
  
  if (Serial.available() > 0){

    String data = Serial.readStringUntil('\n');
    data.trim();

    if(data == "CALIBRATE") {
      return calibrateServos();
    }

    else return setAngles(data);

  }
}