#pragma once

#include "SDL.h"
#include "Core.hpp"
#include "Components.hpp"
#include "Transformation.hpp"
#include "SpriteRenderer.hpp"

namespace Garden::Systems
{
    class Render : public Garden::System
    {
    public:
        Render(Manager *manager, SDL_Renderer *renderer)
            : System(4, {Garden::Components::Transform::type, Garden::Components::SpriteRenderer::type}, manager)
        {
            m_renderer = renderer;
        }
        virtual void preUpdate(float delta) override;
        virtual void postUpdate(float delta) override;
        virtual void updateEntity(float deltaTime, Entity e) override;

    private:
        SDL_Renderer *m_renderer;
    };
} // namespace Garden::Systems