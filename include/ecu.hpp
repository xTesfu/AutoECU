#pragma once

#include <string>

class CANBus;

class ECU
{
public:
    ECU(const std::string &name, CANBus &bus);

    const std::string &getName() const;

    virtual void process();

protected:
    CANBus &bus;

private:
    std::string name;
};