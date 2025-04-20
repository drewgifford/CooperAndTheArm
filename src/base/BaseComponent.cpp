#include "BaseComponent.h"
#include <Arduino.h>

void BaseComponent::setup(int pin){

    minAngle = 1000;
    maxAngle = 2000;

    ArmComponent::setup(pin);

}

void BaseComponent::calibrate(){

    setAngle(1500);
    waitForMotion();
    delay(calibrateDelay * 2);

    for(int i = maxAngle; i > minAngle; i -= (maxAngle - minAngle) / 10){
        setAngle(i);
        waitForMotion();
        delay(calibrateDelay);
    }

    setAngle(1500);

}