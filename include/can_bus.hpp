#pragma once

#include <condition_variable>
#include <optional>
#include <queue>
#include <mutex>

#include "can_frame.hpp"

class CANBus
{
public:
    void send(const CANFrame &frame);

    std::optional<CANFrame> receive();

    bool empty() const;

    void shutdown();

private:
    std::queue<CANFrame> messages;
    mutable std::mutex mutex;
    std::condition_variable condition;
    bool stopped = false;
};