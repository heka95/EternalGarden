#include "systems/CameraSystem.hpp"
#include "components/Transformation.hpp"
#include "core/Manager.hpp"
#include <iostream>
#include <algorithm>

namespace Garden::Systems
{
    void CameraSystem::preUpdate(float deltaTime)
    {
        // in future, need to update on change window size
        auto windowWidth = 800;
        auto windowHeight = 600;
        auto targetTransformation = getManager()->getComponent<Garden::Components::Transform>(camera->target);
        auto targetPosition = targetTransformation->Position;

        if (camera->target != INVALID_ENTITY)
        {
            camera->viewBox.x = targetPosition.X - (windowWidth / 2);
            camera->viewBox.y = targetPosition.Y - (windowHeight / 2);

            camera->viewBox.x = std::max(camera->viewBox.x, 0);
            camera->viewBox.x = std::min(camera->viewBox.x, (camera->sceneWidth - camera->viewBox.w));

            camera->viewBox.y = std::max(camera->viewBox.y, 0);          
            camera->viewBox.y = std::min(camera->viewBox.y, (camera->sceneHeight - camera->viewBox.h));

            camera->position = Garden::Vector2D(camera->viewBox.x, camera->viewBox.y);
        }
    }
} // namespace Garden::Systems