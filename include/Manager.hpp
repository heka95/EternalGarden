#pragma once
#include <cassert>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include "Types.hpp"
#include "Store.hpp"
#include "Event.hpp"
#include "System.hpp"

namespace Garden
{
    class Manager
    {
    public:
        Manager() : m_next(1) {}
        ~Manager();
        Entity createEntity();
        bool destroyEntity(Entity entity);
        std::set<Entity> getEntities() const;
        Store *getStore(ComponentType ct);
        bool createStoreFor(ComponentType ct);
        template <typename C>
        bool createStoreFor()
        {
            static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
            static_assert(C::type != INVALID_TYPE, "C must define its type");
            return createStoreFor(C::type);
        }
        Component *getComponent(Entity e, ComponentType ct);
        template <typename C>
        C *getComponent(Entity e)
        {
            static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
            static_assert(C::type != INVALID_TYPE, "C must define its type");
            return static_cast<C *>(getComponent(e, C::type));
        }
        bool luaAddComponent(Entity e, ComponentType ct, Component *c);
        bool addComponent(Entity e, ComponentType ct, Component *c);
        template <typename C>
        bool addComponent(Entity e, C *c)
        {
            static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
            static_assert(C::type != INVALID_TYPE, "C must define its type");
            return addComponent(e, C::type, c);
        }
        Component *extractComponent(Entity e, ComponentType ct);
        template <typename C>
        C *extractComponent(Entity e)
        {
            static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
            static_assert(C::type != INVALID_TYPE, "C must define its type");
            return static_cast<C *>(extractComponent(e, C::type));
        }
        int subscribeEntityToSystems(Entity e, std::set<ComponentType> components);
        int subscribeEntity(Entity e);
        bool addSystem(std::shared_ptr<System> sys);
        template <typename S, typename... Args>
        bool addSystem(Args &&... args)
        {
            static_assert(std::is_base_of<System, S>::value, "S must be a System");
            return addSystem(std::make_shared<S>(std::forward<Args>(args)...));
        }
        void initSystems();
        void updateSystems(float delta);
        void registerHandler(EventType type, EventHandler handler);
        template <typename E>
        void registerHandler(EventHandler handler)
        {
            static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
            static_assert(E::type != INVALID_TYPE, "E must define its type");
            registerHandler(E::type, handler);
        }
        template <typename E, typename R, typename T>
        void registerHandler(R T::*pm, T *obj)
        {
            static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
            static_assert(E::type != INVALID_TYPE, "E must define its type");
            registerHandler(E::type,
                            std::bind(pm, obj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        }
        void triggerEvent(Entity origin, EventType type, Event *event);
        template <typename E>
        void triggerEvent(Entity origin, E *event)
        {
            static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
            static_assert(E::type != INVALID_TYPE, "E must define its type");
            triggerEvent(origin, E::type, event);
        }

    private:
        Entity m_next;

        std::map<Entity, std::set<ComponentType>> m_entities;
        std::vector<std::shared_ptr<System>> m_systems;
        std::map<ComponentType, Store *> m_stores;
        std::map<EventType, std::vector<EventHandler>> m_handlers;
    };
} // namespace Garden