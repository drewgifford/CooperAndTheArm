#include "ShoulderComponent.h"
#include <Arduino.h>

void ShoulderComponent::setup(int pin){

    servo.attach(pin, minAngle, maxAngle);

    currAngle = minAngle;
    update();

    calibrate();

    

}

void ShoulderComponent::calibrate(){

    Serial.begin(9600);

    for(int i = maxAngle; i > minAngle; i--){
        servo.writeMicroseconds(i);
        delay(10);
    }

    servo.writeMicroseconds(maxAngle);
    
}

void ShoulderComponent::update(){
    this->servo.writeMicroseconds(currAngle);
}

void ShoulderComponent::setAngle(int microseconds){
    currAngle = microseconds;
    update();
};