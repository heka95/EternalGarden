#include <iostream>
#include <algorithm>
#include "WorkingPlatform.hpp"
#include "Component/TransformerComponent.hpp"
#include <SDL2/SDL_ttf.h>


WorkingPlatform::WorkingPlatform() : m_isRunning(false)
{
}

GraphicWindow WorkingPlatform::getGraphicWindow() const
{
    return m_graphicWindow;
}

Renderer WorkingPlatform::getRenderer() const
{
    return m_renderer;
}

void WorkingPlatform::setWorld(const World &world)
{
    m_currentWorld = world;
}

void WorkingPlatform::load(Garden::Configuration &configuration)
{
    m_graphicWindow.createContext(configuration);
    m_renderer.create(&m_graphicWindow);
}

void WorkingPlatform::run()
{
    m_isRunning = true;

    while (m_isRunning)
    {
        processEvents();
    }
}

void WorkingPlatform::processEvents()
{
    while (SDL_PollEvent(&m_event))
    {
        if (m_event.type == SDL_QUIT)
        {
            m_isRunning = false;
        }
        m_renderer.clear();
        for (const auto *layer : m_currentWorld.getLayers())
        {
            for (const auto *entity : layer->getEntities())
            {
                auto components = entity->getComponents();
                std::for_each(components.begin(), components.end(), [] (BaseComponent* base) 
                {
                    TransformerComponent* component = dynamic_cast<TransformerComponent*>(base);
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
}