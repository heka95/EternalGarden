#pragma once

class Animation
{
public:
    Animation(bool repeat = true) : m_repeat(repeat) { m_isEnded = false; }
    virtual void update(float deltaTime) = 0;
    inline bool isEndend() { return m_isEnded; }

protected:
    bool m_repeat;
    bool m_isEnded;
    int m_currentFrame;
};