#include "Beltivator\BeltivatorMotors.h"
//temp for testing
#include <frc/smartdashboard/SmartDashboard.h>

BeltivatorMotors::BeltivatorMotors(double top, double bot) {
    // set second motor to mirror first
    m_leader.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
    m_leader.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
    m_leader.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, top) 	;
    m_leader.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, bot);
    m_leader.SetSmartCurrentLimit(m_currentLimit);
    m_follower.SetSmartCurrentLimit(m_currentLimit);
    m_follower.Follow(m_leader, true);
    setPidCoeff(m_pidCoeff);
}

void BeltivatorMotors::setPIDPosition(double rotations) {
    m_pid.SetReference(rotations, rev::CANSparkMax::ControlType::kPosition);
}

double BeltivatorMotors::getPIDPosition() {
    return m_encoder.GetPosition();
}

void BeltivatorMotors::setPIDVelocity(double velocity) {
    m_pid.SetReference(velocity, rev::CANSparkMax::ControlType::kDutyCycle);
}

void BeltivatorMotors::setPidCoeff(Constants::pidCoeff pid_coeff) {
    // set PID coefficients
    m_pid.SetP(pid_coeff.kP);
    m_pid.SetI(pid_coeff.kI);
    m_pid.SetD(pid_coeff.kD);
    m_pid.SetIZone(pid_coeff.kIz);
    m_pid.SetFF(pid_coeff.kFF);
    m_pid.SetOutputRange(pid_coeff.kMinOutput, pid_coeff.kMaxOutput);
}