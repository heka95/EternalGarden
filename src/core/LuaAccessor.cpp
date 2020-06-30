#include "core/LuaAccessor.hpp"
#include <memory>
#include <type_traits>
#include <utility>
#include <string>
#include <iostream>
#include "core/ECSTypes.hpp"
#include "components/BaseComponent.hpp"
#include "Vector2D.hpp"
#include "SDL.h"
#include "components/PlayerCommand.hpp"
#include "components/RigidBody.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/SpriteRenderer.hpp"
#include "components/Transformation.hpp"
#include "components/World.hpp"
#include "scripting/LuaComponentFactory.hpp"
#include "scripting/LuaWorldLoader.hpp"
#include "scripting/LuaLevelLoader.hpp"
#include "Utilities.hpp"

namespace Garden::Core
{
    LuaAccessor::LuaAccessor(Manager *manager)
    {
        m_manager = manager;
        m_lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::math, sol::lib::table);
        addContentPackage("content/scripts/");
        addContentPackage("content/scripts/levels");
        addContentPackage("content/scripts/templates");
        addContentPackage("content/scripts/utils");
        registerBaseTypes();
        registerComponents();
        executeScript("content/scripts/data.lua");
    }

    LuaAccessor::~LuaAccessor()
    {
    }

    void LuaAccessor::executeScript(const std::string &fileName)
    {
        m_lua.script_file(fileName);
        m_funcGetObject = m_lua["getobject"];
    }

    Garden::Core::LevelDefinition *LuaAccessor::loadLevel(const std::string &fileName)
    {
        sol::table result = m_lua.script_file(fileName);
        return Garden::Scripting::LuaLevelLoader::loadLevel(m_manager, result);
    }

    Garden::Components::World *LuaAccessor::loadWorld(const std::string &fileName)
    {
        sol::table result = m_lua.script_file(fileName);
        auto mapFolder = Utility::directoryNameof(fileName);
        return Garden::Scripting::LuaWorldLoader::loadWorld(m_manager, result, mapFolder);
    }

    Entity LuaAccessor::createObject(const std::string &category, const std::string &name)
    {
        sol::table object = m_funcGetObject(category, name);
        if (object == sol::nil || !object.valid())
        {
            std::cerr << "Object [" << category << "|" << name << "] not exists or registered on lua context !";
            return INVALID_ENTITY;
        }
        return Garden::Scripting::LuaComponentFactory::buildEntity(m_manager, object);
    }

    void LuaAccessor::addContentPackage(const std::string &folder)
    {
        const std::string package_path = m_lua["package"]["path"];
        m_lua["package"]["path"] = package_path + (!package_path.empty() ? ";" : "") + folder + "?.lua";
    }

    void LuaAccessor::registerComponents()
    {
    }

    void LuaAccessor::registerBaseTypes()
    {
        m_lua.new_enum("AnimationType",
                       "IDLE", Garden::Components::AnimationType::IDLE,
                       "RUN", Garden::Components::AnimationType::RUN,
                       "JUMP", Garden::Components::AnimationType::JUMP,
                       "ATTACK", Garden::Components::AnimationType::ATTACK,
                       "CROUCH", Garden::Components::AnimationType::CROUCH,
                       "FALL", Garden::Components::AnimationType::FALL);
    }
} // namespace Garden::Core