#include "ArmComponent.h"
#include <Arduino.h>

const int STD_MIN = -1000;
const int STD_MAX = 1000;
const int STD_RANGE = STD_MAX - STD_MIN;

void ArmComponent::setup(int pin){
    servo.attach(pin, minAngle, maxAngle);
    
    servo.writeMicroseconds(minAngle);
    currAngle = minAngle;
    targetAngle = minAngle;
}

bool ArmComponent::isMoving(){
    return currAngle != targetAngle;
}

void ArmComponent::waitForMotion(){
    while(isMoving()){
        update();
    }
}

void ArmComponent::zero(){
    targetAngle = minAngle;
    waitForMotion();
}

int ArmComponent::getAngle(){
    return currAngle;
}

int ArmComponent::getAngleStandardized(){
    int angle = getAngle();

    float valuePct = (angle - minAngle) / (float)(maxAngle - minAngle);
    int angleStd = STD_MIN + (int)(STD_RANGE) * valuePct;

    return angleStd;
}

void ArmComponent::setSpeed(int speed){
    const int MAX_SPEED = 20;
    const int MIN_SPEED = 1;
    if(speed > MAX_SPEED) speed = MAX_SPEED;
    else if(speed < MIN_SPEED) speed = MIN_SPEED;

    stepSize = speed;
}

void ArmComponent::setAngle(int microseconds){

    if(microseconds > maxAngle) microseconds = maxAngle;
    if(microseconds < minAngle) microseconds = minAngle;

    targetAngle = microseconds;
};

void ArmComponent::setAngleStandardized(int value){

    if(value > STD_MAX) value = STD_MAX;
    else if(value < STD_MIN) value = STD_MIN;

    int range = maxAngle - minAngle;
    float valuePct = ((float)value - STD_MIN) / (float)STD_RANGE; // Range: 0-2000
    int angle = minAngle + (int)(range * valuePct);

    targetAngle = angle;
}

int ArmComponent::getSpeed(){
    return stepSize;
}

void ArmComponent::update(){

    unsigned long now = millis();

    if (now - lastUpdate >= updateInterval) {
        lastUpdate = now;

        if(currAngle == targetAngle) return;

        if(currAngle < targetAngle) {
            currAngle += stepSize;
            if(currAngle >= targetAngle) currAngle = targetAngle;
        }
        else {
            currAngle -= stepSize;
            if(currAngle <= targetAngle) currAngle = targetAngle;
        }

        servo.writeMicroseconds(currAngle);
    }
}

const char* ArmComponent::getName(){
    return name;
}