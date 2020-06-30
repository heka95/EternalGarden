#pragma once

#include <string>
#include <memory>
#include "SDL.h"
#include "Size.hpp"
#include "Configuration.hpp"

class GraphicWindow
{
    public:
        GraphicWindow();
        ~GraphicWindow();
        bool createContext(Garden::Configuration &configuration);
        void release();
        
        Garden::Size getWindowSize() const;
        Garden::Size getDisplaySize() const;
        SDL_Window* getWindow() const;

    private:
        Garden::Size m_windowSize;
        Garden::Size m_displaySize;
        SDL_Window *m_sdlWindowPtr;
        const int m_defaultDisplayIndex;
};