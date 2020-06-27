#pragma once

#include <memory>
#include "SDL.h"
#include "components/BaseComponent.hpp"
#include "components/PlayerCommand.hpp"
#include "systems/System.hpp"

namespace Garden::Systems
{
    enum Axis
    {
        HORIZONTAL,
        VERTICAL
    };

#define BACKWARD = -1;
#define FORWARD = 1;

    class InputSystem : public Garden::System
    {
    public:
        InputSystem(int priority, Manager *manager) : System(priority, {Garden::Components::PlayerCommand::type}, manager)
        {
            m_keyStates = SDL_GetKeyboardState(nullptr);
        }
        virtual void updateEntity(float deltaTime, Entity e) override;
        virtual void preUpdate(float deltaTime) override;

    private:
        void windowEvents(SDL_Event event);
        void keyUp();
        void keyDown();
        bool getKeyDown(SDL_Scancode key);
        int getAxisKey(Axis axis);
        const Uint8 *m_keyStates;
    };
} // namespace Garden::Systems