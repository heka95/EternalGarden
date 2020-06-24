#pragma once

#include "SDL.h"
#include "Core.hpp"
#include "Components.hpp"
#include "SpriteAnimation.hpp"

namespace Garden::Systems
{
    class AnimatorSystem : public Garden::System
    {
    public:
        AnimatorSystem(Manager *manager) : System(3, {Garden::Components::SpriteAnimation::type}, manager)
        {
        }
        virtual void updateEntity(float deltaTime, Entity e) override;
    };
} // namespace Garden::Systems