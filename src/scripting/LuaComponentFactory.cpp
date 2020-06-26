#include "scripting/LuaComponentFactory.hpp"
#include "core/ECSTypes.hpp"
#include "components/Transformation.hpp"
#include "components/SpriteRenderer.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/RigidBody.hpp"

namespace Garden::Scripting
{
    void LuaComponentFactory::buildSpriteAnimation(Manager *manager, Garden::Entity entity, const sol::table &parentTable)
    {
        auto luaObject = hasElement(parentTable, "Animation");
        if (luaObject)
        {
            auto component = new Garden::Components::SpriteAnimation();
            component->width = luaObject["FrameWidth"];
            component->height = luaObject["FrameHeight"];
            component->rowCount = luaObject["SpriteRowIndex"];
            component->frameCount = luaObject["FrameCount"];
            component->speed = luaObject["Speed"];
            component->loop = luaObject["Loop"];
            manager->addComponent(entity, component);
        }
    }

    void LuaComponentFactory::buildRigidBody(Manager *manager, Garden::Entity entity, const sol::table &parentTable)
    {
        auto luaObject = hasElement(parentTable, "RigidBody");
        if (luaObject)
        {
            auto component = new Garden::Components::RigidBody();
            component->mass = luaObject["Mass"];
            component->gravity = luaObject["Gravity"];
            manager->addComponent(entity, component);
        }
    }

    void LuaComponentFactory::buildSpriteRenderer(Manager *manager, Garden::Entity entity, const sol::table &parentTable)
    {
        auto luaObject = hasElement(parentTable, "Sprite");
        if (luaObject)
        {
            auto component = new Garden::Components::SpriteRenderer();
            component->width = luaObject["Width"];
            component->height = luaObject["Height"];
            component->scale = Garden::Vector2D{luaObject["XScale"], luaObject["YScale"]};
            component->textureId = luaObject["TextureId"];
            component->flip = luaObject["DefaultFlip"];
            manager->addComponent(entity, component);
        }
    }

    void LuaComponentFactory::buildTransformation(Manager *manager, Garden::Entity entity, const sol::table &parentTable)
    {
        auto transform = hasElement(parentTable, "SpawnPosition");
        if (transform)
        {
            auto transformation = new Garden::Components::Transform();
            transformation->Position = Garden::Vector2D{transform["X"], transform["Y"]};
            manager->addComponent(entity, transformation);
        }
    }

    sol::table LuaComponentFactory::hasElement(const sol::table &object, const std::string &property)
    {
        sol::table element = object[property];
        if (element != sol::nil && element.valid())
        {
            return element;
        }
        return NULL;
    }

    Entity LuaComponentFactory::buildEntity(Manager *manager, const sol::table &parentTable)
    {
        auto newEntity = manager->createEntity();
        buildTransformation(manager, newEntity, parentTable);
        buildSpriteRenderer(manager, newEntity, parentTable);
        buildSpriteAnimation(manager, newEntity, parentTable);
        buildRigidBody(manager, newEntity, parentTable);
        manager->subscribeEntity(newEntity);
        return newEntity;
    }

} // namespace Garden::Scripting