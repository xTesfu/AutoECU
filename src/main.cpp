#include <iostream>
#include <vector>

#include "engine_ecu.hpp"
#include "brake_ecu.hpp"
#include "steering_ecu.hpp"

int main()
{
    EngineECU engine;
    BrakeECU brake;
    SteeringECU steering;

    std::vector<ECU *> ecus = {
        &engine,
        &brake,
        &steering};

    for (ECU *ecu : ecus)
    {
        ecu->process();
    }

    return 0;
}