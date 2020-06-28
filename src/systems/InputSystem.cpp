#include "systems/InputSystem.hpp"
#include "components/RigidBody.hpp"
#include "components/SpriteRenderer.hpp"
#include "components/SpriteAnimation.hpp"
#include "GameEngine.hpp"

namespace Garden::Systems
{
    void InputSystem::preUpdate(float deltaTime)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            windowEvents(event);
            switch (event.type)
            {
            case SDL_QUIT:
                GameEngine::getInstance().stopRunning();
                break;
            case SDL_KEYDOWN:
                m_keyStates = SDL_GetKeyboardState(nullptr);
                break;
            case SDL_KEYUP:
                m_keyStates = SDL_GetKeyboardState(nullptr);
                break;
            }
        }
    }

    void InputSystem::windowEvents(SDL_Event event)
    {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            auto width = event.window.data1;
            auto height = event.window.data2;
            const SDL_Rect window{0, 0, width, height};
            GameEngine::getInstance().setWindowSize(window);
            //Camera::getInstance().setSceneSize(window.w, window.h);
        }
    }

    void InputSystem::updateEntity(float deltaTime, Entity e)
    {
        auto cCommand = getManager()->getComponent<Garden::Components::PlayerCommand>(e);
        cCommand->reset();

        if (getAxisKey(Axis::HORIZONTAL) == 1)
        {
            cCommand->isKeyMoveRight = true;
        }
        if (getAxisKey(Axis::HORIZONTAL) == -1)
        {
            cCommand->isKeyMoveLeft = true;
        }
        if (getAxisKey(Axis::VERTICAL) == -1)
        {
            cCommand->isKeyCrouching = true;
        }
        if (getKeyDown(SDL_SCANCODE_K))
        {
            cCommand->isKeyAttack = true;
        }
        if (getKeyDown(SDL_SCANCODE_J))
        {
            cCommand->isKeyJump = true;
        }

        //const to change....
        float run_force = 4.0f;
        float jump_force = 10.0f;
        float jump_time = 30.0f;
        float attacke_time = 20.0f;

        auto rigidBody = getManager()->getComponent<Garden::Components::RigidBody>(e);
        auto renderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);
        auto animation = getManager()->getComponent<Garden::Components::SpriteAnimation>(e);
        animation->currentAnimation = Garden::Components::AnimationType::IDLE;
        rigidBody->force = Vector2D::zero();


        if (cCommand->isKeyMoveRight)
        {
            animation->currentAnimation = Garden::Components::AnimationType::RUN;
            rigidBody->force.X = (1 * run_force);
            renderer->flip = SDL_RendererFlip::SDL_FLIP_NONE;
        }
        if (cCommand->isKeyMoveLeft)
        {
            animation->currentAnimation = Garden::Components::AnimationType::RUN;
            rigidBody->force.X = (-1 * run_force);
            renderer->flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
        }
        if (cCommand->isKeyCrouching)
        {
            animation->currentAnimation = Garden::Components::AnimationType::CROUCH;
            rigidBody->force = Vector2D::zero();
        }
        if (cCommand->isKeyAttack)
        {
            animation->currentAnimation = Garden::Components::AnimationType::ATTACK;
            rigidBody->force = Vector2D::zero();
        }
        if(cCommand->isKeyJump)
        {
            animation->currentAnimation = Garden::Components::AnimationType::JUMP;
            rigidBody->force.Y = -jump_force;
        }

        // update texture
        renderer->textureId = animation->animations[animation->currentAnimation].textureId;
    }

    int InputSystem::getAxisKey(Axis axis)
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

    bool InputSystem::getKeyDown(SDL_Scancode key)
    {
        return (m_keyStates[key] == 1);
    }

    void InputSystem::keyUp()
    {
        m_keyStates = SDL_GetKeyboardState(nullptr);
    }

    void InputSystem::keyDown()
    {
        m_keyStates = SDL_GetKeyboardState(nullptr);
    }
} // namespace Garden::Systems