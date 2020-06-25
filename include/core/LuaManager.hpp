#pragma once
#include <string>
#include "sol.hpp"
#include "core/Manager.hpp"

namespace Garden::Core
{
    class LuaManager
    {
    public:
        LuaManager(Manager *manager);
        ~LuaManager();
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

    private:
        void addContentPackage();
        void registerBaseTypes();
        sol::state m_lua;
        Manager const *m_manager;
    };
} // namespace Garden::Core