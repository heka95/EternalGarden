#include "core/LuaManager.hpp"
#include <memory>
#include <type_traits>
#include <utility>
#include <string>
#include "core/ECSTypes.hpp"
#include "components/BaseComponent.hpp"
#include "core/Manager.hpp"
#include "Vector2D.hpp"
#include "SDL.h"
#include "components/BaseComponent.hpp"

namespace Garden::Core
{
    LuaManager::LuaManager(Manager *manager)
    {
        m_manager = manager;
        m_lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::math, sol::lib::table);
        addContentPackage();
        registerBaseTypes();
    }

    LuaManager::~LuaManager()
    {
    }

    void LuaManager::executeScript(const std::string &fileName)
    {
        m_lua.script_file(fileName);
    }

    void LuaManager::addContentPackage()
    {
        const std::string package_path = m_lua["package"]["path"];
        m_lua["package"]["path"] = package_path + (!package_path.empty() ? ";" : "") + "content/scripts/" + "?.lua";
    }

    void LuaManager::registerBaseTypes()
    {
        m_lua.new_usertype<Garden::Entity>("entity");
        m_lua.new_usertype<Garden::ComponentType>("componentType");
        m_lua.new_usertype<Garden::BaseComponent>("component");
        m_lua.new_usertype<Garden::Manager>("manager", sol::constructors<void>(),
                                            "createEntity", &Garden::Manager::createEntity,
                                            "addComponent", &Garden::Manager::luaAddComponent,
                                            "registerEntity", &Garden::Manager::subscribeEntity);
        m_lua.new_usertype<Garden::Vector2D>("vector2D", sol::constructors<Garden::Vector2D(int, int)>(),
                                             "x", &Garden::Vector2D::X,
                                             "y", &Garden::Vector2D::Y);
        m_lua["RenderFlip"] = m_lua.create_table_with(
            "none", SDL_RendererFlip::SDL_FLIP_NONE,
            "horizontal", SDL_RendererFlip::SDL_FLIP_HORIZONTAL,
            "vertical", SDL_RendererFlip::SDL_FLIP_VERTICAL);

        m_lua["currentManager"] = m_manager;
    }
} // namespace Garden::Core