#pragma once
#include <map>
#include "SDL.h"
#include "Component.hpp"

namespace Garden::Components
{
    class PlayerCommand : public Garden::Component
    {
    public:
        static const ComponentType type = Types::PlayerCommandType;
        PlayerCommand() 
        {
            m_type = type;
            reset();
        }
        bool isKeyMoveRight;
        bool isKeyMoveLeft;
        bool isKeyJump;
        bool isKeyAttack;
        bool isKeyCrouching;
        void reset()
        {
            isKeyMoveRight = false;
            isKeyMoveLeft = false;
            isKeyJump = false;
            isKeyAttack = false;
            isKeyCrouching = false;
        }
    };
} // namespace Garden::Components