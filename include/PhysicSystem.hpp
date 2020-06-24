#pragma once

#include "Core.hpp"
#include "Components.hpp"

namespace Garden::Systems
{
    class PhysicSystem : public Garden::System
    {
    public:
        PhysicSystem(Manager *manager) : System(2, {Garden::Components::RigidBodyType}, manager)
        {
        }
        virtual void updateEntity(float deltaTime, Entity e) override;
    };
} // namespace Garden::Systems