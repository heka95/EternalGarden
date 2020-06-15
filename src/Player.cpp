#include "Player.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Types/GameTypes.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "CollisionHandler.hpp"

Player::Player(Garden::ObjectMetaData *metaData) : Character(metaData)
{
    m_jumpTime = JUMP_TIME;
    m_jumpForce = JUMP_FORCE;
    m_collider = new Collider();
    m_collider->SetBuffer(0, 0, 0, 0);
    m_rigidBody = new Garden::RigidBody();
    m_rigidBody->setGravity(3.0f);
    m_Animation = new Animation();
    m_Animation->setMetaData(metaData->TextureId, 1, 8, 100);
}

void Player::draw()
{
    m_Animation->draw(Garden::Vector2I{(int)m_transform->X, (int)m_transform->Y}, m_size);

    auto cameraPosition = Camera::getInstance().getPosition();
    SDL_Rect colliderBox = m_collider->get();
    colliderBox.x -= cameraPosition.X;
    colliderBox.y -= cameraPosition.Y;
    SDL_RenderDrawRect(GameEngine::getInstance().getRenderer(), &colliderBox);
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

    if (Input::getInstance().getKeyDown(SDL_SCANCODE_J) && m_isGrounded)
    {
        m_isJumping = true;
        m_isGrounded = false;
        m_rigidBody->setForceY(-m_jumpForce);
    }
    if (Input::getInstance().getKeyDown(SDL_SCANCODE_J) && m_isJumping && m_jumpTime > 0)
    {
        m_jumpTime -= deltaTime;
        m_rigidBody->setForceY(-m_jumpForce);
    }
    else
    {
        m_isJumping = false;
        m_jumpTime = JUMP_TIME;
    }

    m_rigidBody->update(deltaTime);
    m_lastSafePosition.X = m_transform->X;
    m_transform->X += m_rigidBody->getPosition().X;
    m_collider->set(m_transform->X, m_transform->Y, 56, 64);

    if (CollisionHandler::getInstance().worldCollision(m_collider->get()))
    {
        m_transform->X = m_lastSafePosition.X;
    }

    m_rigidBody->update(deltaTime);
    m_lastSafePosition.Y = m_transform->Y;
    m_transform->Y += m_rigidBody->getPosition().Y;
    m_collider->set(m_transform->X, m_transform->Y, 56, 64);

    if (CollisionHandler::getInstance().worldCollision(m_collider->get()))
    {
        m_isGrounded = true;
        m_transform->Y = m_lastSafePosition.Y;
    }
    else
    {
        m_isGrounded = false;
    }

    if (m_isJumping || !m_isGrounded)
    {
        m_Animation->setMetaData("player_jump", 1, 8, 100);
    }
    m_origin->X = m_transform->X + m_size.width / 2;
    m_origin->Y = m_transform->Y + m_size.height / 2;
    m_Animation->update();
}

void Player::release()
{
    TextureManager::getInstance().unload(m_textureId);
}