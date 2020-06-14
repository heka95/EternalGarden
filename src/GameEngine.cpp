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

Player *player = nullptr;

GameEngine::GameEngine() : m_isRunning(false)
{
    m_renderer = nullptr;
}

GraphicWindow GameEngine::getGraphicWindow() const
{
    return m_graphicWindow;
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
    if (m_graphicWindow.createContext(configuration))
    {
        m_renderer = SDL_CreateRenderer(m_graphicWindow.getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    std::string texturePath = configuration.executionPath + "/assets/cat_idle.png";
    std::string textureRunPath = configuration.executionPath + "/assets/cat_run.png";

    // test loading texture
    TextureManager::getInstance().load("player", texturePath);
    TextureManager::getInstance().load("player_run", textureRunPath);
    player = new Player(new Garden::ObjectMetaData("player", Garden::Vector2I{100, 200}, Garden::Size{64, 56}));
}

void GameEngine::doUpdate()
{
    auto deltaTime = Timer::getInstance().getDeltaTime();
    m_world->update();
    player->update(deltaTime);
}

void GameEngine::doDraw()
{
    SDL_SetRenderDrawColor(m_renderer, 0x2B, 0x84, 0xAB, 0xFF);
    SDL_RenderClear(m_renderer);
    m_world->render();

    //TextureManager::getInstance().draw("eagle", Garden::Vector2I{100,100}, Garden::Size{40,41});
    player->draw();

    /*
    for (const auto *layer : m_currentWorld.getLayers())
    {
        for (const auto *entity : layer->getEntities())
        {
            auto components = entity->getComponents();
            std::for_each(components.begin(), components.end(), [](BaseComponent *base) {
                TransformerComponent *component = dynamic_cast<TransformerComponent *>(base);
                if (component)
                {
                    std::cout << "super !" << std::endl;
                }
            });
        }
    }
    //renderer.draw(textures...)
    */
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