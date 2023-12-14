// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include "Beltivator/Beltivator.h"
#include "rev/ColorSensorV3.h"
#include <frc/XboxController.h>
#include <frc/DriverStation.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;

 private:
  Beltivator m_beltivator;
  Beltivator::PRESET m_preset = Beltivator::kBOTTOM;
  frc::XboxController m_stick{0};
  bool testing = false;
  double right_y;
  int count = 0;
  bool lock = false;
  };