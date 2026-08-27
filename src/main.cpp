#include <iostream>
#include <vector>

#include "can_bus.hpp"
#include "engine_ecu.hpp"
#include "brake_ecu.hpp"
#include "steering_ecu.hpp"

int main()
{
    CANBus bus;

    EngineECU engine(bus);
    engine.setRPM(3000);

    BrakeECU brake(bus);
    SteeringECU steering(bus);

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