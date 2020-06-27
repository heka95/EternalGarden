#include "managers/GameManager.hpp"
#include "core/ECSTypes.hpp"
#include "systems/InputSystem.hpp"
#include "systems/Render.hpp"
#include "systems/AnimatorSystem.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/CameraSystem.hpp"
#include "GraphicWindow.hpp"

namespace Garden::Managers
{
    GameManager::GameManager(SDL_Renderer *sdlRenderer, SDL_Rect viewbox) : Manager()
    {
        m_camera = new Garden::Components::CameraComponent();
        m_camera->viewBox = viewbox;
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
        m_camera->sceneWidth = (m_world->columns * m_world->tileWidth);
        m_camera->sceneHeight = (m_world->rows * m_world->tileHeight);

        createStoreFor(Garden::Types::TransformationType);
        createStoreFor(Garden::Types::SpriteRendererType);
        createStoreFor(Garden::Types::SpriteAnimationType);
        createStoreFor(Garden::Types::PlayerCommandType);
        createStoreFor(Garden::Types::RigidBodyType);

        addSystem<Garden::Systems::CameraSystem>(1, this, m_camera);
        addSystem<Garden::Systems::InputSystem>(2, this);
        addSystem<Garden::Systems::PhysicSystem>(3, this);
        addSystem<Garden::Systems::Render>(4, this, sdlRenderer, m_textureStore, m_world, m_camera);
        addSystem<Garden::Systems::AnimatorSystem>(5, this);
        initSystems();

        auto player = m_lua->createObject("entity", "player");
        m_camera->target = player;
    }
} // namespace Garden::Managers