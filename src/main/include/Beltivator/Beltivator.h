#pragma once
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
        void setPidCoeff(Constants::pidCoeff coeff);
        const double kMAX_POS = 100.0;                 //fully extended position (# of rotations) (may overshoot slightly)
        const double kMIN_POS = 5.0;                   //fully retracted position (# of rotations) (may overshoot slightly)
        double m_position;
        BeltivatorMotors m_motors{kMAX_POS, kMIN_POS}; // abstraction layer for motors since they might change
    private:
        
        const double kPRESETS[3] = {0.0, 50.0, 100.0}; //array of presets (# of rotations) - maps to PRESET enum
        const double kJOYSTICK_THRESHOLD = 0.05;       //threshold to consider joystick active
        const double kVEL_MULT = 1.0;                  //maximum rotations/second for joystick control
        const double kBOUNCE = 2.0;
        enum STATE {
            kSTART,
            kSTATIC,
            kMANUAL
        } m_state = kSTART;
        double m_direction = 0.0;
        
        
};