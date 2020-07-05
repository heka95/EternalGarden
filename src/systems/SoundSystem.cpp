#include "systems/SoundSystem.hpp"
#include "core/Manager.hpp"
#include <iostream>

namespace Garden::Systems
{

    SoundSystem::SoundSystem(int priority, Manager *manager) : System(priority, {}, manager)
    {
        if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE) < 0)
        {
            std::cerr << "Error on load music:" << Mix_GetError() << std::endl;
            std::cout << "Audio System disabled !" << std::endl;
        }
        else
        {
            manager->registerHandler<Garden::RegisterMusicEvent>(&SoundSystem::onRegisterMusic, this);
            manager->registerHandler<Garden::RegisterSoundEvent>(&SoundSystem::onRegisterSound, this);
            manager->registerHandler<Garden::PlayMusicEvent>(&SoundSystem::onPlayMusic, this);
            manager->registerHandler<Garden::PlaySoundEvent>(&SoundSystem::onPlaySound, this);
        }
    }

    Garden::EventStatus SoundSystem::onRegisterMusic(Garden::Entity source, Garden::EventType type, Garden::Event *event)
    {
        assert(type == Garden::RegisterMusicEvent::type);
        auto eventData = static_cast<Garden::RegisterMusicEvent *>(event);
        loadMusic(eventData->id, eventData->sourceFile);
        return Garden::EventStatus::KEEP_AFTER_CALL;
    }

    Garden::EventStatus SoundSystem::onRegisterSound(Garden::Entity source, Garden::EventType type, Garden::Event *event)
    {
        assert(type == Garden::RegisterSoundEvent::type);
        auto eventData = static_cast<Garden::RegisterSoundEvent *>(event);
        loadSound(eventData->id, eventData->sourceFile);
        return Garden::EventStatus::KEEP_AFTER_CALL;
    }

    Garden::EventStatus SoundSystem::onPlayMusic(Garden::Entity source, Garden::EventType type, Garden::Event *event)
    {
        assert(type == Garden::PlayMusicEvent::type);
        auto eventData = static_cast<Garden::PlayMusicEvent *>(event);
        playMusic(eventData->id);
        return Garden::EventStatus::KEEP_AFTER_CALL;
    }

    Garden::EventStatus SoundSystem::onPlaySound(Garden::Entity source, Garden::EventType type, Garden::Event *event)
    {
        assert(type == Garden::PlaySoundEvent::type);
        auto eventData = static_cast<Garden::PlaySoundEvent *>(event);
        playSound(eventData->id);
        return Garden::EventStatus::KEEP_AFTER_CALL;
    }

    void SoundSystem::loadMusic(std::string const &id, std::string &sourceFile)
    {
        Mix_Music *music = Mix_LoadMUS(sourceFile.c_str());
        if (music != nullptr)
        {
            m_musicsMap[id] = music;
        }
        else
        {
            std::cerr << "Error on load music:" << Mix_GetError() << std::endl;
        }
    }

    void SoundSystem::playMusic(std::string const &id)
    {
        auto musicFromId = m_musicsMap[id];
        if (musicFromId == nullptr)
        {
            std::cerr << "Music ID: " << id << " not found" << std::endl;
            return;
        }
        if (Mix_PlayMusic(musicFromId, -1) == -1)
        {
            std::cerr << "Error on play music:" << Mix_GetError() << std::endl;
        }
    }

    void SoundSystem::loadSound(std::string const &id, std::string &sourceFile)
    {
        Mix_Chunk *sound = Mix_LoadWAV(sourceFile.c_str());
        if (sound != nullptr)
        {
            m_soundsMap[id] = sound;
        }
        else
        {
            std::cerr << Mix_GetError() << std::endl;
        }
    }

    void SoundSystem::playSound(std::string const &id)
    {
        auto soundFromId = m_soundsMap[id];
        if (soundFromId == nullptr)
        {
            std::cerr << "Sound ID: " << id << " not found" << std::endl;
            return;
        }
        if (Mix_PlayChannel(-1, soundFromId, 0) == -1)
        {
            std::cerr << "Error on play sound:" << Mix_GetError() << std::endl;
        }
    }

    SoundSystem::~SoundSystem()
    {
        for (auto music : m_musicsMap)
        {
            Mix_FreeMusic(music.second);
        }
        m_musicsMap.clear();

        for (auto sound : m_soundsMap)
        {
            Mix_FreeChunk(sound.second);
        }
        m_soundsMap.clear();
    }
} // namespace Garden::Systems