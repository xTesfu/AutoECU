#include "ecu.hpp"

ECU::ECU(const std::string &name, CANBus &bus)
    : name(name), bus(bus)
{
}

const std::string &ECU::getName() const
{
    return name;
}

void ECU::process()
{
}