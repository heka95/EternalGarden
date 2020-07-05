#pragma once

#include <string>
#include "SDL.h"

namespace Garden::Systems
{
    struct TextDefinition
    {
        SDL_Color color{0, 0, 0, 0};
        std::string message{""};
        std::string fontId{""};
        int positionX{0};
        int positionY{0};
        bool draw{false};
    };
}