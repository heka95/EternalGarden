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
        load(sdlRenderer);
    }

    void GameManager::load(SDL_Renderer *sdlRenderer)
    {
        createStoreFor(Garden::Types::TransformationType);
        createStoreFor(Garden::Types::SpriteRendererType);
        createStoreFor(Garden::Types::SpriteAnimationType);
        createStoreFor(Garden::Types::PlayerCommandType);
        createStoreFor(Garden::Types::RigidBodyType);

        addSystem<Garden::Systems::InputSystem>(this);
        addSystem<Garden::Systems::Render>(this, sdlRenderer);
        addSystem<Garden::Systems::AnimatorSystem>(this);
        addSystem<Garden::Systems::PhysicSystem>(this);
        initSystems();
    }
} // namespace Garden::Managers