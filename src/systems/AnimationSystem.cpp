#include "systems/AnimatorSystem.hpp"
#include "core/Manager.hpp"
#include "components/SpriteAnimation.hpp"
#include "Vector2D.hpp"
#include "components/SpriteRenderer.hpp"

namespace Garden::Systems
{
    void AnimatorSystem::updateEntity(float deltaTime, Entity e)
    {
        auto animator = getManager()->getComponent<Garden::Components::SpriteAnimation>(e);
        auto spriteRenderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);
        auto currentAnimation = animator->animations[animator->currentAnimation];
        auto currentFrame = (SDL_GetTicks() / currentAnimation.speed) % currentAnimation.frameCount;

        spriteRenderer->drawHeight = currentAnimation.height;
        spriteRenderer->drawWidth = currentAnimation.width;
        spriteRenderer->textureId = currentAnimation.textureId;
        spriteRenderer->origin.X = currentAnimation.width / 2;
        spriteRenderer->origin.Y = currentAnimation.height / 2;

        auto xOffset = currentAnimation.width * currentFrame;
        auto yOffset = currentAnimation.height * (currentAnimation.rowCount - 1);
        spriteRenderer->drawOffset = Garden::Vector2D{static_cast<float>(xOffset), static_cast<float>(yOffset)};
    }
} // namespace Garden::Systems