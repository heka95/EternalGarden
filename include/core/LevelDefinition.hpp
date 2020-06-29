#pragma once
#include <string>
#include <vector>

namespace Garden::Core
{
    class LevelDefinition
    {
    public:
        std::string mapFile{""};
        bool debugMode{false};
        std::vector<std::tuple<std::string, std::string>> entities;
    };
} // namespace Garden::Core