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
        /*
        registerComponent<Garden::Components::Transform>("Transform",
                                                         "Position", &Garden::Components::Transform::Position,
                                                         "type", &Garden::Components::Transform::getType);
        registerComponent<Garden::Components::SpriteRenderer>("SpriteRenderer",
                                                              "width", &Garden::Components::SpriteRenderer::width,
                                                              "height", &Garden::Components::SpriteRenderer::height,
                                                              "drawWidth", &Garden::Components::SpriteRenderer::drawWidth,
                                                              "drawHeight", &Garden::Components::SpriteRenderer::drawHeight,
                                                              "drawOffset", &Garden::Components::SpriteRenderer::drawOffset,
                                                              "rotation", &Garden::Components::SpriteRenderer::rotation,
                                                              "scale", &Garden::Components::SpriteRenderer::scale,
                                                              "origin", &Garden::Components::SpriteRenderer::origin,
                                                              "textureId", &Garden::Components::SpriteRenderer::textureId,
                                                              "flip", &Garden::Components::SpriteRenderer::flip,
                                                              "type", &Garden::Components::SpriteRenderer::getType);
        registerComponent<Garden::Components::SpriteAnimation>("SpriteAnimation",
                                                               "width", &Garden::Components::SpriteAnimation::width,
                                                               "height", &Garden::Components::SpriteAnimation::height,
                                                               "rowCount", &Garden::Components::SpriteAnimation::rowCount,
                                                               "frameCount", &Garden::Components::SpriteAnimation::frameCount,
                                                               "speed", &Garden::Components::SpriteAnimation::speed,
                                                               "loop", &Garden::Components::SpriteAnimation::loop,
                                                               "type", &Garden::Components::SpriteAnimation::getType);
        registerComponent<Garden::Components::PlayerCommand>("PlayerCommand",
                                                             "type", &Garden::Components::PlayerCommand::getType);
        registerComponent<Garden::Components::RigidBody>("RigidBody",
                                                         "mass", &Garden::Components::RigidBody::mass,
                                                         "gravity", &Garden::Components::RigidBody::gravity,
                                                         "force", &Garden::Components::RigidBody::force,
                                                         "friction", &Garden::Components::RigidBody::friction,
                                                         "position", &Garden::Components::RigidBody::position,
                                                         "velocity", &Garden::Components::RigidBody::velocity,
                                                         "acceleration", &Garden::Components::RigidBody::acceleration,
                                                         "type", &Garden::Components::RigidBody::getType);
                                                         */
    }

    void LuaAccessor::registerBaseTypes()
    {
        /*
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
        */
    }
} // namespace Garden::Core