#include "steering_ecu.hpp"

#include <iostream>

SteeringECU::SteeringECU(CANBus &bus)
    : ECU("Steering ECU", bus)
{
}

void SteeringECU::process()
{
    std::cout << "Steering ECU is Processing..." << std::endl;
}