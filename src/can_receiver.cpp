#include "can_receiver.hpp"

void CANReceiver::push(const CANFrame &frame)
{
    std::lock_guard<std::mutex> lock(mutex);

    messages.push(frame);

    condition.notify_one();
}

std::optional<CANFrame> CANReceiver::receive()
{
    std::unique_lock<std::mutex> lock(mutex);

    condition.wait(lock, [this]()
                   { return !messages.empty() || stopped; });

    if (stopped && messages.empty())
    {
        return std::nullopt;
    }

    CANFrame frame = messages.front();
    messages.pop();

    return frame;
}

void CANReceiver::shutdown()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        stopped = true;
    }

    condition.notify_all();
}