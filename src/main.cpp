#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

#include "can_bus.hpp"
#include "engine_ecu.hpp"
#include "brake_ecu.hpp"
#include "steering_ecu.hpp"
#include "vehicle_simulator.hpp"
#include "socket_can.hpp"

int main()
{
    // CANBus bus;
    SocketCAN socketCan("vcan0");
    CANBus bus(&socketCan);

    VehicleSimulator simulator;

    EngineECU engine(bus);
    BrakeECU brake(bus);
    SteeringECU steering(bus);

    std::atomic<bool> running{true};

    std::thread engineThread([&]()
                             {
        auto nextCycle = std::chrono::steady_clock::now();

        while (running)
        {
            engine.updateFromVehicle(simulator.getState());
            engine.process();
            
            simulator.update();

            nextCycle += std::chrono::milliseconds(500);

            std::this_thread::sleep_until(nextCycle);
        } });

    std::thread brakeThread([&]()
                            {
        auto nextCycle = std::chrono::steady_clock::now();

        while (running) {
            brake.process();

            nextCycle += std::chrono::milliseconds(100);

            std::this_thread::sleep_until(nextCycle);
        } });

    std::thread steeringThread([&]()
                               {
    auto nextCycle = std::chrono::steady_clock::now();

    while (running) {
        steering.process();

        nextCycle += std::chrono::milliseconds(100);
        std::this_thread::sleep_until(nextCycle);
    } });

    std::thread canReceiveThread([&]()
                                 {
    while (running)
    {
        bus.receiveFromSocketCAN();
    } });

    std::this_thread::sleep_for(
        std::chrono::seconds(5));

    running = false;
    bus.shutdown();

    engineThread.join();
    brakeThread.join();
    steeringThread.join();
    canReceiveThread.join();

    return 0;
}