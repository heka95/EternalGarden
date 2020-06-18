#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

constexpr std::size_t MaxComponents = 32;

using ComponentBitSet = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component *, MaxComponents>;

class Component
{
public:
    Entity *entity;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
    virtual ~Component() {}
};

class Entity
{
public:
    void update()
    {
        for (auto &c : components)
            c->update();
    }
    void draw()
    {
        for (auto &c : components)
            c->draw();
    }
    bool isActive() const { return m_isActive; }
    void destroy() { m_isActive = false; }

    template <typename T>
    bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T &addComponent(TArgs &&... mArgs)
    {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));
        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;
        c->init();
        return *c;
    }

    template <typename T>
    T &getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T *>(ptr);
    }

private:
    bool m_isActive = true;
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
};

class Manager
{
public:
    void update()
    {
        for (auto &e : entitites)
        {
            e->update();
        }
    }
    void draw()
    {
        for (auto &e : entitites)
        {
            e->draw();
        }
    }
    void refresh()
    {
        entitites.erase(std::remove_if(std::begin(entitites), std::end(entitites), [](const std::unique_ptr<Entity> &mEntity) { return !mEntity->isActive(); }), std::end(entitites));
    }

    Entity &addEntity()
    {
        Entity *entity = new Entity();
        std::unique_ptr<Entity> uPtr{entity};
        entitites.emplace_back(std::move(uPtr));
        return *entity;
    }

private:
    std::vector<std::unique_ptr<Entity>> entitites;
};