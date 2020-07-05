#pragma once
#include <functional>
#include "core/ECSTypes.hpp"
#include "systems/TextDefinition.hpp"

namespace Garden
{
    class Event
    {
    public:
        EventType getType() const { return m_type; }

    protected:
        EventType m_type = INVALID_TYPE;
    };

    class LoadFontEvent : public Event
    {
    public:
        static const EventType type = EventTypes::LoadFont;

        LoadFontEvent()
        {
            m_type = type;
        }
        std::string id{""};
        std::string sourceFile{""};
        int size{10};
    };

    class CreateTextEvent : public Event
    {
    public:
        static const EventType type = EventTypes::CreateText;

        CreateTextEvent()
        {
            m_type = type;
        }
        std::string textId{""};
        Garden::Systems::TextDefinition definition;
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

    class SetVolumeEvent : public Event
    {
    public:
        static const EventType type = EventTypes::SetVolume;

        SetVolumeEvent()
        {
            m_type = type;
        }
        int volume{128};
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

    class DebugToggleEvent : public Event
    {
    public:
        static const EventType type = EventTypes::DebugToggle;

        DebugToggleEvent()
        {
            m_type = type;
        }
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