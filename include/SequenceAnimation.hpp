#pragma once

#include <map>
#include <string>
#include <vector>
#include "SDL.h"
#include "GameTypes.hpp"
#include "Animation.hpp"

struct Sequence
{
    int Speed;
    int Frames;
    int Width;
    int Height;
    std::vector<std::string> TextureIds;
};

class SequenceAnimation : public Animation
{
public:
    SequenceAnimation(bool repeat = true);
    virtual void update(float deltaTime);
    void parse(std::string sourceFile);
    void setCurrentSequence(std::string sequenceId);
    void setRepeat(bool repeat) { m_repeat = repeat; }
    void drawFrame(Garden::Vector2I position, Garden::Vector2F scale = Garden::Vector2F{1, 1}, Garden::Flip flip = Garden::Flip::NONE);

private:
    Sequence m_sequence;
    std::map<std::string, Sequence> m_sequences;
};