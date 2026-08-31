#pragma once

#include "ecu.hpp"
#include "vehicle_state.hpp"

class EngineECU : public ECU
{
public:
    EngineECU(CANBus &bus);

    void process() override;

    void setRPM(uint16_t rpm);

    void updateFromVehicle(const VehicleState &state);

private:
    CANBus &bus;
    uint16_t rpm;
    uint16_t vehicleSpeed;
    uint16_t engineTemperature;
};