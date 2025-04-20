#include <Arduino.h>
#include "claw/ClawComponent.h"
#include "elbow/ElbowComponent.h"
#include "shoulder/ShoulderComponent.h"
#include "base/BaseComponent.h"

ClawComponent claw;
ElbowComponent elbow;
ShoulderComponent shoulder;
BaseComponent base;

const int NUM_COMPONENTS = 4;
ArmComponent* components[NUM_COMPONENTS] = {&base, &shoulder, &elbow, &claw};

int clawMaxAngle = 165;
int clawMinAngle = 65;
int clawAngle = clawMinAngle;

bool open = false;

// put function declarations here:

void calibrate(){
  claw.zero();
  elbow.zero();
  shoulder.zero();
  base.zero();

  claw.calibrate();
  elbow.calibrate();
  shoulder.calibrate();
  base.calibrate();
}

void setup() {

  Serial.begin(115200);

  // put your setup code here, to run once:
  claw.setup(9);
  elbow.setup(6);
  shoulder.setup(5);
  base.setup(3);

  Serial.println("READY");
}

bool isInteger(const char* str) {
  if (*str == '-' || *str == '+') str++;
  if (*str == '\0') return false;

  while (*str) {
    if (!isdigit(*str)) return false;
    str++;
  }
  return true;
}

void dispatchCommand(const char* target, const char* instruction, const char* argument){

  ArmComponent* component = nullptr;

  for(int i = 0; i < NUM_COMPONENTS; i++){
    // Check if the component's name is equal to target
    if(strcmp(components[i]->getName(), target) == 0){
      component = components[i];
      break;
    }
  }

  if(component == nullptr) {
    Serial.print("RESPONSE.");
    Serial.print(target);
    Serial.print(".");
    Serial.print(instruction);
    Serial.print(" FAIL");
    return;
  }

  if(strcmp(instruction, "SET_ANGLE") == 0){
    
    if(argument && isInteger(argument)){

      Serial.print("RESPONSE.");
      Serial.print(target);
      Serial.println(".SET_ANGLE SUCCESS");

      component->setAngleStandardized(atoi(argument));
    }
    else {
      Serial.print("RESPONSE.");
      Serial.print(target);
      Serial.println(".SET_ANGLE FAIL");
    }
  }
  else if(strcmp(instruction, "CALIBRATE") == 0){
    component->calibrate();
    Serial.print("RESPONSE.");
    Serial.print(target);
    Serial.println(".CALIBRATE SUCCESS");
  }

  else if(strcmp(instruction, "GET_SPEED") == 0){
    Serial.print("RESPONSE.");
    Serial.print(target);
    Serial.print(".GET_SPEED ");
    Serial.println(component->getSpeed());
  }

  else if(strcmp(instruction, "GET_ANGLE") == 0){

    Serial.print("RESPONSE.");
    Serial.print(target);
    Serial.print(".GET_ANGLE ");
    Serial.println(component->getAngleStandardized());

  }
  else if (strcmp(instruction, "SET_SPEED") == 0){
    if(argument && isInteger(argument)){

      Serial.print("RESPONSE.");
      Serial.print(target);
      Serial.println(".SET_SPEED SUCCESS");

      component->setSpeed(atoi(argument));

    }
    else {
      Serial.print("RESPONSE.");
      Serial.print(target);
      Serial.println(".SET_SPEED FAIL");
    }
  }
}

void handleCommand(char* command){

  char* target = strtok(command, ".");
  char* instructionWithArg = strtok(NULL, ".");

  if(target == NULL || instructionWithArg == NULL) return;

  char* instruction = strtok(instructionWithArg, " ");
  char* argument = strtok(NULL, " ");

  dispatchCommand(target, instruction, argument);
}


void processLine(char* line){

  char *saveptr;
  char *token = strtok_r(line, ",", &saveptr);

  while (token != NULL){
    handleCommand(token);
    token = strtok_r(NULL, ",", &saveptr);
  }

}

const int buffer_size = 128;
static char buffer[buffer_size];

void loop() {

  if (Serial.available() > 0){

    size_t len = Serial.readBytesUntil('\n', buffer, buffer_size - 1);
    buffer[len] = '\0';

    processLine(buffer);
  }

  base.update();
  shoulder.update();
  elbow.update();
  claw.update();


}