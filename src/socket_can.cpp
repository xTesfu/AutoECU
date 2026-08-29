#include "socket_can.hpp"

#include <cstring>
#include <iostream>

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/time.h>

#include <linux/can.h>
#include <linux/can/raw.h>

SocketCAN::SocketCAN(const char *interfaceName)
    : socketFd(-1)
{
    socketFd = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (socketFd < 0)
    {
        std::cerr << "Failed to create CAN socket." << std::endl;
        return;
    }

    struct ifreq interfaceRequest{};
    std::strncpy(
        interfaceRequest.ifr_name,
        interfaceName,
        IFNAMSIZ - 1);

    if (ioctl(
            socketFd,
            SIOCGIFINDEX,
            &interfaceRequest) < 0)
    {
        std::cerr << "Failed to find CAN interface."
                  << std::endl;

        close(socketFd);
        socketFd = -1;
        return;
    }

    struct sockaddr_can address{};
    address.can_family = AF_CAN;
    address.can_ifindex = interfaceRequest.ifr_ifindex;

    if (bind(
            socketFd,
            reinterpret_cast<struct sockaddr *>(&address),
            sizeof(address)) < 0)
    {
        std::cerr << "Failed to bind CAN socket."
                  << std::endl;

        close(socketFd);
        socketFd = -1;
        return;
    }

    struct timeval timeout{};
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;

    setsockopt(
        socketFd,
        SOL_SOCKET,
        SO_RCVTIMEO,
        &timeout,
        sizeof(timeout));
}

SocketCAN::~SocketCAN()
{
    if (socketFd >= 0)
    {
        close(socketFd);
    }
}

bool SocketCAN::send(const CANFrame &frame)
{
    if (socketFd < 0)
    {
        return false;
    }

    struct can_frame canFrame{};

    canFrame.can_id = frame.id;
    canFrame.can_dlc = frame.dlc;

    for (int i = 0; i < frame.dlc; ++i)
    {
        canFrame.data[i] = frame.data[i];
    }

    ssize_t bytesWritten =
        write(
            socketFd,
            &canFrame,
            sizeof(canFrame));

    return bytesWritten == sizeof(canFrame);
}

bool SocketCAN::receive(CANFrame &frame)
{
    if (socketFd < 0)
    {
        return false;
    }

    struct can_frame canFrame{};

    ssize_t bytesRead =
        read(
            socketFd,
            &canFrame,
            sizeof(canFrame));

    if (bytesRead != sizeof(canFrame))
    {
        return false;
    }

    frame.id = canFrame.can_id;
    frame.dlc = canFrame.can_dlc;

    for (int i = 0; i < frame.dlc; ++i)
    {
        frame.data[i] = canFrame.data[i];
    }

    return true;
}