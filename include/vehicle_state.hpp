#pragma once
#include <cstdint>

enum class VehicleMode
{
    NORMAL,
    LIMP_HOME
};

struct VehicleState
{
    uint16_t engineRPM = 0;
    uint16_t vehicleSpeed = 0;
    uint16_t engineTemperature = 0;

    VehicleMode mode = VehicleMode::NORMAL;
    bool brakeFailure = false;
    bool steeringSensorFailure = false;
};