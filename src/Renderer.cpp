#include "Renderer.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    if (sdlRenderer != NULL)
    {
        SDL_DestroyRenderer(sdlRenderer);
    }
}

bool Renderer::create(GraphicWindow *graphicWindow)
{
    this->graphicWindow = graphicWindow;
    sdlRenderer = SDL_CreateRenderer(graphicWindow->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return (sdlRenderer != nullptr);
}

void Renderer::draw(SDL_Texture *texture)
{
    SDL_RenderCopy(sdlRenderer, texture, NULL, NULL);
}

void Renderer::clear()
{
    SDL_SetRenderDrawColor(sdlRenderer, 0x2B, 0x84, 0xAB, 0xFF);
    SDL_RenderClear(sdlRenderer);
}

void Renderer::flip()
{
    SDL_RenderPresent(sdlRenderer);
}