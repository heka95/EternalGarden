#pragma once

#include "GameTypes.hpp"

#define G_MASS 1.0f
#define G_GRAVITY 9.8f

namespace Garden
{
    class RigidBody
    {
    public:
        RigidBody()
        {
            m_mass = G_MASS;
            m_gravity = G_GRAVITY;
        }

        inline void setMass(float mass) { m_mass = mass; }
        inline void setGravity(float gravity) { m_gravity = gravity; }

        inline void setForce(Vector2F force) { m_force = force; }
        inline void setForceX(float forceX) { m_force.X = forceX; }
        inline void setForceY(float forceY) { m_force.Y = forceY; }
        inline void setForceZero() { m_force = Vector2F{0, 0}; }

        inline void setFriction(Vector2F friction) { m_friction = friction; }
        inline void setFrictionZero() { m_friction = Vector2F{0, 0}; }

        inline float getMass() { return m_mass; }
        inline Vector2F getPosition() { return m_position; }
        inline Vector2F getVelocity() { return m_velocity; }
        inline Vector2F getAcceleration() { return m_acceleration; }

        void update(float deltaTime)
        {
            m_acceleration.X = (m_force.X + m_friction.X) / m_mass;
            m_acceleration.Y = m_gravity + m_force.Y / m_mass;
            m_velocity = m_acceleration * deltaTime;
            m_position = m_velocity * deltaTime;
        }

    private:
        float m_mass;
        float m_gravity;
        Vector2F m_force;
        Vector2F m_friction;
        Vector2F m_position;
        Vector2F m_velocity;
        Vector2F m_acceleration;
    };
} // namespace Garden