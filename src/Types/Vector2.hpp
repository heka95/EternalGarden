#pragma once

#include <iostream>

namespace Garden
{
    struct Vector2D
    {
        int x{0};
        int y{0};
    };

    inline std::ostream &operator<<(std::ostream &os, const Vector2D &vector)
    {
        os << "position [x=" << vector.x << "][y=" << vector.y << "]";
        return os;
    }
} // namespace Garden