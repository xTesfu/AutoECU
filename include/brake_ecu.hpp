#pragma once

#include "ecu.hpp"

class BrakeECU : public ECU
{
public:
    BrakeECU(CANBus &bus);

    void process() override;
};