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

        float mass = 1.0f;
        float gravity = 9.8f;
        Garden::Vector2D force{0, 0};
        Garden::Vector2D friction{0, 0};
        Garden::Vector2D position{0, 0};
        Garden::Vector2D velocity{0, 0};
        Garden::Vector2D acceleration{0, 0};
        SDL_Rect collider() { return m_colliderBox; }
        void collider(int x, int y, int w, int h)
        {
            m_colliderBox = {
                x - m_colliderBoxBuffer.x,
                y - m_colliderBoxBuffer.y,
                h - m_colliderBoxBuffer.h,
                w - m_colliderBoxBuffer.w};
        }
        void setBuffer(int x, int y, int w, int h) { m_colliderBoxBuffer = {x, y, w, h}; }

    private:
        SDL_Rect m_colliderBox{0, 0, 0, 0};
        SDL_Rect m_colliderBoxBuffer{0, 0, 0, 0};
    };
} // namespace Garden::Components