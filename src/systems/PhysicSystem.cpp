#include "systems/PhysicSystem.hpp"
#include "core/Manager.hpp"
#include "components/Transformation.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/SpriteRenderer.hpp"
#include <algorithm>
#include <iostream>

namespace Garden::Systems
{
    void PhysicSystem::updateEntity(float deltaTime, Entity e)
    {
        auto rigidBody = getManager()->getComponent<Garden::Components::RigidBody>(e);
        auto transform = getManager()->getComponent<Garden::Components::Transform>(e);
        auto renderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

        // update Collider
        rigidBody->collider(transform->Position.X, transform->Position.Y, renderer->drawWidth, renderer->drawHeight);

        rigidBody->acceleration.X = (rigidBody->force.X + rigidBody->friction.X) / rigidBody->mass;
        rigidBody->acceleration.Y = rigidBody->gravity + rigidBody->force.Y / rigidBody->mass;
        rigidBody->velocity = rigidBody->acceleration * deltaTime;
        rigidBody->position = rigidBody->velocity * deltaTime;

        // backup old position
        auto positionXSimulation = transform->Position.X;
        auto positionYSimulation = transform->Position.Y;

        // --- process X
        positionXSimulation += rigidBody->position.X;
        positionXSimulation = std::max(positionXSimulation, 0.0f);
        positionXSimulation = std::min(positionXSimulation, (m_camera->sceneWidth - renderer->drawWidth + 0.0f));

        rigidBody->collider(positionXSimulation, transform->Position.Y, renderer->drawWidth, renderer->drawHeight);

        if (!m_collisionEngine.get()->worldCollision(rigidBody->collider()))
        {
            transform->Position.X = positionXSimulation;
        }

        // --- process Y
        positionYSimulation += rigidBody->position.Y;
        positionYSimulation = std::max(positionYSimulation, 0.0f);
        positionYSimulation = std::min(positionYSimulation, (m_camera->sceneHeight - renderer->drawHeight + 0.0f));

        rigidBody->collider(transform->Position.X, positionYSimulation, renderer->drawWidth, renderer->drawHeight);
        if (!m_collisionEngine.get()->worldCollision(rigidBody->collider()))
        {
            transform->Position.Y = positionYSimulation;
            rigidBody->isGrounded = false;
        }
        else
        {
            auto bufferY = rigidBody->buffer().y;
            rigidBody->collider(transform->Position.X, transform->Position.Y, renderer->drawWidth, renderer->drawHeight);
            rigidBody->isGrounded = true;
        }

        // maybe better...
        auto animation = getManager()->getComponent<Garden::Components::SpriteAnimation>(e);
        if (rigidBody->isRunning)
        {
            animation->currentAnimation = Garden::Components::AnimationType::RUN;
        }
        if (rigidBody->isCrouching)
            animation->currentAnimation = Garden::Components::AnimationType::CROUCH;
        if (rigidBody->isJumping)
            animation->currentAnimation = Garden::Components::AnimationType::JUMP;
        if (rigidBody->isFalling)
            animation->currentAnimation = Garden::Components::AnimationType::FALL;
        if (rigidBody->isAttacking)
            animation->currentAnimation = Garden::Components::AnimationType::ATTACK;
    }
} // namespace Garden::Systems