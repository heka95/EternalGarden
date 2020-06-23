#pragma once
#include "../core/Core.hpp"

namespace Garden::Components
{
    enum Types : Garden::ComponentType
    {
        TransformationType = 1,
        SpriteRendererType = 2,
        SpriteAnimationType = 3,
        PlayerCommandType = 4,
        RigidBodyType = 5,
        WorldType = 6
    };
}