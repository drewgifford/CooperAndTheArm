#include <Servo.h>
#ifndef ARM_COMPONENT_H
#define ARM_COMPONENT_H

class ArmComponent {
    protected:
        int calibrateDelay = 500;

        int maxAngle;
        int minAngle;
        int currAngle;
        int targetAngle;
        Servo servo;
        const char* name;

        unsigned long lastUpdate = 0;
        unsigned int updateInterval = 10;
        int stepSize = 5;

    public:
        virtual void calibrate(){};
        void zero();
        void setup(int pin);
        void update();
        void setAngleStandardized(int value);
        void setAngle(int microseconds);
        void setSpeed(int speed);

        int getAngle();
        int getAngleStandardized();

        int getSpeed();

        bool isMoving();
        void waitForMotion();
        virtual const char* getName();
};
#endif