#include "brake_ecu.hpp"

#include <cstdint>

#include "can_frame.hpp"
#include "can_bus.hpp"
#include "can_ids.hpp"
#include "logger.hpp"
#include "diagnostic_codes.hpp"

BrakeECU::BrakeECU(CANBus &bus)
    : ECU("Brake ECU", bus), bus(bus), state(BrakeState::NORMAL)
{
    bus.registerReceiver(receiver);
}

void BrakeECU::process()
{
    auto frame = receiver.receive();

    if (frame.has_value())
    {
        if (frame->id == CANId::ENGINE_DATA &&
            frame->dlc >= 4)
        {
            uint16_t rpm =
                (static_cast<uint16_t>(frame->data[0]) << 8) |
                static_cast<uint16_t>(frame->data[1]);

            uint8_t speed = frame->data[2];

            Logger::info(
                "Brake ECU received engine data. Engine RPM: " +
                std::to_string(rpm) +
                ", Vehicle Speed: " +
                std::to_string(speed) +
                " km/h");

            if (speed >= 30)
            {
                state = BrakeState::HIGH_SPEED;
            }
            else
            {
                state = BrakeState::NORMAL;
            }

            if (state == BrakeState::HIGH_SPEED)
            {
                Logger::info("Brake ECU: High-speed monitoring");
            }
            else
            {
                Logger::info("Brake ECU: Normal");
            }

            if (speed >= 30)
            {
                CANFrame diagnosticFrame;

                diagnosticFrame.id = CANId::DIAGNOSTIC;
                diagnosticFrame.dlc = 1;
                diagnosticFrame.data[0] = DiagnosticCode::BRAKE_SYSTEM_FAULT;

                bus.send(diagnosticFrame);
            }
        }
    }
}