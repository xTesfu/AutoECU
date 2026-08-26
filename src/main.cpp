#include <iostream>

#include "can_frame.hpp"
#include "can_bus.hpp"

int main() {
    CANFrame frame;
    CANBus bus;

    frame.id = 0x101;
    frame.dlc = 2;

    frame.data[0] = 0x09;
    frame.data[1] = 0x8A;

    bus.send(frame);

    std::optional<CANFrame> receivedFrame = bus.receive();

    if (receivedFrame.has_value()) {
        printFrame(receivedFrame.value());
    }

    std::optional<CANFrame> secondFrame = bus.receive();

    if (!secondFrame.has_value()) {
        std::cout << "CAN bus is empty." << std::endl;
    }

    return 0;
}