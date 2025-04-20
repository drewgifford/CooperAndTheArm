#include "ShoulderComponent.h"
#include <Arduino.h>

void ShoulderComponent::setup(int pin){

    minAngle = 1200;
    maxAngle = 2000;
    ArmComponent::setup(pin);

}

void ShoulderComponent::calibrate(){

    setAngle(maxAngle);
    waitForMotion();
    delay(calibrateDelay * 2);

    for(int i = maxAngle; i > minAngle; i -= (maxAngle - minAngle) / 20){
        setAngle(i);
        waitForMotion();
        delay(calibrateDelay);
    }

    setAngle(maxAngle);
    
}

