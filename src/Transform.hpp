#pragma once

#include "Types/GameTypes.hpp"

class Transform
{
public:
    float X;
    float Y;
    Transform(float x = 0, float y = 0) : X(x), Y(y) {}

private:
    inline void TranslateX(float x) { X += x; }
    inline void TranslateY(float x) { X += x; }
    inline void Translate(Garden::Vector2F vector)
    {
        X += vector.X;
        Y += vector.Y;
    }
};

inline std::ostream &operator<<(std::ostream &os, const Transform &transform)
{
    os << "transform [x=" << transform.X << "][y=" << transform.Y << "]";
    return os;
}