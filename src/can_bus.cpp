#include "can_bus.hpp"

void CANBus::send(const CANFrame &frame)
{
    std::vector<CANReceiver *> receiverList;

    {
        std::lock_guard<std::mutex> lock(mutex);
        receiverList = receivers;
    }

    for (CANReceiver *receiver : receiverList)
    {
        receiver->push(frame);
    }
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
    std::vector<CANReceiver *> receiverList;

    {
        std::lock_guard<std::mutex> lock(mutex);

        stopped = true;
        receiverList = receivers;
    }

    for (CANReceiver *receiver : receiverList)
    {
        receiver->shutdown();
    }

    condition.notify_all();
}

void CANBus::registerReceiver(CANReceiver &receiver)
{
    std::lock_guard<std::mutex> lock(mutex);

    receivers.push_back(&receiver);
}