#pragma once
#include <memory>

namespace Garden
{
    typedef int Type;
    typedef Type ComponentType;
    typedef Type Entity;
    typedef Type EventType;

#define INVALID_TYPE 0
#define INVALID_ENTITY Entity{-1}

    enum class EventStatus
    {
        KEEP, /**< The handler must be kept */
        DIE,  /**< The handler can be removed */
    };

    enum Types : ComponentType
    {
        TransformationType = 1,
        SpriteRendererType = 2,
        SpriteAnimationType = 3,
        PlayerCommandType = 4,
        RigidBodyType = 5,
        WorldType = 6
    };
} // namespace Garden