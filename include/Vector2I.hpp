#pragma once

#include <iostream>

namespace Garden
{
    class Vector2I
    {
    public:
        int X;
        int Y;
        Vector2I(int x = 0, int y = 0) : X(x), Y(y) {}
        inline Vector2I operator+(const Vector2I &addedVector) const
        {
            return Vector2I(X + addedVector.X, Y + addedVector.Y);
        }
        inline Vector2I operator-(const Vector2I &addedVector) const
        {
            return Vector2I(X - addedVector.X, Y - addedVector.Y);
        }
        inline Vector2I operator*(const int scalarElement) const
        {
            return Vector2I(X * scalarElement, Y * scalarElement);
        }
        inline Vector2I operator*(const float scalarElement) const
        {
            return Vector2I(X * scalarElement, Y * scalarElement);
        }
        inline friend Vector2I operator-=(Vector2I &v1, const Vector2I &v2)
        {
            v1.X -= v2.X;
            v1.Y -= v2.Y;
            return v1;
        }
        inline friend Vector2I operator+=(Vector2I &v1, const Vector2I &v2)
        {
            v1.X += v2.X;
            v1.Y += v2.Y;
            return v1;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Vector2I &vector)
    {
        os << "position [x=" << vector.X << "][y=" << vector.Y << "]";
        return os;
    }
} // namespace Garden