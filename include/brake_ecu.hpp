#pragma once

#include "ecu.hpp"
#include "can_receiver.hpp"

class BrakeECU : public ECU
{
    enum class BrakeState
    {
        NORMAL,
        HIGH_SPEED
    };

public:
    BrakeECU(CANBus &bus);

    void process() override;

private:
    CANBus &bus;
    CANReceiver receiver;
    BrakeState state;
};