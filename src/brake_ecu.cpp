#include "brake_ecu.hpp"

#include <iostream>
#include <cstdint>

#include "can_frame.hpp"
#include "can_bus.hpp"
#include "can_ids.hpp"

BrakeECU::BrakeECU(CANBus &bus)
    : ECU("Brake ECU", bus)
{
}

void BrakeECU::process()
{
    auto frame = bus.receive();

    if (frame.has_value())
    {
        if (frame->id == CANId::ENGINE_DATA)
        {
            std::cout << "Brake ECU received engine data." << std::endl;

            uint16_t rpm =
                (static_cast<uint16_t>(frame->data[0]) << 8) | static_cast<uint16_t>(frame->data[1]);

            std::cout << "Engine RPM: " << rpm << std::endl;
        }
    }
}