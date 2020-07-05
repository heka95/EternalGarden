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
#define ENGINE_UPDATE_SPEED 60.0f

    enum class EventStatus
    {
        KEEP_AFTER_CALL,
        DELETE_AFTER_CALL,
    };

    enum EventTypes : EventType
    {
        ExitGame = 1,
        Pause = 2
    };

    enum Types : ComponentType
    {
        TransformationType = 1,
        SpriteRendererType = 2,
        SpriteAnimationType = 3,
        PlayerCommandType = 4,
        RigidBodyType = 5,
        WorldType = 6,
        CameraComponentType = 7
    };
} // namespace Garden