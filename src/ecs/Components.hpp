#pragma once

#include "ecs.hpp"

class PositionComponent : public Component
{
public:
    int x() { return xposition; }
    int y() { return yposition; }
    void setPosition(int x, int y)
    {
        xposition = x;
        yposition = y;
    }
    void init() override
    {
        xposition = 0;
        yposition = 0;
    }
    void update() override
    {
        xposition++;
        yposition++;
    }

private:
    int xposition{0};
    int yposition{0};
};