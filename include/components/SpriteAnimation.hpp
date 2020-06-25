#pragma once
#include "BaseComponent.hpp"

namespace Garden::Components
{
    class SpriteAnimation : public Garden::BaseComponent
    {
    public:
        static const ComponentType type = Garden::Types::SpriteAnimationType;
        SpriteAnimation()
        {
            m_type = type;
        }

        int width{0};
        int height{0};
        int rowCount{0};
        int frameCount{0};
        int speed{0};
        bool loop{false};
    };
} // namespace Garden::Components