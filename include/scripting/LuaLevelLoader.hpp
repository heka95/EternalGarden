#pragma once
#include <string>
#include "sol.hpp"
#include "core/Manager.hpp"
#include "core/LuaAccessor.hpp"
#include "core/LevelDefinition.hpp"

namespace Garden::Scripting
{
    class LuaLevelLoader
    {
        friend Garden::Core::LuaAccessor;
        static Garden::Core::LevelDefinition *loadLevel(Manager *manager, const sol::table &rootTable);
    };
} // namespace Garden::Scripting