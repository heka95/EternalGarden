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
    void update();
    inline int getSceneWidth() { return m_sceneWidth; }
    inline int getSceneHeight() { return m_sceneHeight; }
    inline void moveX(float x) { m_position.X = x; }
    inline void moveY(float y) { m_position.Y = y; }
    inline void setSceneSize(int width, int height)
    {
        m_sceneWidth = width;
        m_sceneHeight = height;
    }

private:
    Camera();
    Camera(const Camera &object) = delete;
    Camera &operator=(const Camera &object) = delete;
    static std::unique_ptr<Camera> m_instance;
    Garden::Vector2I *m_target;
    Garden::Vector2I m_position;
    SDL_Rect m_viewBox;
    int m_sceneWidth;
    int m_sceneHeight;
};