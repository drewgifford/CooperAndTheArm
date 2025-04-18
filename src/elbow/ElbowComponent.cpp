#include "ElbowComponent.h"
#include <Arduino.h>

void ElbowComponent::setup(int pin){

    servo.attach(pin, minAngle, maxAngle);

    currAngle = minAngle;
    update();

    calibrate();

    

}

void ElbowComponent::calibrate(){

    Serial.begin(9600);

    for(int i = maxAngle; i > minAngle; i--){
        servo.writeMicroseconds(i);
        delay(10);
    }

    servo.writeMicroseconds(maxAngle);
    
}

void ElbowComponent::update(){
    this->servo.writeMicroseconds(currAngle);
}

void ElbowComponent::setAngle(int microseconds){
    currAngle = microseconds;
    update();
};