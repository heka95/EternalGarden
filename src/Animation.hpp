#pragma once

#include "Types/GameTypes.hpp"

class Animation
{
public:
    Animation();
    void update();
    void draw(Garden::Vector2I position, Garden::Size spriteSize);
    void setMetaData(std::string textureId, int row, int frameCount, int animationSpeed, Garden::Flip flip = Garden::Flip::NONE);

private:
    int m_row;
    int m_frame;
    int m_frameCount;
    int m_animationSpeed;
    std::string m_textureId;
    Garden::Flip m_flip;
};