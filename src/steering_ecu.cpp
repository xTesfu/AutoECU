#include "steering_ecu.hpp"

#include <iostream>

SteeringECU::SteeringECU()
    : ECU("Steering ECU")
{
}

void SteeringECU::process()
{
    std::cout << "Steering ECU is Processing..." << std::endl;
}