#pragma once

#include "components/World.hpp"
#include "systems/System.hpp"

namespace Garden::Systems
{
    class CameraSystem : public Garden::System
    {
    public:
        CameraSystem(int priority, Manager *manager) : System(priority, {Garden::Components::World::type}, manager)
        {
        }
        virtual void updateEntity(float deltaTime, Entity e) override;
    };
} // namespace Garden::Systems