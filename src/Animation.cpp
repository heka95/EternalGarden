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

void Animation::draw(Garden::Vector2I position, Garden::Size spriteSize, Garden::Flip flip)
{
    TextureManager::getInstance().drawFrame(m_textureId, position, spriteSize, m_row, m_frame, flip);
}

void Animation::setMetaData(std::string textureId, int row, int frameCount, int animationSpeed)
{
    m_textureId = textureId;
    m_row = row;
    m_frameCount = frameCount;
    m_animationSpeed = animationSpeed;
}