#pragma once
#include <functional>
#include "core/ECSTypes.hpp"

namespace Garden
{
    class Event
    {
    public:
        EventType getType() const { return m_type; }

    protected:
        EventType m_type = INVALID_TYPE;
    };

    typedef std::function<EventStatus(Entity, EventType, Event *)> EventHandler;
} // namespace Garden