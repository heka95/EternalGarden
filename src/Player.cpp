#include "Player.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Types/GameTypes.hpp"
#include "Input.hpp"

Player::Player(Garden::ObjectMetaData *metaData) : Character(metaData)
{
    m_rigidBody = new Garden::RigidBody();
    m_Animation = new Animation();
    m_Animation->setMetaData(metaData->TextureId, 1, 8, 100);
}

void Player::draw()
{
    m_Animation->draw(Garden::Vector2I{(int)m_transform->X, (int)m_transform->Y}, m_size);
}

void Player::update(float deltaTime)
{
    m_Animation->setMetaData("player", 1, 10, 100);
    m_rigidBody->setForceZero();

    if (Input::getInstance().getKeyDown(SDL_SCANCODE_A))
    {
        m_rigidBody->setForceX(-5);
        m_Animation->setMetaData("player_run", 1, 8, 100, Garden::Flip::HORIZONTAL);
    }

    if (Input::getInstance().getKeyDown(SDL_SCANCODE_D))
    {
        m_rigidBody->setForceX(5);
        m_Animation->setMetaData("player_run", 1, 8, 100);
    }

    m_rigidBody->update(deltaTime);
    m_transform->TranslateX(m_rigidBody->getPosition().X);
    //m_transform->TranslateY(m_rigidBody->getPosition().Y);
    m_origin->X = m_transform->X + m_size.width / 2;
    m_origin->Y = m_transform->Y + m_size.height / 2;
    m_Animation->update();
}

void Player::release()
{
    TextureManager::getInstance().release();
}