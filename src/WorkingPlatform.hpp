#if !defined(__WORKINGPLATFORM__)
#define __WORKINGPLATFORM__

#include "Types/GameTypes.hpp"
#include "GraphicWindow.hpp"
#include "Renderer.hpp"
#include "World.hpp"

class WorkingPlatform
{
    public:
        WorkingPlatform();
        void load(Garden::Configuration &configuration);
        void run();

        GraphicWindow getGraphicWindow() const;
        Renderer getRenderer() const;
        void setWorld(const World &world);

    private:
        GraphicWindow m_graphicWindow;
        Renderer m_renderer;
        bool m_isRunning;
        SDL_Event m_event;
        World m_currentWorld;
        void processEvents();
};

#endif