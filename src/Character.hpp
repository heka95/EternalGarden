#pragma once

#include <string>
#include "GameObject.hpp"

class Character : public GameObject
{
public:
    Character(Garden::ObjectMetaData *metaData) : GameObject(metaData) {}
    virtual void draw() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void release() = 0;

    protected:
    std::string m_name;
};