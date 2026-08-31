#include "vehicle_simulator.hpp"

VehicleSimulator::VehicleSimulator()
{
    state.engineRPM = 1000;
    state.vehicleSpeed = 0;
    state.engineTemperature = 80;
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

    // Engine temperature
    if (state.engineRPM >= 2500)
    {
        state.engineTemperature += 5;
    }
    else if (state.engineTemperature > 80)
    {
        state.engineTemperature -= 2;
    }
}

const VehicleState &VehicleSimulator::getState() const
{
    return state;
}