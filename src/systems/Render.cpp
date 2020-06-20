#include "Render.hpp"
#include "../components/Components.hpp"
#include "../TextureManager.hpp"

namespace Garden::Systems
{
    void Render::preUpdate(float delta)
    {
        SDL_SetRenderDrawColor(m_renderer, 0x2B, 0x84, 0xAB, 0xFF);
        SDL_RenderClear(m_renderer);
    }

    void Render::postUpdate(float delta)
    {
        SDL_RenderPresent(m_renderer);
    }

    void Render::updateEntity(float deltaTime, Entity e)
    {
        auto cTransform = getManager()->getComponent<Garden::Components::Transform>(e);
        auto position = cTransform->getPosition();
        auto cRenderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

        SDL_Rect sourceRect = {(int)cRenderer->getDrawOffset().X, (int)cRenderer->getDrawOffset().Y, cRenderer->getDrawWidth(), cRenderer->getDrawHeight()};
        auto renderWidth = cRenderer->getDrawWidth() * cRenderer->getScale().X;
        auto renderHeight = cRenderer->getDrawHeight() * cRenderer->getScale().Y;
        SDL_FRect destinationRect = {position.X, position.Y, renderWidth, renderHeight};
        auto texture = TextureManager::getInstance().getTextureFromId(cRenderer->getTextureId());
        SDL_RenderCopyExF(m_renderer, texture, &sourceRect, &destinationRect, cRenderer->getRotation(), nullptr, cRenderer->getFlip());

        /* after camera
        auto cameraPosition = Camera::getInstance().getPosition() * speedRatio;
        auto xRect = size.width * scale.X;
        auto yRect = size.height * scale.Y;
        SDL_Rect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, (int)xRect, (int)yRect};
*/
    }

} // namespace Garden::Systems