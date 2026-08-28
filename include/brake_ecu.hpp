#pragma once

#include "ecu.hpp"
#include "can_receiver.hpp"

class BrakeECU : public ECU
{
public:
    BrakeECU(CANBus &bus);

    void process() override;

private:
    CANBus &bus;
    CANReceiver receiver;
};