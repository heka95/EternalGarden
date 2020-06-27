#include "OldSpriteAnimation.hpp"
#include "OldTextureManager.hpp"

OldSpriteAnimation::OldSpriteAnimation(bool repeat) : Animation(repeat)
{
}

void OldSpriteAnimation::draw(Garden::Vector2I position, Garden::Size size, float xScale, float yScale, Garden::Flip flip)
{
    OldTextureManager::getInstance().drawFrame(m_textureId, position, size, m_spriteRow, m_currentFrame, flip);
}

void OldSpriteAnimation::update(float deltaTime)
{
    m_currentFrame = (SDL_GetTicks() / m_speed) % m_frameCount;
}

void OldSpriteAnimation::setMetaData(std::string textureId, int row, int frameCount, int speed)
{
    m_speed = speed;
    m_textureId = textureId;
    m_spriteRow = row;
    m_frameCount = frameCount;
}