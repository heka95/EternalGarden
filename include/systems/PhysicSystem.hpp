#pragma once

#include "SDL.h"
#include "components/RigidBody.hpp"
#include "systems/System.hpp"
#include "components/CameraComponent.hpp"
#include "components/World.hpp"
#include "core/CollisionEngine.hpp"

namespace Garden::Systems
{
    class PhysicSystem : public Garden::System
    {
    public:
        PhysicSystem(int priority, Manager *manager, Garden::Components::CameraComponent *camera, Garden::Components::World *world, SDL_Renderer *renderer)
            : System(priority, {Garden::Components::RigidBody::type}, manager)
        {
            m_renderer = renderer;
            m_world = world;
            m_camera = camera;
            m_collisionEngine.reset(new Garden::Core::CollisionEngine{m_world});
        }
        virtual void updateEntity(float deltaTime, Entity e) override;
        virtual void postUpdate(float delta) override;

    private:
        Garden::Components::CameraComponent *m_camera;
        Garden::Components::World *m_world;
        std::unique_ptr<Garden::Core::CollisionEngine> m_collisionEngine;
        SDL_Renderer *m_renderer;
    };
} // namespace Garden::Systems