#include "scripting/LuaComponentFactory.hpp"
#include "core/ECSTypes.hpp"
#include "components/Transformation.hpp"
#include "components/SpriteRenderer.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/RigidBody.hpp"
#include "components/PlayerCommand.hpp"

namespace Garden::Scripting
{
    void LuaComponentFactory::buildSpriteAnimations(Manager *manager, Garden::Entity entity, const sol::table &parentTable)
    {
        auto luaObject = hasElement(parentTable, "Animations");
        if (luaObject)
        {
            auto component = new Garden::Components::SpriteAnimation();
            component->currentAnimation = luaObject["DefaultAnimation"];
            sol::table elements = luaObject["Elements"];

            if (elements != sol::nil && elements.valid())
            {
                for (const auto &key_value_pair : elements)
                {
                    sol::table element = key_value_pair.second;
                    auto animation = Garden::Components::AnimationElement{};
                    animation.type = element["Type"];
                    animation.name = element["Name"];
                    animation.source = element["Source"];
                    animation.textureId = element["TextureId"];
                    animation.width = element["FrameWidth"];
                    animation.height = element["FrameHeight"];
                    animation.rowCount = element["SpriteRowIndex"];
                    animation.frameCount = element["FrameCount"];
                    animation.speed = element["Speed"];
                    animation.loop = element["Loop"];
                    component->animations[animation.type] = animation;
                    manager->textureStore()->load(animation.textureId, animation.source);
                }
            }

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
            component->runSpeed = luaObject["RunSpeed"];
            component->jumpForce = luaObject["JumpForce"];
            component->jumpTime = luaObject["JumpTime"];
            component->attackTime = luaObject["AttackTime"];
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
            component->origin.X = component->width / 2;
            component->origin.Y = component->height / 2;
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

    void LuaComponentFactory::buildPlayerCommand(Manager *manager, Garden::Entity entity, const sol::table &parentTable)
    {
        auto commands = hasElement(parentTable, "Commands");
        if (commands)
        {
            bool isEnabled = commands["Enabled"];
            if (isEnabled)
            {
                auto playerCommand = new Garden::Components::PlayerCommand();
                manager->addComponent(entity, playerCommand);
            }
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
        buildSpriteAnimations(manager, newEntity, parentTable);
        buildRigidBody(manager, newEntity, parentTable);
        buildPlayerCommand(manager, newEntity, parentTable);
        manager->subscribeEntity(newEntity);
        return newEntity;
    }

} // namespace Garden::Scripting