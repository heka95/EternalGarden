#pragma once

#include "SDL.h"
#include "components/Transformation.hpp"
#include "components/SpriteRenderer.hpp"
#include "systems/System.hpp"
#include "core/TextureStore.hpp"
#include "components/CameraComponent.hpp"
#include "components/World.hpp"

namespace Garden::Systems
{
    class Render : public Garden::System
    {
    public:
        Render(int priority, Manager *manager, SDL_Renderer *renderer, Garden::Core::TextureStore *textureStore,
        Garden::Components::World *world, Garden::Components::CameraComponent *camera)
            : System(priority, {Garden::Components::Transform::type, Garden::Components::SpriteRenderer::type}, manager)
        {
            m_renderer = renderer;
            m_store = textureStore;
            m_world = world;
            m_camera = camera;
        }
        virtual void update(float deltaTime) override;
        virtual void preUpdate(float delta) override;
        virtual void postUpdate(float delta) override;
        virtual void updateEntity(float deltaTime, Entity e) override;

    private:
        void drawMap();
        void drawBackground();
        SDL_Renderer *m_renderer;
        Garden::Core::TextureStore *m_store;
        Garden::Components::World *m_world;
        Garden::Components::CameraComponent *m_camera;
        int yPosition{0};
    };
} // namespace Garden::Systems