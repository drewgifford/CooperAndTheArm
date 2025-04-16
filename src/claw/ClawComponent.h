#include <Servo.h>
#include "ArmComponent.h"

class ClawComponent : private ArmComponent {
    private:
        int calibrateDelay = 500;

    public:
        int maxAngle = 165;
        int minAngle = 65;
        int currAngle = minAngle;
        Servo servo;

        void calibrate();
        void setup(int pin);
        void update();
};