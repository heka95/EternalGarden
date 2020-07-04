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
        SDL_Rect collider() { return m_colliderBox; }
        void collider(int x, int y, int w, int h)
        {
            m_colliderBox = {
                x + m_colliderBoxBuffer.x,
                y + m_colliderBoxBuffer.y,
                m_colliderBoxBuffer.w,
                m_colliderBoxBuffer.h};
        }
        void setBuffer(int x, int y, int w, int h) { m_colliderBoxBuffer = {x, y, w, h}; }
        SDL_Rect buffer() const { return m_colliderBoxBuffer; }

    private:
        SDL_Rect m_colliderBox{0, 0, 0, 0};
        SDL_Rect m_colliderBoxBuffer{0, 0, 0, 0};
    };
} // namespace Garden::Components