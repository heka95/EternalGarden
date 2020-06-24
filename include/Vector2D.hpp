#pragma once
#include <iostream>

namespace Garden
{
    class Vector2D
    {
    public:
        float X;
        float Y;
        Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}
        inline Vector2D operator+(const Vector2D &addedVector) const
        {
            return Vector2D(X + addedVector.X, Y + addedVector.Y);
        }
        inline Vector2D operator-(const Vector2D &addedVector) const
        {
            return Vector2D(X - addedVector.X, Y - addedVector.Y);
        }
        inline Vector2D operator*(const float scalarElement) const
        {
            return Vector2D(X * scalarElement, Y * scalarElement);
        }
        inline friend Vector2D operator-=(Vector2D &v1, const Vector2D &v2)
        {
            v1.X -= v2.X;
            v1.Y -= v2.Y;
            return v1;
        }
        inline friend Vector2D operator+=(Vector2D &v1, const Vector2D &v2)
        {
            v1.X += v2.X;
            v1.Y += v2.Y;
            return v1;
        }
        static inline Vector2D zero() { return Vector2D{0, 0}; }
    };

    inline std::ostream &operator<<(std::ostream &os, const Vector2D &vector)
    {
        os << "position [x=" << vector.X << "][y=" << vector.Y << "]";
        return os;
    }
} // namespace Garden