#pragma once

#include "ecu.hpp"

class BrakeECU : public ECU
{
public:
    BrakeECU();

    void process() override;
};