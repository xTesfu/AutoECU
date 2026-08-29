#pragma once

#include <condition_variable>
#include <optional>
#include <queue>
#include <mutex>
#include <vector>
#include <memory>

#include "can_frame.hpp"
#include "can_receiver.hpp"
#include "socket_can.hpp"

class CANBus
{
public:
    explicit CANBus(SocketCAN *socketCan = nullptr);

    void send(const CANFrame &frame);

    std::optional<CANFrame> receive();

    bool empty() const;

    void shutdown();

    void registerReceiver(CANReceiver &receiver);

    void receiveFromSocketCAN();

private:
    std::queue<CANFrame> messages;
    mutable std::mutex mutex;
    std::condition_variable condition;
    bool stopped = false;
    std::vector<CANReceiver *> receivers;

    SocketCAN *socketCan;
};