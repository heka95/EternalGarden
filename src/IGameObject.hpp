#pragma once

class IGameObject
{
public:
    virtual void draw() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void release() = 0;
};