#include "brake_ecu.hpp"

#include <cstdint>

#include "can_frame.hpp"
#include "can_bus.hpp"
#include "can_ids.hpp"
#include "logger.hpp"

BrakeECU::BrakeECU(CANBus &bus)
    : ECU("Brake ECU", bus), bus(bus)
{
    bus.registerReceiver(receiver);
}

void BrakeECU::process()
{
    auto frame = receiver.receive();

    if (frame.has_value())
    {
        if (frame->id == CANId::ENGINE_DATA)
        {
            uint16_t rpm =
                (static_cast<uint16_t>(frame->data[0]) << 8) |
                static_cast<uint16_t>(frame->data[1]);

            Logger::info(
                "Brake ECU received engine data. Engine RPM: " +
                std::to_string(rpm));
        }
    }
}