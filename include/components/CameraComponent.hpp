#pragma once

#include "BaseComponent.hpp"
#include "Vector2D.hpp"

namespace Garden::Components
{
    class CameraComponent : public Garden::BaseComponent
    {
    public:
        static const ComponentType type = Garden::Types::CameraComponentType;
        CameraComponent()
        {
            m_type = type;
        }

        Garden::Vector2D *target = nullptr;
        Garden::Vector2D position{0, 0};
    };
} // namespace Garden::Components