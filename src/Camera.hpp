#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "Types/GameTypes.hpp"
#include "GameEngine.hpp"

class Camera
{
public:
    virtual ~Camera() = default;
    static Camera &getInstance();
    SDL_Rect getViewBox();
    Garden::Vector2I getPosition();
    void setTarget(Garden::Vector2I *target);
    void update(float deltaTime);

private:
    Camera();
    Camera(const Camera &object) = delete;
    Camera &operator=(const Camera &object) = delete;
    static std::unique_ptr<Camera> m_instance;
    Garden::Vector2I *m_target;
    Garden::Vector2I m_position;
    SDL_Rect m_viewBox;
};