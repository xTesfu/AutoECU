#include <iostream>

#include "engine_ecu.hpp"

int main()
{
    EngineECU engine;

    ECU *ecu = &engine;

    ecu->process();

    return 0;
}