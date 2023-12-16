#pragma once
#include "Constants.h"
#include <rev/CANSparkMax.h>

// abstraction layer for motors - should allow changing motors without changing beltivator.cpp

class BeltivatorMotors {
    public:
        // abstract interface
        BeltivatorMotors(double top, double bot);
        //temp for testing
        void periodicPrint();
        void setPidCoeff(Constants::pidCoeff pid_coeff);
        void setPIDPosition(double rotations);
        double getPIDPosition();
        void setPIDVelocity(double velocity);
        
        rev::CANSparkMax m_leader{1, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_follower{2, rev::CANSparkMax::MotorType::kBrushless};
        rev::SparkMaxRelativeEncoder m_encoder = m_leader.GetEncoder();

    private:
        // CAN Spark Max-specific details
        rev::SparkMaxPIDController m_pid = m_leader.GetPIDController();
        
    
        //TODO: configure PID
        Constants::pidCoeff m_pidCoeff{0.9, 0.0, 0.1, 0.0, 0.0, -1.0, 1.0};
        const int m_currentLimit = 20;
};