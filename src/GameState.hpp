#pragma once

#include <SDL2/SDL.h>

class GameState
{
public:
    virtual bool initialize() = 0;
    virtual bool release() = 0;
    virtual void doUpdate() = 0;
    virtual void doDraw() = 0;

protected:
    SDL_Renderer *m_renderContext;
};