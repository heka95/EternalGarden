#pragma once
#include <string>
#include "sol.hpp"
#include "core/Manager.hpp"
#include "components/World.hpp"
#include "core/LevelDefinition.hpp"

namespace Garden::Core
{
    class LuaAccessor
    {
    public:
        LuaAccessor(Manager *manager);
        ~LuaAccessor();
        void executeScript(const std::string &fileName);
        template <typename Class, typename... Args>
        void registerComponent(const std::string &name, Args &&... args)
        {
            static_assert(std::is_base_of<BaseComponent, Class>::value, "Class must be a Component");
            m_lua.new_usertype<Class>(name,
                                      sol::constructors<Class()>(),
                                      sol::base_classes, sol::bases<Garden::BaseComponent>(),
                                      std::forward<Args>(args)...);
        }

        template <typename Class, typename... Args>
        void registerObject(const std::string &name, Args &&... args)
        {
            static_assert(!std::is_base_of<BaseComponent, Class>::value, "Please use RegisterComponent when you register a component");
            m_lua.new_usertype<Class>(name, sol::constructors<Class()>(), std::forward<Args>(args)...);
        }
        Entity createObject(const std::string &category, const std::string &name, int spawnX, int spawnY);
        Garden::Components::World* loadWorld(const std::string &fileName);
        Garden::Core::LevelDefinition *loadLevel(const std::string &fileName);
    private:
        void addContentPackage(const std::string &folder);
        void registerComponents();
        void registerBaseTypes();
        sol::state m_lua;
        Manager *m_manager;
        sol::function m_funcGetObject;
    };
} // namespace Garden::Core