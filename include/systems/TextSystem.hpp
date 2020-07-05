#pragma once

#include <map>
#include <string>
#include "SDL_ttf.h"
#include "systems/System.hpp"
#include "core/ECSTypes.hpp"
#include "Event.hpp"
#include "systems/TextDefinition.hpp"

namespace Garden::Systems
{
    using mapFonts = std::map<std::string, TTF_Font *>;
    using mapTextures = std::map<std::string, SDL_Texture *>;
    using mapDefinitions = std::map<std::string, TextDefinition>;

    class TextSystem : public Garden::System
    {
    public:
        TextSystem(int priority, Manager *manager, SDL_Renderer *renderer);
        ~TextSystem();
        void loadFont(std::string const &id, std::string &sourceFile, int size);
        void createText(std::string const &textId, TextDefinition &definition);
        virtual void update(float deltaTime) override;

    private:
        Garden::EventStatus onLoadFont(Garden::Entity source, Garden::EventType type, Garden::Event *event);
        Garden::EventStatus onCreateText(Garden::Entity source, Garden::EventType type, Garden::Event *event);
        mapFonts m_fontsMap;
        SDL_Renderer *m_renderer;
        mapTextures m_textures;
        mapDefinitions m_definitions;
    };
} // namespace Garden::Systems