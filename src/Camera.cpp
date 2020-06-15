#include "Camera.hpp"

std::unique_ptr<Camera> Camera::m_instance;
Camera &Camera::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new Camera());
    }
    return *m_instance.get();
}

Camera::Camera()
{
    auto windowSize = GameEngine::getInstance().getGraphicWindow()->getWindowSize();
    m_viewBox = SDL_Rect{0, 0, windowSize.width, windowSize.height};
}

SDL_Rect Camera::getViewBox() { return m_viewBox; }
Garden::Vector2I Camera::getPosition() { return m_position; }
void Camera::setTarget(Garden::Vector2I *target)
{
    m_target = target;
}

void Camera::update(float deltaTime)
{
    auto windowSize = GameEngine::getInstance().getGraphicWindow()->getWindowSize();

    if (m_target != nullptr)
    {
        m_viewBox.x = m_target->X - windowSize.width / 2;
        m_viewBox.y = m_target->Y - windowSize.height / 2;

        if (m_viewBox.x < 0)
        {
            m_viewBox.x = 0;
        }

        if (m_viewBox.y < 0)
        {
            m_viewBox.y = 0;
        }

        if (m_viewBox.x > (2 * windowSize.width - m_viewBox.w))
        {
            m_viewBox.x = (2 * windowSize.width - m_viewBox.w);
        }

        if (m_viewBox.y > (windowSize.height - m_viewBox.h))
        {
            m_viewBox.y = (windowSize.height - m_viewBox.h);
        }

        m_position = Garden::Vector2I(m_viewBox.x, m_viewBox.y);
    }
}