#include "ElbowComponent.h"
#include <Arduino.h>

void ElbowComponent::setup(int pin){

    this->servo.attach(pin);

    currAngle = 80;
    update();

    delay(1000);

    for(int i = 0; i < 10; i++){

        currAngle -= 5;
        update();

        delay(500);
    }

}

void ElbowComponent::calibrate(){

}

void ElbowComponent::update(){
    this->servo.write(currAngle);
}