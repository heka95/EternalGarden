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
        m_camera = new Garden::Components::CameraComponent();
        m_textureStore = new Garden::Core::TextureStore(sdlRenderer);
        load(sdlRenderer);
    }

    GameManager::~GameManager()
    {
        delete m_lua;
        delete m_world;
        delete m_camera;
    }

    void GameManager::load(SDL_Renderer *sdlRenderer)
    {
        m_lua = new Garden::Core::LuaAccessor(this);
        m_world = m_lua->loadWorld("content/assets/graphics/maps/test_map.lua");

        createStoreFor(Garden::Types::TransformationType);
        createStoreFor(Garden::Types::SpriteRendererType);
        createStoreFor(Garden::Types::SpriteAnimationType);
        createStoreFor(Garden::Types::PlayerCommandType);
        createStoreFor(Garden::Types::RigidBodyType);

        addSystem<Garden::Systems::InputSystem>(2, this);
        addSystem<Garden::Systems::PhysicSystem>(3, this);
        addSystem<Garden::Systems::Render>(4, this, sdlRenderer, m_textureStore, m_world, m_camera);
        addSystem<Garden::Systems::AnimatorSystem>(5, this);
        initSystems();

        auto player = m_lua->createObject("entity", "player");
        auto playerPosition = getComponent<Garden::Components::Transform>(player)->Position;
        m_camera->target = &playerPosition;
    }
} // namespace Garden::Managers