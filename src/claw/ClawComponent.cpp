#include "ClawComponent.h"
#include <Arduino.h>

void ClawComponent::setup(int pin){

    minAngle = 1000;
    maxAngle = 2000;

    ArmComponent::setup(pin);

}

void ClawComponent::calibrate(){
    
    setAngle(maxAngle);
    waitForMotion();
    delay(calibrateDelay * 2);

    for(int i = maxAngle; i >= minAngle; i -= (maxAngle - minAngle) / 5){
        setAngle(i);
        waitForMotion();
        delay(calibrateDelay);
    }

    setAngle(maxAngle);

}