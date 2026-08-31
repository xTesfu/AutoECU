#pragma once

#include <string>

enum class Severity
{
    INFO,
    WARNING,
    CRITICAL
};

struct DiagnosticTroubleCode
{
    std::string code;
    std::string description;
    Severity severity;
};