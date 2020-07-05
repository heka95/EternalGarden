#pragma once

#include <memory>
#include "SDL.h"
#include "components/BaseComponent.hpp"
#include "components/PlayerCommand.hpp"
#include "systems/System.hpp"
#include "components/CameraComponent.hpp"
#include "GraphicWindow.hpp"
#include "systems/TextDefinition.hpp"
#include "Event.hpp"
#include "core/Manager.hpp"

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
        InputSystem(int priority, Manager *manager, Garden::Components::CameraComponent *camera, GraphicWindow *graphicWindow) : System(priority, {Garden::Components::PlayerCommand::type}, manager)
        {
            m_graphicWindow = graphicWindow;
            m_camera = camera;
            m_keyStates = SDL_GetKeyboardState(nullptr);            
        }
        virtual void updateEntity(float deltaTime, Entity e) override;
        virtual void preUpdate(float deltaTime) override;

    private:
        Garden::Components::CameraComponent *m_camera;
        void windowEvents(SDL_Event event);
        void keyUp();
        void keyDown();
        bool getKeyDown(SDL_Scancode key);
        int getAxisKey(Axis axis);
        const Uint8 *m_keyStates;
        GraphicWindow *m_graphicWindow;
        Garden::Systems::TextDefinition m_pauseTextDef;
        std::string m_pauseEventTextKey{"pauseText"};
        bool m_textConfigured{false};
    };
} // namespace Garden::Systems