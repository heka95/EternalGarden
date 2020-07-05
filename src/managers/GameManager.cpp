#include "managers/GameManager.hpp"
#include "core/ECSTypes.hpp"
#include "systems/InputSystem.hpp"
#include "systems/Render.hpp"
#include "systems/AnimatorSystem.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/CameraSystem.hpp"
#include "systems/SoundSystem.hpp"
#include "systems/TextSystem.hpp"
#include "GraphicWindow.hpp"
#include <algorithm>

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
        m_definition = m_lua->loadLevel(level); // obsolete ?
        m_world = m_lua->loadWorld(m_definition->mapFile);
        m_world->debug = m_definition->debugMode;
        m_camera->sceneWidth = (m_world->columns * m_world->tileWidth);
        m_camera->sceneHeight = (m_world->rows * m_world->tileHeight);

        createStoreFor(Garden::Types::TransformationType);
        createStoreFor(Garden::Types::SpriteRendererType);
        createStoreFor(Garden::Types::SpriteAnimationType);
        createStoreFor(Garden::Types::PlayerCommandType);
        createStoreFor(Garden::Types::RigidBodyType);

        addSystem<Garden::Systems::SoundSystem>(0, this);
        addSystem<Garden::Systems::CameraSystem>(1, this, m_camera);
        addSystem<Garden::Systems::InputSystem>(2, this, m_camera, m_graphicWindow);
        addSystem<Garden::Systems::PhysicSystem>(3, this, m_camera, m_world, sdlRenderer);
        addSystem<Garden::Systems::Render>(4, this, sdlRenderer, m_textureStore, m_world, m_camera);
        addSystem<Garden::Systems::TextSystem>(5, this, sdlRenderer);
        addSystem<Garden::Systems::AnimatorSystem>(6, this);

        initSystems();

        registerHandler<Garden::DebugToggleEvent>(&GameManager::onDebugToggle, this);

        for (auto entity : m_world->entities)
        {
            if (entity.type == "entity")
            {
                auto entityId = m_lua->createObject(entity.type, entity.name, entity.spawnX, entity.spawnY);
                if (entity.isCameraTarget)
                {
                    m_camera->target = entityId;
                }
                continue;
            }
            if (entity.type == "background")
            {
                auto newEntity = this->createEntity();
                auto transformation = new Garden::Components::Transform();
                transformation->Position = Garden::Vector2D{(float)entity.spawnX, (float)entity.spawnY};
                this->addComponent(newEntity, transformation);
                auto renderer = new Garden::Components::SpriteRenderer();
                renderer->width = entity.width;
                renderer->height = entity.height;
                renderer->drawHeight = renderer->height;
                renderer->drawWidth = renderer->width;
                renderer->scale = Garden::Vector2D{1.0f, 1.0f};
                renderer->textureId = entity.name;
                renderer->flip = SDL_RendererFlip::SDL_FLIP_NONE;
                renderer->origin.X = renderer->width / 2;
                renderer->origin.Y = renderer->height / 2;
                this->addComponent(newEntity, renderer);
                //this->subscribeEntity(newEntity);
                m_world->backgrounds.push_back(newEntity);
            }
        }
    }

    Garden::EventStatus GameManager::onDebugToggle(Garden::Entity source, Garden::EventType type, Garden::Event *event)
    {
        assert(type == Garden::DebugToggleEvent::type);
        m_world->debug = !m_world->debug;
        return Garden::EventStatus::KEEP_AFTER_CALL;
    }
} // namespace Garden::Managers