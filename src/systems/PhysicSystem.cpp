#include "systems/PhysicSystem.hpp"
#include "core/Manager.hpp"
#include "components/Transformation.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/SpriteRenderer.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>

namespace Garden::Systems
{
    void PhysicSystem::updateEntity(float deltaTime, Entity e)
    {
        if (!getManager()->isActive)
        {
            return;
        }

        auto rigidBody = getManager()->getComponent<Garden::Components::RigidBody>(e);
        auto transform = getManager()->getComponent<Garden::Components::Transform>(e);
        auto renderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

        // update Collider
        rigidBody->collider(transform->Position.X, transform->Position.Y, renderer->drawWidth, renderer->drawHeight);

        rigidBody->acceleration.X = (rigidBody->force.X + rigidBody->friction.X) / rigidBody->mass;
        rigidBody->velocity.X = rigidBody->acceleration.X;
        rigidBody->position.X = rigidBody->velocity.X * deltaTime;

        if (rigidBody->force.Y == 0)
        {
            rigidBody->force.Y = rigidBody->jumpForce;
        }

        rigidBody->acceleration.Y += rigidBody->gravity + (rigidBody->force.Y / rigidBody->mass);
        rigidBody->acceleration.Y = std::min(rigidBody->force.Y / rigidBody->mass * 10, rigidBody->acceleration.Y);
        rigidBody->velocity.Y = rigidBody->acceleration.Y;
        rigidBody->position.Y = rigidBody->velocity.Y * deltaTime;

        // backup old position
        auto positionXSimulation = transform->Position.X;
        auto positionYSimulation = transform->Position.Y;

        // --- process X
        positionXSimulation += rigidBody->position.X;
        positionXSimulation = std::max(positionXSimulation, 0.0f);
        positionXSimulation = std::min(positionXSimulation, (m_camera->sceneWidth - renderer->drawWidth + 0.0f));
        positionXSimulation = positionXSimulation;

        rigidBody->collider(positionXSimulation, transform->Position.Y, renderer->drawWidth, renderer->drawHeight);

        if (!m_collisionEngine.get()->worldCollision(rigidBody->collider()))
        {
            transform->Position.X = positionXSimulation;
        }

        // --- process Y
        positionYSimulation += rigidBody->position.Y;
        positionYSimulation = std::max(positionYSimulation, 0.0f);
        positionYSimulation = std::min(positionYSimulation, (m_camera->sceneHeight - renderer->drawHeight + 0.0f));
        positionYSimulation = positionYSimulation;

        rigidBody->collider(transform->Position.X, positionYSimulation, renderer->drawWidth, renderer->drawHeight);
        if (!m_collisionEngine.get()->worldCollision(rigidBody->collider()))
        {
            transform->Position.Y = positionYSimulation;
            rigidBody->isGrounded = false;
        }
        else
        {
            if (rigidBody->isGrounded == false)
            {
                Garden::PlaySoundEvent jumpSoundEvent{};
                jumpSoundEvent.id = "grounded";
                getManager()->triggerEvent(1, &jumpSoundEvent);

                auto bufferY = rigidBody->buffer().y;
                rigidBody->collider(transform->Position.X, transform->Position.Y, renderer->drawWidth, renderer->drawHeight);
                rigidBody->isGrounded = true;
            }

            //rigidBody->acceleration.Y = 1.0f;
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

        // set player position
        if (e == m_camera->target)
        {
            Garden::CreateTextEvent textEvent{};
            textEvent.textId = "playerPosition";
            textEvent.definition.color = SDL_Color{0, 0, 0};
            textEvent.definition.fontId = "debugText";
            std::stringstream buffer;
            buffer << transform->Position;
            textEvent.definition.message = buffer.str();
            textEvent.definition.positionX = 0;
            textEvent.definition.positionY = 0;
            textEvent.definition.draw = m_world->debug;
            getManager()->triggerEvent(1, &textEvent);
        }
    }
} // namespace Garden::Systems