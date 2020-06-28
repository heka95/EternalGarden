#include "systems/PhysicSystem.hpp"
#include "core/Manager.hpp"
#include "components/Transformation.hpp"

namespace Garden::Systems
{
    void PhysicSystem::updateEntity(float deltaTime, Entity e)
    {
        auto bodyComponent = getManager()->getComponent<Garden::Components::RigidBody>(e);
        bodyComponent->acceleration.X = (bodyComponent->force.X + bodyComponent->friction.X) / bodyComponent->mass;
        bodyComponent->acceleration.Y = bodyComponent->gravity + bodyComponent->force.Y / bodyComponent->mass;
        bodyComponent->velocity = bodyComponent->acceleration * deltaTime;
        bodyComponent->position = bodyComponent->velocity * deltaTime;

        auto transformComponent = getManager()->getComponent<Garden::Components::Transform>(e);
        transformComponent->Position += bodyComponent->position;

        if (transformComponent->Position.X < 0)
            transformComponent->Position.X = 0;
        if (transformComponent->Position.Y < 0)
            transformComponent->Position.Y = 0;
        if (transformComponent->Position.X > m_camera->sceneWidth)
            transformComponent->Position.X = m_camera->sceneWidth;
        // workaround - in future, substract not 128 but only the entity height
        if (transformComponent->Position.Y > m_camera->sceneHeight - 128)
            transformComponent->Position.Y = m_camera->sceneHeight - 128;
    }
} // namespace Garden::Systems