#include "TransformerComponent.hpp"

TransformerComponent::TransformerComponent()
{
    m_name = "TransformerComponent";
    m_position.width = 0;
    m_position.height = 0;
}

TransformerComponent::~TransformerComponent()
{
}

Garden::Size TransformerComponent::getPosition() const
{
    return m_position;
}

void TransformerComponent::setPosition(int width, int height)
{
    m_position.width = width;
    m_position.height = height;
}