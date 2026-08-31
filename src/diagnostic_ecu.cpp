#include "diagnostic_ecu.hpp"

#include "can_bus.hpp"
#include "can_ids.hpp"
#include "logger.hpp"
#include "diagnostic_codes.hpp"

std::string severityToString(Severity severity)
{
    switch (severity)
    {
    case Severity::INFO:
        return "INFO";

    case Severity::WARNING:
        return "WARNING";

    case Severity::CRITICAL:
        return "CRITICAL";
    }

    return "UNKNOWN";
}

DiagnosticECU::DiagnosticECU(CANBus &bus)
    : ECU("Diagnostic ECU", bus)
{
    bus.registerReceiver(receiver);
}

void DiagnosticECU::process()
{
    auto frame = receiver.receive();

    if (frame.has_value() &&
        frame->id == CANId::DIAGNOSTIC &&
        frame->dlc >= 1)
    {
        DiagnosticTroubleCode dtc;

        if (frame->data[0] == DiagnosticCode::ENGINE_OVERHEAT)
        {
            dtc = {
                "P0217",
                "Engine overheating",
                Severity::CRITICAL};
        }
        else if (frame->data[0] == DiagnosticCode::STEERING_SENSOR_FAULT)
        {
            dtc = {
                "C1234",
                "Steering sensor fault",
                Severity::WARNING};
        }
        else if (frame->data[0] == DiagnosticCode::BRAKE_SYSTEM_FAULT)
        {
            dtc = {
                "B0001",
                "Brake system fault",
                Severity::CRITICAL};
        }
        else
        {
            dtc = {
                "UNKNOWN",
                "Unknown diagnostic trouble code",
                Severity::INFO};
        }

        // troubleCodes.push_back(dtc);

        bool alreadyStored = false;

        for (const auto &storedDtc : troubleCodes)
        {
            if (storedDtc.code == dtc.code)
            {
                alreadyStored = true;
                break;
            }
        }

        if (!alreadyStored)
        {
            troubleCodes.push_back(dtc);
            Logger::info(
                "Diagnostic ECU: DTC " +
                dtc.code +
                " - " +
                dtc.description +
                " - " + severityToString(dtc.severity));
        }
    }
}