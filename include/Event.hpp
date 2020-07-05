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

    class ExitEvent : public Event
    {
    public:
        static const EventType type = EventTypes::ExitGame;

        ExitEvent()
        {
            m_type = type;
        }
        bool exitAsked{false};
    };

    class PauseEvent : public Event
    {
    public:
        static const EventType type = EventTypes::Pause;

        PauseEvent()
        {
            m_type = type;
        }
        bool pause{false};
    };

    typedef std::function<EventStatus(Entity, EventType, Event *)>
        EventHandler;
} // namespace Garden