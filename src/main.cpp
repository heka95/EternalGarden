#define SOL_ALL_SAFETIES_ON 1

#include <iostream>
#include <sol.hpp>
#include "ConfigurationLoader.hpp"
#include "GameEngine.hpp"
#include "Layer.hpp"
#include "Timer.hpp"
#include "MapLoader.hpp"
#include "GameTypes.hpp"
#include "Components.hpp"
#include "Render.hpp"
#include "AnimatorSystem.hpp"
#include "InputSystem.hpp"
#include "PhysicSystem.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        std::string appPath{argv[0]}; 
        Garden::Configuration configuration = ConfigurationLoader::getConfiguration(appPath);
        GameEngine::getInstance().configureAndInit(configuration);
        auto manager = GameEngine::getInstance().getManager();

        sol::state lua;
        lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::debug, sol::lib::math, sol::lib::table);

        // Create binding to access manager without creation
        lua.new_usertype<Garden::Entity>("entity");
        lua.new_usertype<Garden::ComponentType>("componentType");
        lua.new_usertype<Garden::Component>("component");
        sol::usertype<Garden::Manager> manager_type = lua.new_usertype<Garden::Manager>("manager", sol::constructors<void>());
        manager_type["createEntity"] = &Garden::Manager::createEntity;
        manager_type["addComponent"] = &Garden::Manager::luaAddComponent;
        manager_type["registerEntity"] = &Garden::Manager::subscribeEntity;

        lua["currentManager"] = manager;

        // Define Components
        sol::usertype<Garden::Vector2D> vector2D_type = lua.new_usertype<Garden::Vector2D>("vector2D", sol::constructors<Garden::Vector2D(int, int)>());
        vector2D_type["zero"] = &Garden::Vector2D::zero;
        vector2D_type["x"] = &Garden::Vector2D::X;
        vector2D_type["y"] = &Garden::Vector2D::Y;

        lua["RenderFlip"] = lua.create_table_with(
            "none", SDL_RendererFlip::SDL_FLIP_NONE,
            "horizontal", SDL_RendererFlip::SDL_FLIP_HORIZONTAL,
            "vertical", SDL_RendererFlip::SDL_FLIP_VERTICAL);

        lua.new_usertype<Garden::Component>("Component");

        auto transform_type = lua.new_usertype<Garden::Components::Transform>("Transform",
                                                                              sol::constructors<Garden::Components::Transform(Garden::Vector2D)>(),
                                                                              sol::base_classes, sol::bases<Garden::Component>());
        transform_type["Position"] = &Garden::Components::Transform::Position;
        transform_type["type"] = &Garden::Components::Transform::getType;

        auto sprite_type = lua.new_usertype<Garden::Components::SpriteRenderer>("SpriteRenderer",
                                                                                sol::constructors<Garden::Components::SpriteRenderer(int, int, Garden::Vector2D, std::string, SDL_RendererFlip)>(),
                                                                                sol::base_classes, sol::bases<Garden::Component>());
        sprite_type["type"] = &Garden::Components::SpriteRenderer::getType;
        sprite_type["getFlip"] = &Garden::Components::SpriteRenderer::getFlip;

        auto anim_type = lua.new_usertype<Garden::Components::SpriteAnimation>("SpriteAnimation",
                                                                               sol::constructors<Garden::Components::SpriteAnimation(int, int, int, int, int, bool)>(),
                                                                               sol::base_classes, sol::bases<Garden::Component>());
        anim_type["type"] = &Garden::Components::SpriteAnimation::getType;

        auto command_type = lua.new_usertype<Garden::Components::PlayerCommand>("PlayerCommand",
                                                                                sol::constructors<Garden::Components::PlayerCommand()>(),
                                                                                sol::base_classes, sol::bases<Garden::Component>());
        command_type["type"] = &Garden::Components::PlayerCommand::getType;

        auto rigidBody_type = lua.new_usertype<Garden::Components::RigidBody>("RigidBody",
                                                                              sol::constructors<Garden::Components::RigidBody()>(),
                                                                              sol::base_classes, sol::bases<Garden::Component>());
        rigidBody_type["type"] = &Garden::Components::RigidBody::getType;
        rigidBody_type["mass"] = &Garden::Components::RigidBody::mass;
        rigidBody_type["gravity"] = &Garden::Components::RigidBody::gravity;
        rigidBody_type["force"] = &Garden::Components::RigidBody::force;
        rigidBody_type["friction"] = &Garden::Components::RigidBody::friction;
        rigidBody_type["position"] = &Garden::Components::RigidBody::position;
        rigidBody_type["velocity"] = &Garden::Components::RigidBody::velocity;
        rigidBody_type["acceleration"] = &Garden::Components::RigidBody::acceleration;

        sol::usertype<Garden::Components::TileSet> tileset_type = lua.new_usertype<Garden::Components::TileSet>("TileSet", sol::constructors<Garden::Components::TileSet()>());
        tileset_type["FirstId"] = &Garden::Components::TileSet::FirstId;
        tileset_type["LastId"] = &Garden::Components::TileSet::LastId;
        tileset_type["Rows"] = &Garden::Components::TileSet::Rows;
        tileset_type["Columns"] = &Garden::Components::TileSet::Columns;
        tileset_type["TileCount"] = &Garden::Components::TileSet::TileCount;
        tileset_type["TileSize"] = &Garden::Components::TileSet::TileSize;
        tileset_type["Name"] = &Garden::Components::TileSet::Name;
        tileset_type["Source"] = &Garden::Components::TileSet::Source;

        auto world_type = lua.new_usertype<Garden::Components::World>("World",
                                                                      sol::constructors<Garden::Components::World()>(),
                                                                      sol::base_classes, sol::bases<Garden::Component>());
        world_type["type"] = &Garden::Components::World::getType;
        world_type["addSets"] = &Garden::Components::World::luaAddSets;
        //world_type["addLayers"] = &Garden::Components::World::luaAddLayers;

        const std::string package_path = lua["package"]["path"];
        lua["package"]["path"] = package_path + (!package_path.empty() ? ";" : "") + "content/scripts/" + "?.lua";
        lua.script_file("content/scripts/main.lua");

        // test personnal ECS

        // test to create and draw a simple sprite
        // auto simpleSprite = manager.createEntity();
        // manager.addComponent(simpleSprite, new Garden::Components::Transform(Garden::Vector2D::zero()));
        // manager.addComponent(simpleSprite, new Garden::Components::SpriteRenderer(768, 58, Garden::Vector2D{1, 1}, "player", SDL_RendererFlip::SDL_FLIP_NONE));
        // manager.addComponent(simpleSprite, new Garden::Components::SpriteAnimation(64, 58, 1, 12, 100, true));
        // manager.addComponent(simpleSprite, new Garden::Components::PlayerCommand());
        // manager.subscribeEntity(simpleSprite);

        while (GameEngine::getInstance().isRunning())
        {
            manager->updateSystems(Timer::getInstance().getDeltaTime());
            Timer::getInstance().tick();
        }

        /*
        std::string appPath{argv[0]};
        Garden::Configuration configuration = ConfigurationLoader::getConfiguration(appPath);
        GameEngine::getInstance().configureAndInit(configuration);

        while (GameEngine::getInstance().isRunning())
        {
            GameEngine::getInstance().doEvents();
            GameEngine::getInstance().doUpdate();
            GameEngine::getInstance().doDraw();
            Timer::getInstance().tick();
        }

        GameEngine::getInstance().release();
*/
        GameEngine::getInstance().release();
        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return EXIT_FAILURE;
}