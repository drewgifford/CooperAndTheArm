#include <Servo.h>
#include "ArmComponent.h"

class ElbowComponent : public ArmComponent {
    protected:
        const char* name = "ELBOW";

    public:
        void calibrate();
        void setup(int pin);
        const char* getName() override {
            return name;
        }
        
};