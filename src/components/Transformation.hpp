#pragma once
#include "ComponentTypes.hpp"
#include "../core/Core.hpp"

namespace Garden::Components
{
    class Transform : public Garden::Component
    {
    public:
        static const ComponentType type = Types::TransformationType;
        Transform(Garden::Vector2D position)
        {
            Position = position;
            m_type = type;
        }
        Garden::Vector2D Position;
    };
} // namespace Garden::Components