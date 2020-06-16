#include "Input.hpp"
#include "GameEngine.hpp"

Input::Input()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

std::unique_ptr<Input> Input::m_instance;
Input &Input::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new Input());
    }
    return *m_instance.get();
}

void Input::listen()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            GameEngine::getInstance().stopRunning();
            break;
        case SDL_KEYDOWN:
            keyDown();
            break;
        case SDL_KEYUP:
            keyUp();
            break;
        }
    }
}

int Input::getAxisKey(Axis axis)
{
    switch (axis)
    {
    case HORIZONTAL:
        if (getKeyDown(SDL_SCANCODE_D) || getKeyDown(SDL_SCANCODE_RIGHT))
            return 1;
        if (getKeyDown(SDL_SCANCODE_A) || getKeyDown(SDL_SCANCODE_LEFT))
            return -1;
        break;

    case VERTICAL:
        if (getKeyDown(SDL_SCANCODE_W) || getKeyDown(SDL_SCANCODE_UP))
            return 1;
        if (getKeyDown(SDL_SCANCODE_S) || getKeyDown(SDL_SCANCODE_DOWN))
            return -1;
        break;

    default:
        return 0;
    }
    return 0;
}

bool Input::getKeyDown(SDL_Scancode key)
{
    return (m_keyStates[key] == 1);
}

void Input::keyUp()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}