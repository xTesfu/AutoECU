#pragma once

#include "ecu.hpp"

class SteeringECU : public ECU
{
public:
    SteeringECU(CANBus &bus);

    void process() override;
};