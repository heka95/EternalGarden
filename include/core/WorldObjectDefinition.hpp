#pragma once

#include <string>
#include <vector>

namespace Garden::Core
{
    class WorldObjectDefinition
    {
        public:
        std::string name{""};
        std::string type{""};
        int spawnX{0};
        int spawnY{0};
        int width{0};
        int height{0};
        int rotation{0};
        int imageId{0};
        bool isCameraTarget{false};
    };
} // namespace Garden::Core