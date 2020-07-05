#pragma once

#include <string>
#include <map>
#include "SDL_mixer.h"
#include "systems/System.hpp"

namespace Garden::Systems
{
    using mapSounds = std::map<std::string, Mix_Chunk *>;
    using mapMusics = std::map<std::string, Mix_Music *>;

    class SoundSystem : public Garden::System
    {
    public:
        SoundSystem(int priority, Manager *manager)
            : System(priority, {}, manager)
        {
        }
        void loadMusic(std::string const &id, std::string &sourceFile);
        void playMusic(std::string const &id);

        void loadSound(std::string const &id, std::string &sourceFile);
        void playSound(std::string const &id);

    private:
        mapMusics m_musicsMap;
        mapSounds m_soundsMap;
    };
} // namespace Garden::Systems