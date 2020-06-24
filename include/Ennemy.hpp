#pragma once

#include "Character.hpp"
#include "Collider.hpp"
#include "SequenceAnimation.hpp"
#include "OldRigidBody.hpp"

class Ennemy : public Character
{
public:
    Ennemy(Garden::ObjectMetaData *metaData);
    virtual void draw();
    virtual void update(float deltaTime);
    virtual void release();

private:
    Collider *m_collider;
    Garden::OldRigidBody *m_rigidBody;
    SequenceAnimation *m_animation;
    Garden::Vector2F m_lastSafePosition;
};