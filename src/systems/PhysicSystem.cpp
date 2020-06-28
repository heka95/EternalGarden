#include "systems/PhysicSystem.hpp"
#include "core/Manager.hpp"
#include "components/Transformation.hpp"
#include "components/SpriteAnimation.hpp"

namespace Garden::Systems
{
    void PhysicSystem::updateEntity(float deltaTime, Entity e)
    {
        auto rigidBody = getManager()->getComponent<Garden::Components::RigidBody>(e);
        auto transform = getManager()->getComponent<Garden::Components::Transform>(e);

        // update
        rigidBody->acceleration.X = (rigidBody->force.X + rigidBody->friction.X) / rigidBody->mass;
        rigidBody->acceleration.Y = rigidBody->gravity + rigidBody->force.Y / rigidBody->mass;
        rigidBody->velocity = rigidBody->acceleration * deltaTime;
        rigidBody->position = rigidBody->velocity * deltaTime;

        // backup old position
        auto lastSafePositionX = transform->Position.X;
        auto lastSafePositionY = transform->Position.Y;

        // --- process X
        transform->Position.X += rigidBody->position.X;
        // Check and fix if entity is into the world
        if (transform->Position.X < 0)
            transform->Position.X = 0;
        if (transform->Position.X > m_camera->sceneWidth)
            transform->Position.X = m_camera->sceneWidth;
        // todo : hard values
        rigidBody->collider(transform->Position.X, transform->Position.Y, 58, 64);
        if (m_collisionEngine.get()->worldCollision(rigidBody->collider()))
        {
            transform->Position.X = lastSafePositionX;
        }

        // --- process Y
        transform->Position.Y += rigidBody->position.Y;
        // Check and fix if entity is into the world
        if (transform->Position.Y < 0)
            transform->Position.Y = 0;
        // todo : hard value
        if (transform->Position.Y > m_camera->sceneHeight - 128)
            transform->Position.Y = m_camera->sceneHeight - 128;
        // todo : hard values
        rigidBody->collider(transform->Position.X, transform->Position.Y, 58, 64);
        if (m_collisionEngine.get()->worldCollision(rigidBody->collider()))
        {
            transform->Position.Y = lastSafePositionY;
            rigidBody->isGrounded = true;
        }
        else
        {
            rigidBody->isGrounded = false;
        }

        // todo
        //m_origin->X = m_transform->X + m_size.width / 2;
        //m_origin->Y = m_transform->Y + m_size.height / 2;

        // maybe better...
        auto animation = getManager()->getComponent<Garden::Components::SpriteAnimation>(e);
        if (rigidBody->isRunning) 
        {
            animation->currentAnimation = Garden::Components::AnimationType::RUN;
        }
        if (rigidBody->isCrouching) animation->currentAnimation = Garden::Components::AnimationType::CROUCH;
        if (rigidBody->isJumping) animation->currentAnimation = Garden::Components::AnimationType::JUMP;
        if (rigidBody->isFalling) animation->currentAnimation = Garden::Components::AnimationType::FALL;
        if (rigidBody->isAttacking) animation->currentAnimation = Garden::Components::AnimationType::ATTACK;

        bool drawCollider{true};
        // Debug draw collider
        if (drawCollider)
        {
            auto cameraPosition = m_camera->position;
            SDL_Rect box = {(int)(rigidBody->collider().x - cameraPosition.X), (int)(rigidBody->collider().y - cameraPosition.Y), rigidBody->collider().w, rigidBody->collider().h};
            SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(m_renderer, &box);
        }
    }
} // namespace Garden::Systems