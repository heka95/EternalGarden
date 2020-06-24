#pragma once

#include <memory>
#include "SDL.h"

enum Axis 
{
    HORIZONTAL,
    VERTICAL
};

#define BACKWARD = -1;
#define FORWARD = 1;

class Input
{
    public:
    virtual ~Input() = default;
    static Input &getInstance();
    void listen();
    bool getKeyDown(SDL_Scancode key);
    int getAxisKey(Axis axis);

    private:
    Input();
    Input(const Input &object) = delete;
    Input &operator=(const Input &object) = delete;
    static std::unique_ptr<Input> m_instance;
    void keyUp();
    void keyDown();
    void windowEvents(SDL_Event event);
    const Uint8* m_keyStates;
};