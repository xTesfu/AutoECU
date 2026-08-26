#include "can_bus.hpp"

void CANBus::send(const CANFrame& frame) {
    messages.push(frame);
}

std::optional<CANFrame> CANBus::receive() {
    if (messages.empty()) {
        return std::nullopt;
    }

    CANFrame frame = messages.front();
    messages.pop();

    return frame;
}