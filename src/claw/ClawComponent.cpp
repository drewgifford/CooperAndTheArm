#include "ClawComponent.h"
#include <Arduino.h>

void ClawComponent::setup(int pin){

    this->servo.attach(pin);

    currAngle = minAngle;
    update();

    calibrate();
}

void ClawComponent::calibrate(){
    
    currAngle = minAngle;
    update();

    int steps = 10;
    int step = (maxAngle - minAngle) / steps;

    for(; currAngle <= maxAngle; currAngle += step){
        update();
        delay(calibrateDelay);
    }

    this->servo.write(maxAngle);
    delay(calibrateDelay * 2);

    for(; currAngle >= minAngle; currAngle -= step){
        update();
        delay(calibrateDelay);
    }

    update();

    
    delay(calibrateDelay * 2);
}

void ClawComponent::update(){
    this->servo.write(currAngle);
}