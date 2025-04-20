#include <Servo.h>
#include "ArmComponent.h"

class ShoulderComponent : public ArmComponent {
    protected:
        const char* name = "SHOULDER";

    public:
        void calibrate();
        void setup(int pin); 
        const char* getName() override {
            return name;
        }

};