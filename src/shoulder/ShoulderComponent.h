#include <Servo.h>
#include "ArmComponent.h"

class ShoulderComponent : private ArmComponent {
    private:
        int calibrateDelay = 500;

    public:
        int maxAngle = 2000;
        int minAngle = 1200;
        int currAngle = minAngle;
        Servo servo;

        void calibrate();
        void setup(int pin);
        void update();
        void setAngle(int microseconds);
};