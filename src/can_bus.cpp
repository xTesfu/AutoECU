#include "can_bus.hpp"

void CANBus::send(const CANFrame &frame)
{
    std::lock_guard<std::mutex> lock(mutex);
    messages.push(frame);

    condition.notify_one();
}

std::optional<CANFrame> CANBus::receive()
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

bool CANBus::empty() const
{
    std::lock_guard<std::mutex> lock(mutex);
    return messages.empty();
}

void CANBus::shutdown()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        stopped = true;
    }

    condition.notify_all();
}