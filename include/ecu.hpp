#pragma once

#include <string>

class ECU
{
public:
    ECU(const std::string &name);

    const std::string &getName() const;

private:
    std::string name;
};