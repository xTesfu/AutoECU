#pragma once

#include "ecu.hpp"

class EngineECU : public ECU
{
public:
    EngineECU();

    void process() override;
};