#pragma once

#include "vehicle_state.hpp"

class VehicleSimulator
{
public:
    VehicleSimulator();

    void update();

    const VehicleState &getState() const;

    void injectEngineOverheat();
    void injectBrakeFailure();
    void injectSteeringSensorFailure();

private:
    VehicleState state;
};