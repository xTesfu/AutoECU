#include <iostream>

#include "socket_can.hpp"

int main()
{
    SocketCAN socketCan("vcan0");

    CANFrame frame;

    std::cout << "Waiting for CAN frame..." << std::endl;

    if (socketCan.receive(frame))
    {
        std::cout << "Received CAN frame:" << std::endl;

        printFrame(frame);
    }
    else
    {
        std::cout << "Failed to receive CAN frame."
                  << std::endl;
    }

    return 0;
}