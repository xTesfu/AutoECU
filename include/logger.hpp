#pragma once

#include <mutex>
#include <string>

class Logger
{
public:
    static void info(const std::string &message);

private:
    static std::mutex mutex;
};