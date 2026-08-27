#pragma once

#include "ecu.hpp"

class SteeringECU : public ECU
{
public:
    SteeringECU();

    void process() override;
};