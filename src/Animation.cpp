#include "Animation.hpp"
#include <SDL2/SDL.h>
#include "TextureManager.hpp"

Animation::Animation()
{
}

void Animation::update()
{
    m_frame = (SDL_GetTicks() / m_animationSpeed) % m_frameCount;
}

void Animation::draw(Garden::Vector2I position, Garden::Size spriteSize)
{
    TextureManager::getInstance().drawFrame(m_textureId, position, spriteSize, m_row, m_frame, m_flip);
}

void Animation::setMetaData(std::string textureId, int row, int frameCount, int animationSpeed, Garden::Flip flip)
{
    m_textureId = textureId;
    m_row = row;
    m_frameCount = frameCount;
    m_animationSpeed = animationSpeed;
    m_flip = flip;
}