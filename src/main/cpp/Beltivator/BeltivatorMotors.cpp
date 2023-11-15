#include "Beltivator\BeltivatorMotors.h"

BeltivatorMotors::BeltivatorMotors() {
    // set second motor to mirror first
    m_follower.Follow(m_leader, true);
    // set PID coefficients
    m_pid.SetP(m_pidCoeff.kP);
    m_pid.SetI(m_pidCoeff.kI);
    m_pid.SetD(m_pidCoeff.kD);
    m_pid.SetIZone(m_pidCoeff.kIz);
    m_pid.SetFF(m_pidCoeff.kFF);
    m_pid.Set
}

void BeltivatorMotors::setPIDPositionMode() {
    // not needed
}

void BeltivatorMotors::setPIDVelocityMode() {
    // not needed
}

void BeltivatorMotors::setPIDPosition(double rotations) {
    m_pid.SetReference(rotations, rev::CANSparkMax::ControlType::kPosition);
}

double BeltivatorMotors::getPIDPosition() {
    return m_encoder.GetPosition();
}

void BeltivatorMotors::setPIDVelocity(double velocity) {
    m_pid.SetReference(velocity, rev::CANSparkMax::ControlType::kVelocity);
}