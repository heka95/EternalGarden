#pragma once

#include "GameTypes.hpp"
#include "Animation.hpp"

class OldSpriteAnimation : public Animation
{
public:
    OldSpriteAnimation(bool repeat = true);
    virtual void update(float deltaTime);
    void draw(Garden::Vector2I position, Garden::Size size, float xScale = 1, float yScale = 1, Garden::Flip flip = Garden::Flip::NONE);
    void setMetaData(std::string textureId, int row, int frameCount, int speed);

private:
    int m_speed;
    int m_spriteRow;
    int m_frameCount;
    std::string m_textureId;
};