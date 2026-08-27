#include "brake_ecu.hpp"

#include <iostream>

BrakeECU::BrakeECU()
    : ECU("Brake ECU")
{
}

void BrakeECU::process()
{
    std::cout << "Brake ECU is Processing..." << std::endl;
}