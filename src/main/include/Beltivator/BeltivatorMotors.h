#include "Constants.h"
#include <rev/CANSparkMax.h>

// abstraction layer for motors - should allow changing motors without changing beltivator.cpp

class BeltivatorMotors {
    public:
        // abstract interface
        BeltivatorMotors();
        void setPidCoeff(Constants::pidCoeff pid_coeff)
        void setPIDPositionMode();
        void setPIDVelocityMode();
        void setPIDPosition(double rotations);
        double getPIDPosition();
        void setPIDVelocity(double velocity);
    private:
        // CAN Spark Max-specific details
        rev::CANSparkMax m_leader{1, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_follower{2, rev::CANSparkMax::MotorType::kBrushless};
        rev::SparkMaxPIDController m_pid = m_leader.GetPIDController();
        rev::SparkMaxRelativeEncoder m_encoder = m_leader.GetEncoder();
        //TODO: configure PID
        Constants::pidCoeff m_pidCoeff{0.1, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0};
};