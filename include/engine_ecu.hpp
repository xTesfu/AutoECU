#pragma once

#include "ecu.hpp"

class EngineECU : public ECU
{
public:
    EngineECU(CANBus &bus);

    void process() override;

    void setRPM(uint16_t rpm);

private:
    uint16_t rpm;
};