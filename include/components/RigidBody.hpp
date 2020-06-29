#pragma once

#include "SDL.h"
#include "BaseComponent.hpp"
#include "Vector2D.hpp"

namespace Garden::Components
{
    class RigidBody : public Garden::BaseComponent
    {
    public:
        static const ComponentType type = Garden::Types::RigidBodyType;
        RigidBody()
        {
            m_type = type;
        }

        float mass{0};
        float gravity{0};
        float runSpeed{0};
        float jumpForce{0};
        float jumpTime{0};
        float attackTime{0};

        float jumpRemainingTime{0};
        float attackRemainingTime{0};
        bool isGrounded{false};
        bool isFalling{false};
        bool isAttacking{false};
        bool isRunning{false};
        bool isCrouching{false};
        bool isJumping{false};

        Garden::Vector2D force{0, 0};
        Garden::Vector2D friction{0, 0};
        Garden::Vector2D position{0, 0};
        Garden::Vector2D velocity{0, 0};
        Garden::Vector2D acceleration{0, 0};
        SDL_FRect collider() { return m_colliderBox; }
        void collider(float x, float y, float w, float h)
        {
            m_colliderBox = {
                x + m_colliderBoxBuffer.x,
                y - m_colliderBoxBuffer.y,
                m_colliderBoxBuffer.h,
                m_colliderBoxBuffer.w};
        }
        void setBuffer(float x, float y, float w, float h) { m_colliderBoxBuffer = {x, y, w, h}; }

    private:
        SDL_FRect m_colliderBox{0, 0, 0, 0};
        SDL_FRect m_colliderBoxBuffer{0, 0, 0, 0};
    };
} // namespace Garden::Components