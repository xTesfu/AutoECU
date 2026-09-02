#include "steering_ecu.hpp"

#include "can_bus.hpp"
#include "can_ids.hpp"
#include "logger.hpp"
#include "diagnostic_codes.hpp"

SteeringECU::SteeringECU(CANBus &bus)
    : ECU("Steering ECU", bus), bus(bus), state(SteeringState::NORMAL)
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

            uint8_t speed = frame->data[2];

            Logger::info(
                "Steering ECU received engine data. Engine RPM: " +
                std::to_string(rpm) +
                ", Vehicle Speed: " +
                std::to_string(speed) +
                " km/h");

            if (speed >= 30)
            {
                state = SteeringState::HIGH_SPEED;
            }
            else
            {
                state = SteeringState::NORMAL;
            }

            if (state == SteeringState::HIGH_SPEED)
            {
                Logger::info("Steering ECU: High-speed steering mode");
            }
            else
            {
                Logger::info("Steering ECU: Normal steering");
            }

            if (rpm >= 2500)
            {
                CANFrame diagnosticFrame;

                diagnosticFrame.id = CANId::DIAGNOSTIC;
                diagnosticFrame.dlc = 1;
                diagnosticFrame.data[0] =
                    DiagnosticCode::STEERING_SENSOR_FAULT;

                bus.send(diagnosticFrame);
            }

            if (steeringSensorFailure)
            {
                CANFrame diagnosticFrame;

                diagnosticFrame.id = CANId::DIAGNOSTIC;
                diagnosticFrame.dlc = 1;
                diagnosticFrame.data[0] =
                    DiagnosticCode::STEERING_SENSOR_FAULT;

                bus.send(diagnosticFrame);
            }
        }
    }
}

void SteeringECU::updateFromVehicle(const VehicleState &vehicleState)
{
    steeringSensorFailure = vehicleState.steeringSensorFailure;
}