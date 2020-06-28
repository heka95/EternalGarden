#pragma once
#include <iostream>
#include "SDL.h"
#include "BaseComponent.hpp"
#include "Vector2D.hpp"

namespace Garden::Components
{
    class SpriteRenderer : public Garden::BaseComponent
    {
    public:
        static const ComponentType type = Garden::Types::SpriteRendererType;
        SpriteRenderer()
        {
            // todo
            //m_origin.X = width / 2;
            //m_origin.Y = height / 2;
            m_type = type;
        }

        int width{0};
        int height{0};
        int drawWidth{0};
        int drawHeight{0};
        Garden::Vector2D drawOffset{0, 0};
        double rotation{0};
        Garden::Vector2D scale{0, 0};
        Garden::Vector2D origin{0, 0};
        std::string textureId{""};
        SDL_RendererFlip flip{SDL_FLIP_NONE};
    };
} // namespace Garden::Components