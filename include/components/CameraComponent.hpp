#pragma once

#include "BaseComponent.hpp"
#include "Vector2D.hpp"
#include "SDL.h"

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

        Entity target{0};
        Garden::Vector2D position{0, 0};
        SDL_Rect viewBox{0, 0, 0, 0};
        int sceneWidth{0};
        int sceneHeight{0};
    };
} // namespace Garden::Components