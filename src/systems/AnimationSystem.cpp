#include "systems/AnimatorSystem.hpp"
#include "core/Manager.hpp"
#include "components/SpriteAnimation.hpp"
#include "Vector2D.hpp"
#include "components/SpriteRenderer.hpp"

namespace Garden::Systems
{
    void AnimatorSystem::updateEntity(float deltaTime, Entity e)
    {
        auto cAnimator = getManager()->getComponent<Garden::Components::SpriteAnimation>(e);
        auto cRenderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

        auto currentFrame = (SDL_GetTicks() / cAnimator->speed) % cAnimator->frameCount;

        cRenderer->drawHeight = cAnimator->height;
        cRenderer->drawWidth = cAnimator->width;

        auto xOffset = cAnimator->width * currentFrame;
        auto yOffset = cAnimator->height * (cAnimator->rowCount - 1);
        cRenderer->drawOffset = Garden::Vector2D{(float)xOffset, (float)yOffset};
    }
} // namespace Garden::Systems