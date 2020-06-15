#pragma once

#include <SDL2/SDL.h>

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

private:
    SDL_Rect m_box;
    SDL_Rect m_buffer;
};