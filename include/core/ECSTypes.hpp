#pragma once
#include <memory>

namespace Garden
{
#define INVALID_TYPE 0
    typedef int Type;
    typedef Type ComponentType;
    typedef Type Entity;
    typedef Type EventType;

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