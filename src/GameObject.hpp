#pragma once

#include <SDL2/SDL.h>
#include "IGameObject.hpp"
#include "Types/GameTypes.hpp"
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
    }

    virtual ~GameObject() = default;
    virtual void draw() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void release() = 0;

protected:
    Transform *m_transform;
    Garden::Size m_size;
    std::string m_textureId;
    Garden::Flip m_renderFlip;
};