#pragma once

#include "Character.hpp"
#include "OldSpriteAnimation.hpp"
#include "OldRigidBody.hpp"
#include "Collider.hpp"

#define JUMP_TIME 30.0f
#define JUMP_FORCE 10.0f
#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Player : public Character
{
public:
    Player(Garden::ObjectMetaData *metaData);
    virtual void draw();
    virtual void update(float deltaTime);
    virtual void release();

private:
    void animationState();
    OldSpriteAnimation *m_Animation;
    Garden::OldRigidBody *m_rigidBody;
    bool m_isJumping;
    bool m_isGrounded;
    float m_jumpTime;
    float m_jumpForce;
    float m_attackTime;
    Collider *m_collider;
    Garden::Vector2F m_lastSafePosition;
    bool m_isRunning;
    bool m_isFalling;
    bool m_isAttacking;
    bool m_isCrouching;
};