#if !defined(__RENDERER__)
#define __RENDERER__

#include "GraphicWindow.hpp"

class Renderer
{
    public:
        Renderer();
        ~Renderer();
        bool create(GraphicWindow *graphicWindow);
        void draw(SDL_Texture *texture);
        void clear();
        void flip();

    private:
        GraphicWindow *graphicWindow = NULL;
        SDL_Renderer *sdlRenderer = NULL;
};

#endif