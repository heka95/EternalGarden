#pragma once

#include "Character.hpp"
#include "Animation.hpp"

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
};