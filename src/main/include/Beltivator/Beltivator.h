#include "BeltivatorMotors.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "Constants.h"

class Beltivator {
    public:
        // used as index of array (possibly cursed)
        enum PRESET {
            kNONE = -1,
            kBOTTOM,
            kHALF,
            kTOP
        };
        void run(PRESET preset, double joystickPos);   // run periodically
        bool m_debug = false;
    private:
        const double kMAX_POS = 100.0;                 //fully extended position (# of rotations) (may overshoot slightly)
        const double kMIN_POS = 0.0;                   //fully retracted position (# of rotations) (may overshoot slightly)
        const double kPRESETS[3] = {0.0, 50.0, 100.0}; //array of presets (# of rotations) - maps to PRESET enum
        const double kJOYSTICK_THRESHOLD = 0.05;       //threshold to consider joystick active
        const double kVEL_MULT = 25.0;                 //maximum rotations/second for joystick control
        enum STATE {
            kSTART,
            kSTATIC,
            kMANUAL
        } m_state = kSTART;
        double m_position;
        BeltivatorMotors m_motors; // abstraction layer for motors since they might change
};