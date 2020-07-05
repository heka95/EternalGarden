#include "systems/TextSystem.hpp"
#include "core/Manager.hpp"
#include <iostream>

namespace Garden::Systems
{
    TextSystem::TextSystem(int priority, Manager *manager, SDL_Renderer *renderer) : System(priority, {}, manager)
    {
        m_renderer = renderer;
        manager->registerHandler<Garden::LoadFontEvent>(&TextSystem::onLoadFont, this);
        manager->registerHandler<Garden::CreateTextEvent>(&TextSystem::onCreateText, this);
    }

    TextSystem::~TextSystem()
    {
        for (auto font : m_fontsMap)
        {
            TTF_CloseFont(font.second);
        }
        m_fontsMap.clear();

        for (auto texture : m_textures)
        {
            SDL_DestroyTexture(texture.second);
        }
        m_textures.clear();
        m_definitions.clear();
    }

    Garden::EventStatus TextSystem::onLoadFont(Garden::Entity source, Garden::EventType type, Garden::Event *event)
    {
        assert(type == Garden::LoadFontEvent::type);
        auto eventData = static_cast<Garden::LoadFontEvent *>(event);
        loadFont(eventData->id, eventData->sourceFile, eventData->size);
        return Garden::EventStatus::KEEP_AFTER_CALL;
    }

    Garden::EventStatus TextSystem::onCreateText(Garden::Entity source, Garden::EventType type, Garden::Event *event)
    {
        assert(type == Garden::CreateTextEvent::type);
        auto eventData = static_cast<Garden::CreateTextEvent *>(event);
        createText(eventData->textId, eventData->definition);
        return Garden::EventStatus::KEEP_AFTER_CALL;
    }

    void TextSystem::loadFont(std::string const &id, std::string &sourceFile, int size)
    {
        auto font = TTF_OpenFont(sourceFile.c_str(), size);
        if (font != nullptr)
        {
            m_fontsMap[id] = font;
        }
        else
        {
            std::cerr << "TTF load font error:" << TTF_GetError() << std::endl;
        }
    }

    void TextSystem::createText(std::string const &textId, TextDefinition &definition)
    {
        auto textSurface = TTF_RenderUTF8_Blended(m_fontsMap[definition.fontId], definition.message.c_str(), definition.color);
        if (textSurface == nullptr)
        {
            std::cerr << "TTF create texture to draw error:" << TTF_GetError() << std::endl;
        }
        auto texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
        SDL_FreeSurface(textSurface);
        m_textures[textId] = texture;
        m_definitions[textId] = definition;
    }

    void TextSystem::update(float deltaTime)
    {
        int width{0};
        int height{0};
        for (auto keyvalueTexture : m_textures)
        {
            auto definition = m_definitions[keyvalueTexture.first];
            if (definition.draw)
            {
                SDL_QueryTexture(keyvalueTexture.second, nullptr, nullptr, &width, &height);
                SDL_Rect sourceRect = {0, 0, width, height};
                SDL_Rect destRect = {definition.positionX, definition.positionY, width, height};
                SDL_RenderCopy(m_renderer, keyvalueTexture.second, &sourceRect, &destRect);
            }
        }
    }
} // namespace Garden::Systems