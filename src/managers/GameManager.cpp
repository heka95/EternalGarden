#include "managers/GameManager.hpp"
#include "core/ECSTypes.hpp"
#include "systems/InputSystem.hpp"
#include "systems/Render.hpp"
#include "systems/AnimatorSystem.hpp"
#include "systems/PhysicSystem.hpp"

namespace Garden::Managers
{
    GameManager::GameManager(SDL_Renderer *sdlRenderer) : Manager()
    {
        m_textureStore = new Garden::Core::TextureStore(sdlRenderer);
        load(sdlRenderer);
    }

    GameManager::~GameManager()
    {
        delete m_lua;
    }

    void GameManager::load(SDL_Renderer *sdlRenderer)
    {
        createStoreFor(Garden::Types::TransformationType);
        createStoreFor(Garden::Types::SpriteRendererType);
        createStoreFor(Garden::Types::SpriteAnimationType);
        createStoreFor(Garden::Types::PlayerCommandType);
        createStoreFor(Garden::Types::RigidBodyType);

        addSystem<Garden::Systems::InputSystem>(this);
        addSystem<Garden::Systems::Render>(this, sdlRenderer, m_textureStore);
        addSystem<Garden::Systems::AnimatorSystem>(this);
        addSystem<Garden::Systems::PhysicSystem>(this);
        initSystems();

        m_lua = new Garden::Core::LuaAccessor(this);
        m_lua->createObject("entity", "player");
        m_world = m_lua->loadWorld("content/assets/graphics/maps/test_map.lua");

        // Temporary hard loading
        m_textureStore->load("player", "assets/player/idle.png");

    }
} // namespace Garden::Managers