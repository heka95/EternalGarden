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

    class RegisterMusicEvent : public Event
    {
    public:
        static const EventType type = EventTypes::RegisterMusic;

        RegisterMusicEvent()
        {
            m_type = type;
        }
        std::string id{""};
        std::string sourceFile{""};
    };

    class RegisterSoundEvent : public Event
    {
    public:
        static const EventType type = EventTypes::RegisterSound;

        RegisterSoundEvent()
        {
            m_type = type;
        }
        std::string id{""};
        std::string sourceFile{""};
    };

    class PlayMusicEvent : public Event
    {
    public:
        static const EventType type = EventTypes::PlayMusic;

        PlayMusicEvent()
        {
            m_type = type;
        }
        std::string id{""};
    };

    class PlaySoundEvent : public Event
    {
    public:
        static const EventType type = EventTypes::PlaySound;

        PlaySoundEvent()
        {
            m_type = type;
        }
        std::string id{""};
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