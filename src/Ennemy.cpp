#include "Ennemy.hpp"
#include "CollisionHandler.hpp"
#include "Camera.hpp"

Ennemy::Ennemy(Garden::ObjectMetaData *metaData) : Character(metaData)
{
    m_rigidBody = new Garden::RigidBody();
    m_rigidBody->setGravity(3.5f);
    m_collider = new Collider();
    m_collider->SetBuffer(-20,0,0,0);
    m_animation = new SequenceAnimation(false);
    m_animation->parse("assets/ennemy.json");
    m_animation->setCurrentSequence("skull-appear");
}

void Ennemy::draw()
{
    m_animation->drawFrame(Garden::Vector2I{(int)m_transform->X, (int)m_transform->Y}, Garden::Vector2F{0.2f, 0.2f}, m_renderFlip);
    m_collider->draw();
}

void Ennemy::update(float deltaTime)
{
    m_rigidBody->update(deltaTime);
    m_lastSafePosition.X = m_transform->X;
    m_transform->X += m_rigidBody->getPosition().X;
    m_collider->set(m_transform->X, m_transform->Y, 75, 75);

    if (CollisionHandler::getInstance().worldCollision(m_collider->get()))
    {
        m_transform->X = m_lastSafePosition.X;
    }

    m_rigidBody->update(deltaTime);
    m_lastSafePosition.Y = m_transform->Y;
    m_transform->Y += m_rigidBody->getPosition().Y;
    m_collider->set(m_transform->X, m_transform->Y, 75, 75);

    if (CollisionHandler::getInstance().worldCollision(m_collider->get()))
    {
        m_transform->Y = m_lastSafePosition.Y;
    }
    m_animation->update(deltaTime);

    if (m_animation->isEndend())
    {
        m_animation->setRepeat(true);
        m_animation->setCurrentSequence("skull-idle");
    }
}

void Ennemy::release()
{

}