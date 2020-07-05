#pragma once

#include <string>
#include <map>
#include "SDL_mixer.h"
#include "systems/System.hpp"
#include "core/ECSTypes.hpp"
#include "Event.hpp"

namespace Garden::Systems
{
    using mapSounds = std::map<std::string, Mix_Chunk *>;
    using mapMusics = std::map<std::string, Mix_Music *>;
    const int SOUND_FREQUENCY = 44100;
    const int CHUNK_SIZE = 2048;

    class SoundSystem : public Garden::System
    {
    public:
        SoundSystem(int priority, Manager *manager);
        ~SoundSystem();
        void loadMusic(std::string const &id, std::string &sourceFile);
        void playMusic(std::string const &id);

        void loadSound(std::string const &id, std::string &sourceFile);
        void playSound(std::string const &id);

    private:
        Garden::EventStatus onRegisterMusic(Garden::Entity source, Garden::EventType type, Garden::Event *event);
        Garden::EventStatus onRegisterSound(Garden::Entity source, Garden::EventType type, Garden::Event *event);
        Garden::EventStatus onPlayMusic(Garden::Entity source, Garden::EventType type, Garden::Event *event);
        Garden::EventStatus onPlaySound(Garden::Entity source, Garden::EventType type, Garden::Event *event);
        Garden::EventStatus onChangeSound(Garden::Entity source, Garden::EventType type, Garden::Event *event);
        mapMusics m_musicsMap;
        mapSounds m_soundsMap;
    };
} // namespace Garden::Systems