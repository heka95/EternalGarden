#include "GraphicWindow.hpp"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

GraphicWindow::GraphicWindow() : m_sdlWindowPtr(nullptr),
                                 m_defaultDisplayIndex(0),
                                 m_windowName("Eternal Garden")
{
    m_windowSize.height = 0;
    m_windowSize.width = 0;
}

GraphicWindow::~GraphicWindow()
{
    if (m_sdlWindowPtr != nullptr)
    {
        SDL_DestroyWindow(m_sdlWindowPtr);
    }
    SDL_Quit();
}

Garden::Size GraphicWindow::getWindowSize() const
{
    return m_windowSize;
}

SDL_Window *GraphicWindow::getWindow() const
{
    return m_sdlWindowPtr;
}

Garden::Size GraphicWindow::getDisplaySize() const
{
    return m_displaySize;
}

bool GraphicWindow::createContext(Garden::Configuration &configuration)
{
    m_windowSize.width = configuration.windowSize.width;
    m_windowSize.height = configuration.windowSize.height;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
    {
        std::cout << "Could not initialize SDL IMAGE: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_DisplayMode display;
    SDL_GetCurrentDisplayMode(this->m_defaultDisplayIndex, &display);
    m_displaySize.height = display.h;
    m_displaySize.width = display.w;

    std::cout << "Main screen resolution: " << m_displaySize << std::endl;
    std::cout << "Game window size: " << m_windowSize << std::endl;

    m_sdlWindowPtr = SDL_CreateWindow(m_windowName.c_str(), SDL_WINDOWPOS_CENTERED_DISPLAY(0), SDL_WINDOWPOS_CENTERED_DISPLAY(0),
                                      m_windowSize.width, m_windowSize.height, SDL_WINDOW_SHOWN);
    if (m_sdlWindowPtr == nullptr)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "Window has been created with success" << std::endl;
    return true;
}