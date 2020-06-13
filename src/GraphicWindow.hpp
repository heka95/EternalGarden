#if !defined(__GRAPHICWINDOW__)
#define __GRAPHICWINDOW__

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "Types/GameTypes.hpp"

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
        std::string m_windowName;
        void configureOpenGL();
};

#endif