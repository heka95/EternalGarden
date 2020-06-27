#pragma once
#include <string>
#include "sol.hpp"
#include "core/Manager.hpp"
#include "core/LuaAccessor.hpp"


namespace Garden::Scripting
{
    class LuaComponentFactory
    {
        friend Garden::Core::LuaAccessor;
        static void buildTransformation(Manager *manager, Garden::Entity entity, const sol::table &parentTable);
        static sol::table hasElement(const sol::table &object, const std::string &property);
        static Entity buildEntity(Manager *manager, const sol::table &parentTable);
        static void buildSpriteRenderer(Manager *manager, Garden::Entity entity, const sol::table &parentTable);
        static void buildSpriteAnimations(Manager *manager, Garden::Entity entity, const sol::table &parentTable);
        static void buildRigidBody(Manager *manager, Garden::Entity entity, const sol::table &parentTable);
        static void buildPlayerCommand(Manager *manager, Garden::Entity entity, const sol::table &parentTable);
    };
}