#pragma once
#include "core/ECSTypes.hpp"

namespace Garden
{
    class BaseComponent
    {
    public:
        ComponentType getType() const { return m_type; }
        static const ComponentType type = INVALID_TYPE;

    protected:
        ComponentType m_type = INVALID_TYPE;
    };
} // namespace Garden