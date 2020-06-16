#include "SpriteAnimation.hpp"
#include "TextureManager.hpp"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat)
{
}

void SpriteAnimation::draw(Garden::Vector2I position, Garden::Size size, float xScale, float yScale, Garden::Flip flip)
{
    TextureManager::getInstance().drawFrame(m_textureId, position, size, m_spriteRow, m_currentFrame, flip);
}

void SpriteAnimation::update(float deltaTime)
{
    m_currentFrame = (SDL_GetTicks() / m_speed) % m_frameCount;
}

void SpriteAnimation::setMetaData(std::string textureId, int row, int frameCount, int speed)
{
    m_speed = speed;
    m_textureId = textureId;
    m_spriteRow = row;
    m_frameCount = frameCount;
}