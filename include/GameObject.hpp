#pragma once

#include <iostream>
#include "SDL.h"
#include "IGameObject.hpp"
#include "GameTypes.hpp"
#include "Transform.hpp"

class GameObject : public IGameObject
{
public:
    GameObject(Garden::ObjectMetaData *metaData)
    {
        m_transform = new Transform(metaData->Position.X, metaData->Position.Y);
        m_size = metaData->Size;
        m_textureId = metaData->TextureId;
        m_renderFlip = metaData->RenderFlip;
        auto originPositionX = metaData->Position.X + metaData->Size.width / 2;
        auto originPositionY = metaData->Position.Y + metaData->Size.height / 2;
        m_origin = new Garden::Vector2I{originPositionX, originPositionY};
    }

    virtual ~GameObject() = default;
    virtual void draw() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void release() = 0;
    inline Garden::Vector2I *getOrigin()
    {
        return m_origin;
    }

protected:
    Garden::Vector2I *m_origin;
    Transform *m_transform;
    Garden::Size m_size;
    std::string m_textureId;
    Garden::Flip m_renderFlip;
};