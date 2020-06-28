#include "systems/PhysicSystem.hpp"
#include "core/Manager.hpp"
#include "components/Transformation.hpp"

namespace Garden::Systems
{
    void PhysicSystem::updateEntity(float deltaTime, Entity e)
    {
        auto bodyComponent = getManager()->getComponent<Garden::Components::RigidBody>(e);
        auto transformComponent = getManager()->getComponent<Garden::Components::Transform>(e);

        // update
        bodyComponent->acceleration.X = (bodyComponent->force.X + bodyComponent->friction.X) / bodyComponent->mass;
        bodyComponent->acceleration.Y = bodyComponent->gravity + bodyComponent->force.Y / bodyComponent->mass;
        bodyComponent->velocity = bodyComponent->acceleration * deltaTime;
        bodyComponent->position = bodyComponent->velocity * deltaTime;

        // backup old position
        auto lastSafePositionX = transformComponent->Position.X;
        auto lastSafePositionY = transformComponent->Position.Y;

        // --- process X
        transformComponent->Position.X += bodyComponent->position.X;
        // Check and fix if entity is into the world
        if (transformComponent->Position.X < 0)
            transformComponent->Position.X = 0;
        if (transformComponent->Position.X > m_camera->sceneWidth)
            transformComponent->Position.X = m_camera->sceneWidth;
        // todo : hard values
        bodyComponent->collider(transformComponent->Position.X, transformComponent->Position.Y, 58, 64);
        if (m_collisionEngine.get()->worldCollision(bodyComponent->collider()))
        {
            transformComponent->Position.X = lastSafePositionX;
        }

        // --- process Y
        transformComponent->Position.Y += bodyComponent->position.Y;
        // Check and fix if entity is into the world
        if (transformComponent->Position.Y < 0)
            transformComponent->Position.Y = 0;
        // todo : hard value
        if (transformComponent->Position.Y > m_camera->sceneHeight - 128)
            transformComponent->Position.Y = m_camera->sceneHeight - 128;
        // todo : hard values
        bodyComponent->collider(transformComponent->Position.X, transformComponent->Position.Y, 58, 64);
        if (m_collisionEngine.get()->worldCollision(bodyComponent->collider()))
        {
            transformComponent->Position.Y = lastSafePositionY;
        }

        bool drawCollider{true};
        // Debug draw collider
        if (drawCollider)
        {
            auto cameraPosition = m_camera->position;
            SDL_Rect box = {(int)(bodyComponent->collider().x - cameraPosition.X), (int)(bodyComponent->collider().y - cameraPosition.Y), bodyComponent->collider().w, bodyComponent->collider().h};
            SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(m_renderer, &box);
        }
    }
} // namespace Garden::Systems