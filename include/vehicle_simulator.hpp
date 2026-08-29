#pragma once

#include "vehicle_state.hpp"

class VehicleSimulator
{
public:
    VehicleSimulator();

    void update();

    const VehicleState &getState() const;

private:
    VehicleState state;
};