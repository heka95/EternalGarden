#pragma once

#include <memory>
#include "GraphicWindow.hpp"
#include "core/Manager.hpp"

class GameEngine
{
public:
    virtual ~GameEngine() = default;
    static GameEngine &getInstance();
    void configureAndInit(Garden::Configuration &configuration);
    void stopRunning();
    void release();
    bool isRunning() const;
    GraphicWindow *getGraphicWindow();
    SDL_Renderer *getRenderer();
    void popState();
    void setWindowSize(SDL_Rect windowSize) { m_windowSize = windowSize; }
    SDL_Rect getWindowSize() { return m_windowSize; }
    Garden::Manager* getManager() {return m_manager;}

private:
    GameEngine();
    GameEngine(const GameEngine &object) = delete;
    GameEngine &operator=(const GameEngine &object) = delete;
    static std::unique_ptr<GameEngine> m_instance;
    std::unique_ptr<GraphicWindow> m_graphicWindow;
    SDL_Renderer *m_renderer;
    bool m_isRunning;
    SDL_Rect m_windowSize;
    Garden::Manager* m_manager;
};