// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include <iostream>

#include "Robot.h"
#include "Beltivator/BeltivatorMotors.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  frc::SmartDashboard::PutNumber("P", 0.0);
  frc::SmartDashboard::PutNumber("I", 0.0);
  frc::SmartDashboard::PutNumber("D", 0.0);
  frc::SmartDashboard::PutNumber("Iz", 0.0);
  frc::SmartDashboard::PutNumber("FF", 0.0);
  frc::SmartDashboard::PutNumber("MinO", -1.0);
  frc::SmartDashboard::PutNumber("MaxO", 1.0);
}

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

  Constants::pidCoeff debugPid = {
    frc::SmartDashboard::GetNumber("P", 0.0),
    frc::SmartDashboard::GetNumber("I", 0.0),
    frc::SmartDashboard::GetNumber("D", 0.0),
    frc::SmartDashboard::GetNumber("Iz", 0.0),
    frc::SmartDashboard::GetNumber("FF", 0.0),
    frc::SmartDashboard::GetNumber("MinO", -1.0),
    frc::SmartDashboard::GetNumber("MaxO", 1.0)
  };

  m_beltivator.setPidCoeff(debugPid);
  m_preset = Beltivator::kNONE;
}

void Robot::TeleopPeriodic() {
  if(m_stick.GetAButtonPressed()){
    frc::SmartDashboard::PutString("PrintMessage", "Bottom");
    m_preset = Beltivator::kBOTTOM;
  } else if(m_stick.GetYButtonPressed()){
    frc::SmartDashboard::PutString("PrintMessage", "Top");
    m_preset = Beltivator::kTOP;
  } else if(m_stick.GetXButtonPressed()){
    frc::SmartDashboard::PutString("PrintMessage", "Half");
    m_preset = Beltivator::kHALF;
  }
  double right_y = -m_stick.GetRightY();
  if(abs(right_y) > 0.05) {
    m_preset = Beltivator::kNONE;
  }
  frc::SmartDashboard::PutNumber("RightY", right_y);
/*  if (m_stick.GetAButtonPressed())
  {
    testing = true;
  }
*/  if (testing)
  {
    //frc::SmartDashboard::PutBoolean("testing", testing);
    if (m_beltivator.m_motors.m_encoder.GetPosition() < 10)
    {
      right_y = .75;
      if (lock==false)
      {
        count++;
        lock = true;
      }
    }
    else if (m_beltivator.m_motors.m_encoder.GetPosition() > 95)
    {
      right_y = -.75;
      lock = false;
    }
     
  }
  m_beltivator.run(m_preset, right_y);
  
  frc::SmartDashboard::PutNumber("Preset", m_preset);
  frc::SmartDashboard::PutNumber("Position", m_beltivator.m_motors.m_encoder.GetPosition());
  frc::SmartDashboard::PutNumber("Count", count);
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
