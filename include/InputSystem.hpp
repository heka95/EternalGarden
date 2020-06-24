#pragma once

#include <memory>
#include "SDL.h"
#include "Core.hpp"
#include "Components.hpp"
#include "core/ECSTypes.hpp"
#include "PlayerCommand.hpp"

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
        InputSystem(Manager *manager) : System(1, {Garden::Components::PlayerCommand::type}, manager)
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