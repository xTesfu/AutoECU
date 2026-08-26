#include <iostream>

#include "can_frame.hpp"

int main() {
    CANFrame frame;

    frame.id = 0x101;
    frame.dlc = 2;

    frame.data[0] = 0x09;
    frame.data[1] = 0x8A;

     printFrame(frame);

    return 0;
}