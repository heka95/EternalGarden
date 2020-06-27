#pragma once

#include "SDL.h"
#include "components/SpriteAnimation.hpp"
#include "systems/System.hpp"

namespace Garden::Systems
{
    class AnimatorSystem : public Garden::System
    {
    public:
        AnimatorSystem(int priority, Manager *manager) : System(priority, {Garden::Components::SpriteAnimation::type}, manager)
        {
        }
        virtual void updateEntity(float deltaTime, Entity e) override;
    };
} // namespace Garden::Systems