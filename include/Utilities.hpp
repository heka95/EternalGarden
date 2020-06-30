#pragma once
#include <string>

class Utility
{
public:
    static std::string directoryNameof(const std::string &fileName)
    {
        size_t position = fileName.find_last_of("\\/");
        return (std::string::npos == position) ? "" : fileName.substr(0, position);
    }
};