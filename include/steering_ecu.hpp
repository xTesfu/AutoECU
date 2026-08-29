#pragma once

#include "ecu.hpp"
#include "can_receiver.hpp"

class SteeringECU : public ECU
{
    enum class SteeringState
    {
        NORMAL,
        HIGH_SPEED
    };

public:
    SteeringECU(CANBus &bus);

    void process() override;

private:
    CANBus &bus;
    CANReceiver receiver;
    SteeringState state;
};