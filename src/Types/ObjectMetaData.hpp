#pragma once

#include "GameTypes.hpp"

namespace Garden
{
    class ObjectMetaData
    {
    public:
        ObjectMetaData(std::string textureId, Vector2I position, Size size, Flip flip = Flip::NONE)
        {
            TextureId = textureId;
            Position = position;
            Size = size;
            RenderFlip = flip;
        }

        std::string TextureId;
        Vector2I Position;
        Size Size;
        Flip RenderFlip;
    };
} // namespace Garden