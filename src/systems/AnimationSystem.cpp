#include "AnimatorSystem.hpp"

namespace Garden::Systems
{
    void AnimatorSystem::updateEntity(float deltaTime, Entity e)
    {
        auto cAnimator = getManager()->getComponent<Garden::Components::SpriteAnimation>(e);
        auto cRenderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

        auto currentFrame = (SDL_GetTicks() / cAnimator->getSpeed()) % cAnimator->getFrameCount();

        cRenderer->setDrawHeight(cAnimator->getHeight());
        cRenderer->setDrawWidth(cAnimator->getWidth());

        auto xOffset = cAnimator->getWidth() * currentFrame;
        auto yOffset = cAnimator->getHeight() * (cAnimator->getRowCount() - 1);
        cRenderer->setDrawOffset(Garden::Vector2D{(float)xOffset, (float)yOffset});
    }
} // namespace Garden::Systems