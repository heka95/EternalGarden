#include "Player.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Types/GameTypes.hpp"

Player::Player(Garden::ObjectMetaData *metaData) : Character(metaData)
{
    m_frameCount = 10;
    m_row = 1;
    m_animationSpeed = 40;
}

void Player::draw()
{
    TextureManager::getInstance().drawFrame(m_textureId, Garden::Vector2I{(int)m_transform->X, (int)m_transform->Y}, m_size, m_row, m_frame);
}

void Player::update(float deltaTime)
{
    m_frame = (SDL_GetTicks() / m_animationSpeed) % m_frameCount;
}

void Player::release()
{
    TextureManager::getInstance().release();
}