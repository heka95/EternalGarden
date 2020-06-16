#include "Player.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Types/GameTypes.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "CollisionHandler.hpp"
#include "ObjectFactory.hpp"

// Register type to factory
static Registrar<Player> registrar("PLAYER");

Player::Player(Garden::ObjectMetaData *metaData) : Character(metaData)
{
    m_isRunning = false;
    m_isJumping = false;
    m_isFalling = false;
    m_isGrounded = false;
    m_isAttacking = false;
    m_isCrouching = false;

    m_renderFlip = Garden::Flip::NONE;
    m_jumpTime = JUMP_TIME;
    m_jumpForce = JUMP_FORCE;
    m_attackTime = ATTACK_TIME;

    m_collider = new Collider();
    m_collider->SetBuffer(0, 10, 0, 0);

    m_rigidBody = new Garden::RigidBody();
    m_rigidBody->setGravity(3.5f);

    m_Animation = new SpriteAnimation();
    m_Animation->setMetaData(metaData->TextureId, 1, 8, 100);
}

void Player::draw()
{
    m_Animation->draw(Garden::Vector2I{(int)m_transform->X, (int)m_transform->Y}, m_size, 1.0f, 1.0f, m_renderFlip);
    m_collider->draw();
}

void Player::update(float deltaTime)
{
    m_isRunning = false;
    m_isCrouching = false;
    m_rigidBody->setForceZero();

    if (Input::getInstance().getAxisKey(Axis::HORIZONTAL) == 1 && !m_isAttacking)
    {
        m_rigidBody->setForceX(1 * RUN_FORCE);
        m_renderFlip = Garden::Flip::NONE;
        m_isRunning = true;
    }

    if (Input::getInstance().getAxisKey(Axis::HORIZONTAL) == -1 && !m_isAttacking)
    {
        m_rigidBody->setForceX(-1 * RUN_FORCE);
        m_renderFlip = Garden::Flip::HORIZONTAL;
        m_isRunning = true;
    }

    if (Input::getInstance().getAxisKey(Axis::VERTICAL) == -1)
    {
        m_rigidBody->setForceZero();
        m_isCrouching = true;
    }

    if (Input::getInstance().getKeyDown(SDL_SCANCODE_K))
    {
        m_rigidBody->setForceZero();
        m_isAttacking = true;
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

    m_isFalling = (m_rigidBody->getVelocity().Y > 0 && !m_isGrounded);

    if (m_isAttacking && m_attackTime > 0)
    {
        m_attackTime -= deltaTime;
    }
    else
    {
        m_isAttacking = false;
        m_attackTime = ATTACK_TIME;
    }

    m_rigidBody->update(deltaTime);
    m_lastSafePosition.X = m_transform->X;
    m_transform->X += m_rigidBody->getPosition().X;
    m_collider->set(m_transform->X, m_transform->Y, 58, 64);

    if (CollisionHandler::getInstance().worldCollision(m_collider->get()))
    {
        m_transform->X = m_lastSafePosition.X;
    }

    m_rigidBody->update(deltaTime);
    m_lastSafePosition.Y = m_transform->Y;
    m_transform->Y += m_rigidBody->getPosition().Y;
    m_collider->set(m_transform->X, m_transform->Y, 58, 64);

    if (CollisionHandler::getInstance().worldCollision(m_collider->get()))
    {
        m_isGrounded = true;
        m_transform->Y = m_lastSafePosition.Y;
    }
    else
    {
        m_isGrounded = false;
    }

    m_origin->X = m_transform->X + m_size.width / 2;
    m_origin->Y = m_transform->Y + m_size.height / 2;
    animationState();
    m_Animation->update(deltaTime);
    //std::cout << "[X=" << m_origin->X << ";Y=" << m_origin->Y << "]" << std::endl;
}

void Player::animationState()
{
    m_Animation->setMetaData("player", 1, 12, 100);

    if (m_isRunning)
    {
        m_Animation->setMetaData("player_run", 1, 8, 100);
    }
    if (m_isCrouching)
    {
        m_Animation->setMetaData("player_crouch", 1, 8, 100);
    }
    if (m_isJumping)
    {
        m_Animation->setMetaData("player_jump", 1, 8, 100);
    }
    if (m_isFalling)
    {
        m_Animation->setMetaData("player_fall", 1, 8, 100);
    }
    if (m_isAttacking)
    {
        m_Animation->setMetaData("player_attack", 1, 8, 100);
    }
}

void Player::release()
{
    TextureManager::getInstance().unload(m_textureId);
}