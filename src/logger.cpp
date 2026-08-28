#include "logger.hpp"

#include <iostream>

std::mutex Logger::mutex;

void Logger::info(const std::string &message)
{
    std::lock_guard<std::mutex> lock(mutex);

    std::cout << message << std::endl;
}