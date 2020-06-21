#pragma once

#include <SDL2/SDL.h>
#include "../core/Core.hpp"
#include "../components/Components.hpp"

namespace Garden::Systems
{
    class AnimatorSystem : public Garden::System
    {
    public:
        AnimatorSystem(Manager *manager) : System(3, {Garden::Components::SpriteAnimationType}, manager)
        {
        }
        virtual void updateEntity(float deltaTime, Entity e) override;
    };
} // namespace Garden::Systems