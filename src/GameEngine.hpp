#pragma once

#include <memory>

#include "Types/GameTypes.hpp"
#include "GraphicWindow.hpp"
#include "World.hpp"

class GameEngine
{
public:
    virtual ~GameEngine() = default;
    static GameEngine& getInstance();
    void configureAndInit(Garden::Configuration &configuration);
    void doEvents();
    void doUpdate();
    void doDraw();
    void stopRunning();
    void release();
    bool isRunning() const;
    GraphicWindow getGraphicWindow() const;
    SDL_Renderer* getRenderer();
    void setWorld(const World &world);

private:
    GameEngine();
    GameEngine(const GameEngine& object) = delete;
    GameEngine& operator=(const GameEngine& object) = delete;
    static std::unique_ptr<GameEngine> m_instance;
    GraphicWindow m_graphicWindow;
    SDL_Renderer* m_renderer;
    bool m_isRunning;
    SDL_Event m_event;
    World m_currentWorld;
};