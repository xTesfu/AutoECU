#include <atomic>
#include <chrono>
#include <thread>
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
    BrakeECU brake(bus);
    SteeringECU steering(bus);

    std::atomic<bool> running{true};

    std::thread engineThread([&]()
                             {
        int rpm = 1000;

        while (running) {
            engine.setRPM(rpm);
            engine.process();

            rpm += 500;

            if (rpm > 3000) {
                rpm = 1000;
            }

            std::this_thread::sleep_for(
                std::chrono::milliseconds(500)
            );
        } });

    std::thread brakeThread([&]()
                            {
        while (running) {
            brake.process();

            std::this_thread::sleep_for(
                std::chrono::milliseconds(100)
            );
        } });

    std::thread steeringThread([&]()
                               {
    while (running) {
        steering.process();
    } });

    std::this_thread::sleep_for(
        std::chrono::seconds(5));

    running = false;
    bus.shutdown();

    engineThread.join();
    brakeThread.join();
    steeringThread.join();

    return 0;
}