#pragma once
#include "../core/Core.hpp"

namespace Garden::Components
{
    class Transform : public Garden::Component
    {
    public:
        static const ComponentType type = 1;
        Transform(Garden::Vector2D position) : m_position(position)
        { }
        Garden::Vector2D getPosition() const { return m_position; }
        void setPosition(Garden::Vector2D &position) { m_position = position; }

    private:
        Garden::Vector2D m_position;
    };
} // namespace Garden::Components