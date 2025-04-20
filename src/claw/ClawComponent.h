#include <Servo.h>
#include "ArmComponent.h"

class ClawComponent : public ArmComponent {
    protected:
        const char* name = "CLAW";

    public:
        void calibrate();
        void setup(int pin);
        const char* getName() override {
            return name;
        }

};