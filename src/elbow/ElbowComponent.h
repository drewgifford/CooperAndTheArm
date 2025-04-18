#include <Servo.h>
#include "ArmComponent.h"

class ElbowComponent : private ArmComponent {
    private:
        int calibrateDelay = 500;

    public:
        int maxAngle = 1500;
        int minAngle = 900;
        int currAngle = minAngle;
        Servo servo;

        void calibrate();
        void setup(int pin);
        void update();
        void setAngle(int microseconds);
        
};