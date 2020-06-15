#include <iostream>
#include <algorithm>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "GameEngine.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include "Timer.hpp"
#include "MapLoader.hpp"
#include "Camera.hpp"

Player *player = nullptr;

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

World *GameEngine::getWorld()
{
    return m_world;
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
    }

    if (!MapLoader::getInstance().load("level1", "assets/maps/test_map.json"))
    {
        std::cout << "Failed to load map" << std::endl;
    }

    m_world = MapLoader::getInstance().getWorld("level1");

    // test loading texture
    TextureManager::getInstance().load("player", "assets/cat_idle.png");
    TextureManager::getInstance().load("player_run", "assets/cat_run.png");
    TextureManager::getInstance().load("player_jump", "assets/cat_jump.png");

    TextureManager::getInstance().load("background", "assets/bg_forest.png");

    player = new Player(new Garden::ObjectMetaData("player", Garden::Vector2I{10, 500}, Garden::Size{64, 56}));
    Camera::getInstance().setTarget(player->getOrigin());
}

void GameEngine::doUpdate()
{
    auto deltaTime = Timer::getInstance().getDeltaTime();
    player->update(deltaTime);
    m_world->update();
    Camera::getInstance().update(deltaTime);
}

void GameEngine::doDraw()
{
    SDL_SetRenderDrawColor(m_renderer, 0x2B, 0x84, 0xAB, 0xFF);
    SDL_RenderClear(m_renderer);
    TextureManager::getInstance().draw("background", Garden::Vector2I{0, 0}, Garden::Size{1280, 720});
    m_world->render();
    player->draw();
    SDL_RenderPresent(m_renderer);
}

void GameEngine::release()
{
    TextureManager::getInstance().release();
    SDL_DestroyRenderer(m_renderer);
    m_graphicWindow.release();
    IMG_Quit();
    SDL_Quit();
}

void GameEngine::doEvents()
{
    Input::getInstance().listen();
}