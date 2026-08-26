#pragma once

#include <optional>
#include <queue>

#include "can_frame.hpp"

class CANBus {
public:
    void send(const CANFrame& frame);
    std::optional<CANFrame> receive();

private:
    std::queue<CANFrame> messages;
};