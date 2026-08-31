#pragma once

#include <vector>

#include "ecu.hpp"
#include "can_receiver.hpp"
#include "diagnostic_trouble_code.hpp"

class DiagnosticECU : public ECU
{
public:
    DiagnosticECU(CANBus &bus);

    void process() override;

private:
    CANReceiver receiver;
    std::vector<DiagnosticTroubleCode> troubleCodes;
};