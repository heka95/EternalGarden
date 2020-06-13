#include "Player.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Types/GameTypes.hpp"

Player::Player(Garden::ObjectMetaData *metaData) : Character(metaData)
{
    m_Animation = new Animation();
    m_Animation->setMetaData(metaData->TextureId, 1, 10, 40);
}

void Player::draw()
{
    m_Animation->draw(Garden::Vector2I{(int)m_transform->X, (int)m_transform->Y}, m_size);
}

void Player::update(float deltaTime)
{
    m_Animation->update();
}

void Player::release()
{
    TextureManager::getInstance().release();
}