#include "SequenceAnimation.hpp"
#include <fstream>
#include "json.hpp"
#include "TextureManager.hpp"

SequenceAnimation::SequenceAnimation(bool repeat) : Animation(repeat)
{
}

void SequenceAnimation::drawFrame(Garden::Vector2I position, Garden::Vector2F scale, Garden::Flip flip)
{
    TextureManager::getInstance().draw(m_sequence.TextureIds[m_currentFrame], position, Garden::Size{m_sequence.Width, m_sequence.Height}, scale, flip);
}

void SequenceAnimation::update(float deltaTime)
{
    if (m_repeat || !m_isEnded)
    {
        m_isEnded = false;
        m_currentFrame = (SDL_GetTicks() / m_sequence.Speed) % m_sequence.Frames;
    }
    if (!m_repeat && m_currentFrame == (m_sequence.Frames - 1))
    {
        m_isEnded = true;
        m_currentFrame = (m_sequence.Frames - 1);
    }
}

void SequenceAnimation::setCurrentSequence(std::string sequenceId)
{
    if (m_sequences.count(sequenceId) > 0)
    {
        m_sequence = m_sequences[sequenceId];
    }
    else
    {
        std::cout << "Animation does not exists on sequence: " << sequenceId << std::endl;
    }
}

void SequenceAnimation::parse(std::string sourceFile)
{
    std::ifstream file_input(sourceFile.c_str(), std::ios::in);
    if (file_input.fail())
    {
        std::cout << "Can't load the file " << sourceFile << std::endl;
    }
    nlohmann::json jsonData{};
    file_input >> jsonData;

    for (auto &element : jsonData["sequences"])
    {
        auto sequenceId = element["id"];
        Sequence sequence = {
            .Speed = element["speed"],
            .Frames = element["frames"],
            .Width = element["width"],
            .Height = element["height"]};
        for (auto &texture : element["textures"])
        {
            sequence.TextureIds.push_back(texture["id"]);
        }
        m_sequences[sequenceId] = sequence;
    }
}