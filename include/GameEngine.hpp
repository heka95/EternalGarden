#pragma once

#include <memory>
#include "GraphicWindow.hpp"
#include "core/Manager.hpp"

class GameEngine
{
public:
    GameEngine();
    GameEngine(const GameEngine &object) = delete;
    GameEngine &operator=(const GameEngine &object) = delete;
    virtual ~GameEngine() = default;
    void configureAndInit(Garden::Configuration &configuration);
    void stopRunning();
    void release();
    bool isRunning() const;
    GraphicWindow *getGraphicWindow();
    SDL_Renderer *getRenderer();
    void popState();
    void setWindowSize(SDL_Rect windowSize) { m_windowSize = windowSize; }
    SDL_Rect getWindowSize() { return m_windowSize; }
    Garden::Manager *getManager() { return m_manager; }
    Garden::EventStatus onExitGame(Garden::Entity source, Garden::EventType type, Garden::Event *event);
    Garden::EventStatus onPause(Garden::Entity source, Garden::EventType type, Garden::Event *event);

private:
    std::unique_ptr<GraphicWindow> m_graphicWindow;
    SDL_Renderer *m_renderer;
    bool m_isRunning;
    SDL_Rect m_windowSize;
    Garden::Manager *m_manager;
};