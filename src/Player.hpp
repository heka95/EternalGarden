#pragma once

#include "Character.hpp"

class Player : public Character
{
public:
    Player(Garden::ObjectMetaData *metaData);
    virtual void draw();
    virtual void update(float deltaTime);
    virtual void release();

private:
    int m_row;
    int m_frame;
    int m_frameCount;
    int m_animationSpeed;
};