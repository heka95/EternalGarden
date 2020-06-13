#pragma once

#include <string>
#include "../Types/GameTypes.hpp"
#include "BaseComponent.hpp"

class TransformerComponent : public BaseComponent
{
public:
    TransformerComponent();
    ~TransformerComponent();
    Garden::Size getPosition() const;
    void setPosition(int width, int height);

private:
    Garden::Size m_position;
};