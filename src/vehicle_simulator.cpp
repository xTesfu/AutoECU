#include "vehicle_simulator.hpp"

VehicleSimulator::VehicleSimulator()
{
    state.engineRPM = 1000;
    state.vehicleSpeed = 0;
}

void VehicleSimulator::update()
{
    if (state.engineRPM >= 3000)
    {
        state.engineRPM = 1000;
        state.vehicleSpeed = 0;
    }
    else
    {
        state.engineRPM += 500;
        state.vehicleSpeed += 10;
    }
}

const VehicleState &VehicleSimulator::getState() const
{
    return state;
}