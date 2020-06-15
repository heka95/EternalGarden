#pragma once

#include "Character.hpp"
#include "Animation.hpp"
#include "Collider.hpp"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

class Player : public Character
{
public:
    Player(Garden::ObjectMetaData *metaData);
    virtual void draw();
    virtual void update(float deltaTime);
    virtual void release();

private:
    Animation *m_Animation;
    Garden::RigidBody *m_rigidBody;
    bool m_isJumping;
    bool m_isGrounded;
    float m_jumpTime;
    float m_jumpForce;
    Collider *m_collider;
    Garden::Vector2F m_lastSafePosition;
};