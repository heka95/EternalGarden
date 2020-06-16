#pragma once

#include <SDL2/SDL.h>
#include "GameEngine.hpp"
#include "Camera.hpp"
#include "CollisionHandler.hpp"

class Collider
{
public:
    inline SDL_Rect get() { return m_box; }
    inline void set(int x, int y, int w, int h)
    {
        m_box = {
            x - m_buffer.x,
            y - m_buffer.y,
            h - m_buffer.h,
            w - m_buffer.w};
    }
    inline void SetBuffer(int x, int y, int w, int h) { m_buffer = {x, y, w, h}; }
    bool collideWithWorld()
    {
        return CollisionHandler::getInstance().worldCollision(m_box);
    }

    void draw()
    {
        auto cameraPosition = Camera::getInstance().getPosition();
        SDL_Rect box = {(int)(m_box.x - cameraPosition.X), (int)(m_box.y - cameraPosition.Y), m_box.w, m_box.h};
        SDL_SetRenderDrawColor(GameEngine::getInstance().getRenderer(), 255, 0, 0, 255);
        SDL_RenderDrawRect(GameEngine::getInstance().getRenderer(), &box);
    }

private:
    SDL_Rect m_box;
    SDL_Rect m_buffer;
};