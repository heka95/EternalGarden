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
        Transform()
        {
            Position = Garden::Vector2D{0,0};
            m_type = type;
        }
        Garden::Vector2D Position;
    };
} // namespace Garden::Components