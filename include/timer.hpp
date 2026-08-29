#pragma once

#include <chrono>

class Timer
{
public:
    Timer()
        : startTime(std::chrono::steady_clock::now())
    {
    }

    double elapsedMilliseconds() const
    {
        auto elapsed =
            std::chrono::steady_clock::now() - startTime;

        return std::chrono::duration<double, std::milli>(elapsed).count();
    }

private:
    std::chrono::steady_clock::time_point startTime;
};