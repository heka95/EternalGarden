#pragma once
#include <map>
#include "BaseComponent.hpp"

namespace Garden::Components
{
    class AnimationElement
    {
    public:
        std::string name{""};
        std::string source{""};
        std::string textureId{""};
        int width{0};
        int height{0};
        int rowCount{0};
        int frameCount{0};
        int speed{0};
        bool loop{false};
    };

    class SpriteAnimation : public Garden::BaseComponent
    {
    public:
        static const ComponentType type = Garden::Types::SpriteAnimationType;
        SpriteAnimation()
        {
            m_type = type;
        }
        std::string currentAnimation{""};
        std::map<std::string, AnimationElement> animations;
    };
} // namespace Garden::Components