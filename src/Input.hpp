#pragma once

#include <memory>
#include <SDL2/SDL.h>

class Input
{
    public:
    virtual ~Input() = default;
    static Input &getInstance();
    void listen();
    bool getKeyDown(SDL_Scancode key);

    private:
    Input();
    Input(const Input &object) = delete;
    Input &operator=(const Input &object) = delete;
    static std::unique_ptr<Input> m_instance;
    void keyUp();
    void keyDown();
    const Uint8* m_keyStates;
};