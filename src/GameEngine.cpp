#include <iostream>
#include <algorithm>
#include "GameEngine.hpp"
#include "Component/TransformerComponent.hpp"
#include <SDL2/SDL_ttf.h>

GameEngine::GameEngine() : m_isRunning(false)
{
}

GraphicWindow GameEngine::getGraphicWindow() const
{
    return m_graphicWindow;
}

Renderer GameEngine::getRenderer() const
{
    return m_renderer;
}

bool GameEngine::isRunning() const
{
    return m_isRunning;
}

std::unique_ptr<GameEngine> GameEngine::m_instance;
GameEngine& GameEngine::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new GameEngine());
    }
    return *m_instance.get();
}

void GameEngine::setWorld(const World &world)
{
    m_currentWorld = world;
}

void GameEngine::configureAndInit(Garden::Configuration &configuration)
{
    if (m_graphicWindow.createContext(configuration) &&
        m_renderer.create(&m_graphicWindow))
    {
        m_isRunning = true;
    }
}

void GameEngine::doUpdate()
{
}

void GameEngine::doDraw()
{
    m_renderer.clear();
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
    m_renderer.flip();
}

void GameEngine::release()
{
}

void GameEngine::doEvents()
{
    while (SDL_PollEvent(&m_event))
    {
        if (m_event.type == SDL_QUIT)
        {
            m_isRunning = false;
        }
    }
}