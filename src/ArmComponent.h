#include <Servo.h>
#ifndef ARM_COMPONENT_H
#define ARM_COMPONENT_H

class ArmComponent {
    private:
        int calibrateDelay;

    public:
        int maxAngle;
        int minAngle;
        int currAngle;
        Servo servo;

        virtual void calibrate(){};
        virtual void setup(int pin){};
        virtual void update(){};
};
#endif