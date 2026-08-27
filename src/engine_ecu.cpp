#include <iostream>
#include "engine_ecu.hpp"

EngineECU::EngineECU()
    : ECU("Engine ECU")
{
}

void EngineECU::process()
{
    std::cout << "Engine ECU is Processing..." << std::endl;
}