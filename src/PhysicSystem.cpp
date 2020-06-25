#include "PhysicSystem.hpp"
#include "core/Manager.hpp"
#include "Transformation.hpp"

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
        transformComponent->Position.X += bodyComponent->position.X;
        transformComponent->Position.Y += bodyComponent->position.Y;
    }
} // namespace Garden::Systems