#pragma once

#include "ecu.hpp"
#include "can_receiver.hpp"
#include "vehicle_state.hpp"

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

    void updateFromVehicle(const VehicleState &state);

private:
    CANBus &bus;
    CANReceiver receiver;
    BrakeState state;

    bool brakeFailure = false;
};