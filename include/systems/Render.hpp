#pragma once

#include "SDL.h"
#include "components/Transformation.hpp"
#include "components/SpriteRenderer.hpp"
#include "systems/System.hpp"
#include "core/TextureStore.hpp"

namespace Garden::Systems
{
    class Render : public Garden::System
    {
    public:
        Render(Manager *manager, SDL_Renderer *renderer, Garden::Core::TextureStore *textureStore)
            : System(4, {Garden::Components::Transform::type, Garden::Components::SpriteRenderer::type}, manager)
        {
            m_renderer = renderer;
            m_store = textureStore;
        }
        virtual void preUpdate(float delta) override;
        virtual void postUpdate(float delta) override;
        virtual void updateEntity(float deltaTime, Entity e) override;

    private:
        SDL_Renderer *m_renderer;
        Garden::Core::TextureStore *m_store;
    };
} // namespace Garden::Systems