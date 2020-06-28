#include "systems/CameraSystem.hpp"
#include "components/Transformation.hpp"
#include "core/Manager.hpp"
#include <iostream>

namespace Garden::Systems
{
    void CameraSystem::preUpdate(float deltaTime)
    {
        // in future, need to update on change window size
        auto windowWidth = 800;
        auto windowHeight = 600;
        auto transformation = getManager()->getComponent<Garden::Components::Transform>(camera->target);
        auto targetPosition = transformation->Position;

        if (camera->target != INVALID_ENTITY)
        {
            camera->viewBox.x = targetPosition.X - (windowWidth / 2);
            camera->viewBox.y = targetPosition.Y - (windowHeight / 2);

            if (camera->viewBox.x < 0)
            {
                camera->viewBox.x = 0;
            }

            if (camera->viewBox.y < 0)
            {
                camera->viewBox.y = 0;
            }

            if (camera->viewBox.x > (camera->sceneWidth - camera->viewBox.w))
            {
                camera->viewBox.x = (camera->sceneWidth - camera->viewBox.w);
            }
            if (camera->viewBox.y > (camera->sceneHeight - camera->viewBox.h))
            {
                camera->viewBox.y = (camera->sceneHeight - camera->viewBox.h);
            }
            camera->position = Garden::Vector2D(camera->viewBox.x, camera->viewBox.y);
        }
    }
} // namespace Garden::Systems