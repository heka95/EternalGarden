#include "Menu.hpp"
#include <iostream>
#include "GameEngine.hpp"

bool Menu::initialize()
{
    m_renderContext = GameEngine::getInstance().getRenderer();
    std::cout << "Menu loaded" << std::endl;
    return true;
}

void Menu::doDraw()
{
    SDL_SetRenderDrawColor(m_renderContext, 16, 45, 70, 255);
    SDL_RenderClear(m_renderContext);
    SDL_RenderPresent(m_renderContext);
}

void Menu::doUpdate()
{
}

bool Menu::release()
{
    std::cout << "Menu Release" << std::endl;
    return true;
}

void Menu::startGame() 
{
    std::cout << "Go to Start game" << std::endl;
}

void Menu::Settings() 
{
    std::cout << "Go to settings" << std::endl;
}

void Menu::Editor() 
{
    std::cout << "Go to editor" << std::endl;
}

void Menu::Quit() 
{
    std::cout << "Go to quit" << std::endl;
}