// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include <iostream>

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  // enable debug mode (displays PID coefficients on smart dashboard)
  m_beltivator.m_debug = true;
}

void Robot::TeleopPeriodic() {
  //std::cout << "test";
  // Calculate distance to target and shoot
  //auto distance = vision.getDistanceToTarget();
  //shooter.shoot(distance);
  m_preset = Beltivator::kNONE;
  if(m_stick.GetAButtonPressed()){
    m_preset = Beltivator::kBOTTOM;
  } else if(m_stick.GetBButtonPressed()){
    m_preset = Beltivator::kTOP;
  } else if(m_stick.GetXButtonPressed()){
    m_preset = Beltivator::kHALF;
  }
  m_beltivator.run(m_preset, m_stick.GetRightY());
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
