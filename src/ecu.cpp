#include "ecu.hpp"

ECU::ECU(const std::string &name)
    : name(name)
{
}

const std::string &ECU::getName() const
{
    return name;
}

void ECU::process()
{
}