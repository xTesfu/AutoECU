#include "steering_ecu.hpp"

#include "can_bus.hpp"
#include "can_ids.hpp"
#include "logger.hpp"

SteeringECU::SteeringECU(CANBus &bus)
    : ECU("Steering ECU", bus), bus(bus)
{
    bus.registerReceiver(receiver);
}

void SteeringECU::process()
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
                "Steering ECU received engine data. Engine RPM: " +
                std::to_string(rpm));
        }
    }
}