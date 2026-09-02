#pragma once

#include "ecu.hpp"
#include "can_receiver.hpp"
#include "vehicle_state.hpp"

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

    void updateFromVehicle(const VehicleState &state);

private:
    CANBus &bus;
    CANReceiver receiver;
    SteeringState state;

    bool steeringSensorFailure = false;
};