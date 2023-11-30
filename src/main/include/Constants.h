#pragma once

namespace Constants {
    struct pidCoeff {
        double kP;
        double kI;
        double kD;
        double kIz;
        double kFF;
        double kMinOutput;
        double kMaxOutput;
    };
}