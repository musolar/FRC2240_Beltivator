# FRC2240_Beltivator
### Status:
Currently mostly working, only thing left to do is determine PID constants on real hardware
### Test setup:
Note: you MUST input PID constants via SmartDashboard before enabling. This will be changed later.

Controls:
- Y: go to top
- X: go to half
- A: go to bottom
- Right joystick (up/down): manual control

### Constants:
Beltivator.h:
```
const double kMAX_POS;             // fully extended position (# of rotations)
const double kMIN_POS;             // fully retracted position (# of rotations)
const double kPRESETS[3];          // array of presets (# of rotations) - maps to PRESET enum
const double kJOYSTICK_THRESHOLD;  // threshold to consider joystick active
const double kVEL_MULT = 1.0;      // throttle multiplier for joystick control
```
BeltivatorMotors.h:
```
const int m_currentLimit;  // max current limit **PER MOTOR** (Amps) 
```