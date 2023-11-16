#include "Beltivator/Beltivator.h"

Beltivator::Beltivator() {
    if(m_debug) {
        frc::SmartDashboard::PutNumber("P", 1.0);
        frc::SmartDashboard::PutNumber("I", 0.0);
        frc::SmartDashboard::PutNumber("D", 0.0);
        frc::SmartDashboard::PutNumber("Iz", 0.0);
        frc::SmartDashboard::PutNumber("FF", 0.0);
        frc::SmartDashboard::PutNumber("MaxO", 1.0);
        frc::SmartDashboard::PutNumber("MinO", -1.0);
    }
}

// main state machine (runs periodically)
void Beltivator::run(Beltivator::PRESET preset, double joystickPos) {

    if(m_debug) {
        Constants::pidCoeff debugPid = {
            frc::SmartDashboard::GetNumber("P"),
            frc::SmartDashboard::GetNumber("I"),
            frc::SmartDashboard::GetNumber("D"),
            frc::SmartDashboard::GetNumber("Iz"),
            frc::SmartDashboard::GetNumber("FF"),
            frc::SmartDashboard::GetNumber("MaxO"),
            frc::SmartDashboard::GetNumber("MinO")
        }
        m_motors.setPidCoeff(debugPid);
    }

    switch(m_state) {
        case kSTART:
            // init state, sets up + immediately transitions to kSTATIC
            m_motors.setPIDPositionMode();
            m_position = kMIN_POS;
            m_state = kSTATIC;
            break;
        case kSTATIC:
            // state used whenever Beltivator is controlled by position PID
            if(joystickPos > kJOYSTICK_THRESHOLD || joystickPos < -kJOYSTICK_THRESHOLD) {
                //switch to manual control
                m_motors.setPIDVelocityMode();
                m_state = kMANUAL;
            } else {
                if(preset != kNONE) {
                    // set preset
                    m_position = kPRESETS[preset];
                }
                m_motors.setPIDPosition(m_position);
            }
            break;
        case kMANUAL:
            // state used for manual (joystick) control - uses velocity PID
            double encoderPos = m_motors.getPIDPosition();
            if(joystickPos > -kJOYSTICK_THRESHOLD && joystickPos < kJOYSTICK_THRESHOLD) {
                // revert to kSTATIC (position PID control)
                m_motors.setPIDPositionMode();
                m_position = encoderPos;
                m_state = kSTATIC;
            } else if((joystickPos < 0 && encoderPos > kMIN_POS) || (joystickPos > 0 && encoderPos < kMAX_POS)) {
                //limit max/min position
                m_motors.setPIDVelocity(kVEL_MULT * joystickPos);
            }
            break;
    }
}