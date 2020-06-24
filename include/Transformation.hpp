#pragma once
#include "core/ECSTypes.hpp"
#include "Vector2D.hpp"
#include "BaseComponent.hpp"

namespace Garden::Components
{
    class Transform : public Garden::BaseComponent
    {
    public:
        static const ComponentType type = Garden::Types::TransformationType;
        Transform(Garden::Vector2D position)
        {
            Position = position;
            m_type = type;
        }
        Garden::Vector2D Position;
    };
} // namespace Garden::Components