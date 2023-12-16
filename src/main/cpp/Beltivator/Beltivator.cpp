#include "Beltivator/Beltivator.h"

void Beltivator::setPidCoeff(Constants::pidCoeff coeff) {
    m_motors.setPidCoeff(coeff);
}

// main state machine (runs periodically)
void Beltivator::run(Beltivator::PRESET preset, double joystickPos) {

    switch(m_state) {
        case kSTART:
            // init state, sets up + immediately transitions to kSTATIC
            m_position = kMIN_POS;
            m_state = kSTATIC;
            break;
        case kSTATIC:
            // state used whenever Beltivator is controlled by position PID
            if(joystickPos > kJOYSTICK_THRESHOLD || joystickPos < -kJOYSTICK_THRESHOLD) {
                //switch to manual control
                m_state = kMANUAL;
                //frc::SmartDashboard::PutString("PrintMessage", "Manual mode");
            } else if(preset != kNONE) {
                // set preset
                m_position = kPRESETS[preset];
                m_motors.setPIDPosition(m_position);
            }
            break;
        case kMANUAL:
            // state used for manual (joystick) control - uses velocity PID
            double encoderPos = m_motors.getPIDPosition();
            if(joystickPos > -kJOYSTICK_THRESHOLD && joystickPos < kJOYSTICK_THRESHOLD) {
                // revert to kSTATIC (position PID control)
                //frc::SmartDashboard::PutString("PrintMessage", "Static mode");
                double bounce = kBOUNCE * m_direction;
                m_position = encoderPos + bounce;
                if(m_position > kMAX_POS) {
                    m_position = kMAX_POS;
                } else if(m_position < kMIN_POS) {
                    m_position = kMIN_POS;
                }
                m_motors.setPIDPosition(m_position);
                m_state = kSTATIC;
            } else if((joystickPos < 0 && encoderPos < kMIN_POS) || (joystickPos > 0 && encoderPos > kMAX_POS)) {
                m_motors.setPIDVelocity(0.0); //exceeded limit
            } else {
                m_motors.setPIDVelocity(kVEL_MULT * joystickPos);
                if(joystickPos < 0) {
                    m_direction = -1.0;
                } else {
                    m_direction = 1.0;
                }
            }
            break;
    }
}