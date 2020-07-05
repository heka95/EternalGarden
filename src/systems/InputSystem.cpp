#include "systems/InputSystem.hpp"
#include "components/RigidBody.hpp"
#include "components/SpriteRenderer.hpp"
#include "components/SpriteAnimation.hpp"
#include "GameEngine.hpp"

namespace Garden::Systems
{
    void InputSystem::preUpdate(float deltaTime)
    {
        if(!m_textConfigured)
        {
            m_textConfigured = true;
            Garden::LoadFontEvent fontEvent{};
            fontEvent.id = "pauseFont";
            fontEvent.size = 48;
            fontEvent.sourceFile = "content/assets/font/Retrow Mentho.ttf";
            getManager()->triggerEvent(1, &fontEvent);

            m_pauseTextDef.color = SDL_Color{145, 200, 255};
            m_pauseTextDef.fontId = fontEvent.id;
            m_pauseTextDef.draw = false;
            m_pauseTextDef.message = "PAUSE";
            m_pauseTextDef.positionX = 600;
            m_pauseTextDef.positionY = 350;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            windowEvents(event);
            switch (event.type)
            {
            case SDL_QUIT:
            {
                Garden::ExitEvent event{};
                event.exitAsked = true;
                getManager()->triggerEvent(1, &event);
            }
            break;
            case SDL_KEYDOWN:
            {
                m_keyStates = SDL_GetKeyboardState(nullptr);
                if (getKeyDown(SDL_SCANCODE_P))
                {
                    Garden::PauseEvent event{};
                    event.pause = true;
                    getManager()->triggerEvent(1, &event);
                    m_pauseTextDef.draw = !m_pauseTextDef.draw;
                    Garden::CreateTextEvent textEvent{};
                    textEvent.textId = m_pauseEventTextKey;
                    textEvent.definition = m_pauseTextDef;
                    getManager()->triggerEvent(1, &textEvent);
                }
                if (getKeyDown(SDL_SCANCODE_F1))
                {
                    Garden::DebugToggleEvent event{};
                    getManager()->triggerEvent(1, &event);
                }
                if (getKeyDown(SDL_SCANCODE_ESCAPE))
                {
                    Garden::ExitEvent event{};
                    event.exitAsked = true;
                    getManager()->triggerEvent(1, &event);
                }
            }
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
            Garden::Size size{};
            size.width = event.window.data1;
            size.height = event.window.data2;
            m_graphicWindow->windowSize(size);
            m_camera->viewBox.h = size.height;
            m_camera->viewBox.w = size.width;
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

        auto rigidBody = getManager()->getComponent<Garden::Components::RigidBody>(e);
        auto renderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);
        auto animation = getManager()->getComponent<Garden::Components::SpriteAnimation>(e);
        animation->currentAnimation = Garden::Components::AnimationType::IDLE;
        rigidBody->force = Vector2D::zero();
        rigidBody->isCrouching = false;
        rigidBody->isRunning = false;
        rigidBody->isAttacking = false;

        if (cCommand->isKeyMoveRight)
        {
            rigidBody->force.X = (1 * rigidBody->runSpeed);
            renderer->flip = SDL_RendererFlip::SDL_FLIP_NONE;
            rigidBody->isRunning = true;
        }
        if (cCommand->isKeyMoveLeft)
        {
            rigidBody->force.X = (-1 * rigidBody->runSpeed);
            renderer->flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
            rigidBody->isRunning = true;
        }
        if (cCommand->isKeyCrouching)
        {
            rigidBody->force = Vector2D::zero();
            rigidBody->isCrouching = true;
        }
        if (cCommand->isKeyAttack)
        {
            //rigidBody->force = Vector2D::zero();
            rigidBody->isAttacking = true;
        }
        if (cCommand->isKeyJump && rigidBody->isGrounded)
        {
            rigidBody->force.Y = -rigidBody->jumpForce;
            rigidBody->isJumping = true;
            rigidBody->isGrounded = false;
            Garden::PlaySoundEvent jumpSoundEvent{};
            jumpSoundEvent.id = "jump";
            getManager()->triggerEvent(1, &jumpSoundEvent);
        }
        if (cCommand->isKeyJump && rigidBody->isJumping && rigidBody->jumpRemainingTime > 0)
        {
            rigidBody->jumpRemainingTime -= deltaTime;
            rigidBody->force.Y = -rigidBody->jumpForce;
        }
        else
        {
            rigidBody->isJumping = false;
            rigidBody->jumpRemainingTime = rigidBody->jumpTime;
        }

        rigidBody->isFalling = (rigidBody->velocity.Y > 0 && !rigidBody->isGrounded);

        if (rigidBody->isAttacking && rigidBody->attackRemainingTime == rigidBody->attackTime)
        {
            Garden::PlaySoundEvent attackSoundEvent{};
            attackSoundEvent.id = "attack";
            getManager()->triggerEvent(1, &attackSoundEvent);
        }
        if (rigidBody->isAttacking && rigidBody->attackRemainingTime > 0)
        {
            rigidBody->attackRemainingTime -= deltaTime;
        }
        else
        {
            rigidBody->isAttacking = false;
            rigidBody->attackRemainingTime = rigidBody->attackTime;
        }
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