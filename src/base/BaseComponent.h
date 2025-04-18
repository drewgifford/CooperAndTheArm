#include <Servo.h>
#include "ArmComponent.h"

class BaseComponent : private ArmComponent {
    private:
        int calibrateDelay = 500;

    public:
        int maxAngle = 3000;
        int minAngle = 0;
        int currAngle = minAngle;
        Servo servo;

        void calibrate();
        void setup(int pin);
        void update();
        void setAngle(int microseconds);
};