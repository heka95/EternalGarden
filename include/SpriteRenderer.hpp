#pragma once
#include <iostream>
#include "SDL.h"
#include "Component.hpp"
#include "Vector2D.hpp"

namespace Garden::Components
{
    class SpriteRenderer : public Garden::Component
    {
    public:
        static const ComponentType type = Garden::Types::SpriteRendererType;
        SpriteRenderer(int width, int height, Garden::Vector2D scale, std::string textureId, SDL_RendererFlip flip)
            : m_width(width), m_height(height), m_scale(scale), m_textureId(textureId), m_flip(flip)
        {
            m_origin.X = width / 2;
            m_origin.Y = height / 2;
            m_drawHeight = height;
            m_drawWidth = width;
            m_drawOffset.X = 0;
            m_drawOffset.Y = 0;
            m_type = type;
        }

        int getTextureWidth() const { return m_width; }
        int getTextureHeight() const { return m_height; }
        int getDrawWidth() const { return m_drawWidth; }
        int getDrawHeight() const { return m_drawHeight; }
        void setDrawWidth(int width) { m_drawWidth = width; }
        void setDrawHeight(int height) { m_drawHeight = height; }
        void setDrawOffset(Garden::Vector2D drawOffset)
        {
            //std::cout << "OFFSET DRAW: " << drawOffset << std::endl;
            m_drawOffset = drawOffset;
        }
        double getRotation() const { return m_rotation; }
        SDL_RendererFlip getFlip() const { return m_flip; }
        std::string getTextureId() const { return m_textureId; }
        Garden::Vector2D getOrigin() const { return m_origin; }
        Garden::Vector2D getScale() const { return m_scale; }
        Garden::Vector2D getDrawOffset() const { return m_drawOffset; }
        void setScale(Garden::Vector2D &scale) { m_scale = scale; }

    private:
        int m_width, m_height;
        int m_drawWidth, m_drawHeight;
        Garden::Vector2D m_drawOffset;
        double m_rotation;
        Garden::Vector2D m_scale;
        Garden::Vector2D m_origin;
        std::string m_textureId;
        SDL_RendererFlip m_flip;
    };
} // namespace Garden::Components