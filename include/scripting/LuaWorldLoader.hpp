#pragma once
#include <string>
#include "sol.hpp"
#include "core/Manager.hpp"
#include "core/LuaAccessor.hpp"
#include "components/World.hpp"

namespace Garden::Scripting
{
    class LuaWorldLoader
    {
        friend Garden::Core::LuaAccessor;
        static Garden::Components::World *loadWorld(Manager *manager, const sol::table &rootTable, const std::string &mapFolderName);
        static void loadLayer(Manager *manager, const sol::table &layerNode, Garden::Components::World *world);
    };
} // namespace Garden::Scripting