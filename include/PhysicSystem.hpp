#pragma once

#include "RigidBody.hpp"
#include "System.hpp"

namespace Garden::Systems
{
    class PhysicSystem : public Garden::System
    {
    public:
        PhysicSystem(Manager *manager) : System(2, {Garden::Components::RigidBody::type}, manager)
        {
        }
        virtual void updateEntity(float deltaTime, Entity e) override;
    };
} // namespace Garden::Systems