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
#include "diagnostic_ecu.hpp"

int main(int argc, char *argv[])
{
    SocketCAN socketCan("vcan0");
    CANBus bus(&socketCan);

    VehicleSimulator simulator;

    if (argc == 4 &&
        std::string(argv[1]) == "fault" &&
        std::string(argv[2]) == "inject")
    {

        std::string fault = argv[3];
        if (fault == "engine-overheat")
        {
            simulator.injectEngineOverheat();

            std::cout << "Fault injected: Engine overheating\n";
            std::cout << "Vehicle mode: LIMP_HOME\n";
        }
        else if (fault == "brake-failure")
        {
            simulator.injectBrakeFailure();

            std::cout << "Fault injected: Brake failure\n";
        }
        else if (fault == "steering-sensor")
        {
            simulator.injectSteeringSensorFailure();

            std::cout << "Fault injected: Steering sensor failure\n";
        }
    }

    EngineECU engine(bus);
    BrakeECU brake(bus);
    SteeringECU steering(bus);
    DiagnosticECU diagnostic(bus);

    std::atomic<bool> running{true};

    std::thread engineThread([&]()
                             {
        auto nextCycle = std::chrono::steady_clock::now();

        while (running)
        {
            const VehicleState &vehicleState = simulator.getState();

            engine.updateFromVehicle(vehicleState);
            brake.updateFromVehicle(vehicleState);
            steering.updateFromVehicle(vehicleState);

            // engine.updateFromVehicle(simulator.getState());
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

    std::thread diagnosticThread([&]()
                                 {
    auto nextCycle = std::chrono::steady_clock::now();

    while (running)
    {
        diagnostic.process();

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
    diagnosticThread.join();
    canReceiveThread.join();

    return 0;
}