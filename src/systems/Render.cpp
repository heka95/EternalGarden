#include "systems/Render.hpp"
#include "TextureManager.hpp"
#include "core/Manager.hpp"

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
        auto position = cTransform->Position;
        auto cRenderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

        SDL_Rect sourceRect = {(int)cRenderer->drawOffset.X, (int)cRenderer->drawOffset.Y, cRenderer->drawWidth, cRenderer->drawHeight};
        auto renderWidth = cRenderer->drawWidth * cRenderer->scale.X;
        auto renderHeight = cRenderer->drawHeight * cRenderer->scale.Y;
        SDL_FRect destinationRect = {position.X, position.Y, renderWidth, renderHeight};
        auto texture = TextureManager::getInstance().getTextureFromId(cRenderer->textureId);
        SDL_RenderCopyExF(m_renderer, texture, &sourceRect, &destinationRect, cRenderer->rotation, nullptr, cRenderer->flip);

        /* after camera
        auto cameraPosition = Camera::getInstance().getPosition() * speedRatio;
        auto xRect = size.width * scale.X;
        auto yRect = size.height * scale.Y;
        SDL_Rect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, (int)xRect, (int)yRect};
*/
    }

} // namespace Garden::Systems