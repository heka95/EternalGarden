#pragma once

#include <iostream>

namespace Garden
{
    class Vector2F
    {
    public:
        float X;
        float Y;
        Vector2F(float x = 0, float y = 0) : X(x), Y(y) {}
        inline Vector2F operator+(const Vector2F &addedVector) const
        {
            return Vector2F(X + addedVector.X, Y + addedVector.Y);
        }
        inline Vector2F operator-(const Vector2F &addedVector) const
        {
            return Vector2F(X - addedVector.X, Y - addedVector.Y);
        }
        inline Vector2F operator*(const float scalarElement) const
        {
            return Vector2F(X * scalarElement, Y * scalarElement);
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Vector2F &vector)
    {
        os << "position [x=" << vector.X << "][y=" << vector.Y << "]";
        return os;
    }
} // namespace Garden