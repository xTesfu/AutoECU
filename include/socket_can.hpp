#pragma once

#include "can_frame.hpp"

class SocketCAN
{
public:
    explicit SocketCAN(const char *interfaceName);
    ~SocketCAN();

    bool send(const CANFrame &frame);
    bool receive(CANFrame &frame);

private:
    int socketFd;
};