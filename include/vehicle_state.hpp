#pragma once
#include <cstdint>

struct VehicleState
{
    uint16_t engineRPM = 0;
    uint16_t vehicleSpeed = 0;
    uint16_t engineTemperature = 0;
};