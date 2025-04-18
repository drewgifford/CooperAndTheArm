#include "BaseComponent.h"
#include <Arduino.h>

void BaseComponent::setup(int pin){

    servo.attach(pin, minAngle, maxAngle);

    currAngle = maxAngle;
    update();

    delay(1000);

    calibrate();

}

void BaseComponent::calibrate(){

    for(int i = maxAngle; i > minAngle; i--){
        servo.writeMicroseconds(i);
        delay(10);
    }

    servo.writeMicroseconds(maxAngle);
    
}

void BaseComponent::update(){
    this->servo.writeMicroseconds(currAngle);
}

void BaseComponent::setAngle(int microseconds){
    currAngle = microseconds;
    update();
};