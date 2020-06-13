#if !defined(__CONFIGURATION__)
#define __CONFIGURATION__

#include <string>
#include "GameTypes.hpp"

namespace Garden
{
    struct Configuration
    {
        Size windowSize;
        std::string luaDirectory;
        std::string executionPath;
    };
} // namespace Garden

#endif