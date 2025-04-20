#include "ElbowComponent.h"
#include <Arduino.h>

void ElbowComponent::setup(int pin){

    minAngle = 1000;
    maxAngle = 1500;
    
    ArmComponent::setup(pin);
}

void ElbowComponent::calibrate(){

    setAngle(minAngle);
    //waitForMotion();
    delay(calibrateDelay * 2);

    for(int i = minAngle; i < maxAngle; i += (maxAngle - minAngle) / 10){
        setAngle(i);
        while(isMoving()){
            update();
        }
        delay(calibrateDelay);
    }

    setAngle(minAngle);
    
}