#pragma once

#include "can_frame.hpp"

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

class CANReceiver
{
public:
    void push(const CANFrame &frame);

    std::optional<CANFrame> receive();

    void shutdown();

private:
    std::queue<CANFrame> messages;

    std::mutex mutex;
    std::condition_variable condition;

    bool stopped = false;
};