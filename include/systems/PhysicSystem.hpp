#pragma once

#include "components/RigidBody.hpp"
#include "systems/System.hpp"
#include "components/CameraComponent.hpp"

namespace Garden::Systems
{
    class PhysicSystem : public Garden::System
    {
    public:
        PhysicSystem(int priority, Manager *manager, Garden::Components::CameraComponent *camera) : System(priority, {Garden::Components::RigidBody::type}, manager)
        {
            m_camera = camera;
        }
        virtual void updateEntity(float deltaTime, Entity e) override;

    private:
        Garden::Components::CameraComponent *m_camera;
    };
} // namespace Garden::Systems