#include "systems/PhysicSystem.hpp"
#include "core/Manager.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include "components/Transformation.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/SpriteRenderer.hpp"

namespace Garden::Systems
{
    void PhysicSystem::postUpdate(float delta)
    {
        for (auto e : getEntities())
        {
            auto transform = getManager()->getComponent<Garden::Components::Transform>(e);
            auto rigidBody = getManager()->getComponent<Garden::Components::RigidBody>(e);
            auto renderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

            // Draw Collider
            SDL_Rect box = {(rigidBody->collider().x - m_camera->viewBox.x), (rigidBody->collider().y - m_camera->viewBox.y), rigidBody->collider().w, rigidBody->collider().h};
            SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(m_renderer, &box);

            // Draw Sprite
            box = {((int)transform->Position.X - m_camera->viewBox.x), ((int)transform->Position.Y - m_camera->viewBox.y), renderer->drawWidth, renderer->drawHeight};
            SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
            SDL_RenderDrawRect(m_renderer, &box);

            // Draw Central Line
            int x1 = rigidBody->collider().x + (rigidBody->collider().w * 0.5) - m_camera->viewBox.x;
            int y1 = rigidBody->collider().y - m_camera->viewBox.y;
            int x2 = rigidBody->collider().x + (rigidBody->collider().w * 0.5) - m_camera->viewBox.x;
            int y2 = rigidBody->collider().y + rigidBody->collider().h - m_camera->viewBox.y;
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
            SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
        }
    }

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
        positionYSimulation += rigidBody->position.Y;
        positionYSimulation = std::max(positionYSimulation, 0.0f);
        positionYSimulation = std::min(positionYSimulation, (m_camera->sceneHeight - renderer->drawHeight + 0.0f));
        positionYSimulation = positionYSimulation;

        rigidBody->collider(positionXSimulation, positionYSimulation, renderer->drawWidth, renderer->drawHeight);

        auto collisionResult = m_collisionEngine.get()->worldCollision(rigidBody->collider());

        if (!collisionResult.centerCollision())
        {
            transform->Position.X = positionXSimulation;
        }

        // --- process Y
        if (collisionResult.bottomCollision())
        {
            if (rigidBody->isGrounded == false)
            {
                Garden::PlaySoundEvent jumpSoundEvent{};
                jumpSoundEvent.id = "grounded";
                getManager()->triggerEvent(1, &jumpSoundEvent);

                rigidBody->collider(transform->Position.X, transform->Position.Y, renderer->drawWidth, renderer->drawHeight);
                rigidBody->isGrounded = true;
            }
        }
        if (collisionResult.topCollision())
        {
            rigidBody->jumpRemainingTime = 0;
            rigidBody->force.Y = 0;
        }
        if (!collisionResult.topCollision() && !collisionResult.bottomCollision())
        {
            transform->Position.Y = positionYSimulation;
            rigidBody->isGrounded = false;
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