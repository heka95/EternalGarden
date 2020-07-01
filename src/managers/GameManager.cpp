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
    GameManager::GameManager(SDL_Renderer *sdlRenderer, SDL_Rect viewbox, std::string const &level, GraphicWindow *graphicWindow) : Manager()
    {
        m_graphicWindow = graphicWindow;
        m_camera = new Garden::Components::CameraComponent();
        m_camera->viewBox = viewbox;
        m_textureStore = new Garden::Core::TextureStore(sdlRenderer);
        load(sdlRenderer, level);
    }

    GameManager::~GameManager()
    {
        delete m_lua;
        delete m_world;
        delete m_camera;
    }

    void GameManager::load(SDL_Renderer *sdlRenderer, std::string const &level)
    {
        m_lua = new Garden::Core::LuaAccessor(this);
        m_definition = m_lua->loadLevel(level);
        m_world = m_lua->loadWorld(m_definition->mapFile);
        m_world->debug = m_definition->debugMode;
        m_camera->sceneWidth = (m_world->columns * m_world->tileWidth);
        m_camera->sceneHeight = (m_world->rows * m_world->tileHeight);

        createStoreFor(Garden::Types::TransformationType);
        createStoreFor(Garden::Types::SpriteRendererType);
        createStoreFor(Garden::Types::SpriteAnimationType);
        createStoreFor(Garden::Types::PlayerCommandType);
        createStoreFor(Garden::Types::RigidBodyType);

        addSystem<Garden::Systems::CameraSystem>(1, this, m_camera);
        addSystem<Garden::Systems::InputSystem>(2, this, m_camera, m_graphicWindow);
        addSystem<Garden::Systems::PhysicSystem>(3, this, m_camera, m_world, sdlRenderer);
        addSystem<Garden::Systems::Render>(4, this, sdlRenderer, m_textureStore, m_world, m_camera);
        addSystem<Garden::Systems::AnimatorSystem>(5, this);
        initSystems();

        for (auto &entity : m_definition->entities)
        {
            auto entityId = m_lua->createObject(std::get<0>(entity), std::get<1>(entity));
            if (std::get<0>(entity).compare("entity") == 0 && std::get<1>(entity).compare("player") == 0)
            {
                m_camera->target = entityId;
            }
        }
    }
} // namespace Garden::Managers