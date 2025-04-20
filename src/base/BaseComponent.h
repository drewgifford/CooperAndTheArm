#include <Servo.h>
#include "ArmComponent.h"

class BaseComponent : public ArmComponent {
    protected:
        const char* name = "BASE";

    public:
        void calibrate();
        void setup(int pin);
        const char* getName() override {
            return name;
        }

};