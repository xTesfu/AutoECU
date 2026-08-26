#include "can_frame.hpp"

#include <iomanip>
#include <iostream>

void printFrame(const CANFrame& frame) {
    std::cout << "CAN ID: 0x"
              << std::hex << frame.id << std::endl;

    std::cout << "DLC: "
              << std::dec << static_cast<int>(frame.dlc)
              << std::endl;

    std::cout << "DATA: ";

    for (int i = 0; i < frame.dlc; ++i) {
        std::cout << std::hex
                  << std::setw(2)
                  << std::setfill('0')
                  << static_cast<int>(frame.data[i])
                  << " ";
    }

    std::cout << std::endl;
}