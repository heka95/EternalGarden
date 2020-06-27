#include <iostream>
#include <algorithm>
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "GameEngine.hpp"
#include "OldTextureManager.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "managers/GameManager.hpp"

GameEngine::GameEngine() : m_isRunning(false)
{
    m_renderer = nullptr;
    m_graphicWindow.reset(new GraphicWindow());
}

GraphicWindow *GameEngine::getGraphicWindow()
{
    return m_graphicWindow.get();
}

SDL_Renderer *GameEngine::getRenderer()
{
    return m_renderer;
}

bool GameEngine::isRunning() const
{
    return m_isRunning;
}

void GameEngine::stopRunning()
{
    m_isRunning = false;
    std::cout << "Engine stop asked !" << std::endl;
}

std::unique_ptr<GameEngine> GameEngine::m_instance;
GameEngine &GameEngine::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new GameEngine());
    }
    return *m_instance.get();
}

void GameEngine::configureAndInit(Garden::Configuration &configuration)
{
    if (m_graphicWindow->createContext(configuration))
    {
        m_renderer = SDL_CreateRenderer(m_graphicWindow->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_renderer != nullptr)
        {
            m_isRunning = true;
        }
        SDL_RenderSetLogicalSize(m_renderer, 800, 600);
    }
    /*
    auto game = new Game();
    if (game->initialize())
    {
        m_states.push_back(game);
    }
*/
    // Create ECS
    m_manager = new Garden::Managers::GameManager(m_renderer);
    m_manager->initSystems();
}

void GameEngine::doUpdate()
{
    m_states.back()->doUpdate();
}

void GameEngine::popState()
{
}

void GameEngine::pushState(GameState *current)
{
}

void GameEngine::changeState(GameState *target)
{
}

void GameEngine::doDraw()
{
    m_states.back()->doDraw();
}

void GameEngine::release()
{
    m_states.back()->release();
    //TextureManager::getInstance().release();
    SDL_DestroyRenderer(m_renderer);
    m_graphicWindow.release();
    IMG_Quit();
    SDL_Quit();
}

void GameEngine::doEvents()
{
    Input::getInstance().listen();
}