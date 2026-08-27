#include <iostream>
#include "engine_ecu.hpp"
#include "can_bus.hpp"
#include "can_ids.hpp"

EngineECU::EngineECU(CANBus &bus)
    : ECU("Engine ECU", bus), rpm(0)
{
}

void EngineECU::setRPM(uint16_t rpm)
{
    this->rpm = rpm;
}

void EngineECU::process()
{
    CANFrame frame;

    frame.id = CANId::ENGINE_DATA;
    frame.dlc = 2;

    frame.data[0] = static_cast<uint8_t>(rpm >> 8);
    frame.data[1] = static_cast<uint8_t>(rpm & 0xFF);

    bus.send(frame);
}