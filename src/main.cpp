#define SOL_ALL_SAFETIES_ON 1

#include <iostream>
#include "ConfigurationLoader.hpp"
#include "GameEngine.hpp"
#include "Layer.hpp"
#include "Timer.hpp"
#include "MapLoader.hpp"
#include "GameTypes.hpp"
#include "systems/Render.hpp"
#include "systems/AnimatorSystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/PhysicSystem.hpp"
#include "core/LuaManager.hpp"
#include "components/Transformation.hpp"
#include "components/World.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        std::string appPath{argv[0]};
        Garden::Configuration configuration = ConfigurationLoader::getConfiguration(appPath);
        GameEngine::getInstance().configureAndInit(configuration);
        auto manager = GameEngine::getInstance().getManager();

        auto luaManager = Garden::Core::LuaManager(manager);
        luaManager.registerComponent<Garden::Components::Transform>("Transform",
                                                                    "Position", &Garden::Components::Transform::Position,
                                                                    "type", &Garden::Components::Transform::getType);
        luaManager.registerComponent<Garden::Components::SpriteRenderer>("SpriteRenderer",
                                                                         "width", &Garden::Components::SpriteRenderer::width,
                                                                         "height", &Garden::Components::SpriteRenderer::height,
                                                                         "drawWidth", &Garden::Components::SpriteRenderer::drawWidth,
                                                                         "drawHeight", &Garden::Components::SpriteRenderer::drawHeight,
                                                                         "drawOffset", &Garden::Components::SpriteRenderer::drawOffset,
                                                                         "rotation", &Garden::Components::SpriteRenderer::rotation,
                                                                         "scale", &Garden::Components::SpriteRenderer::scale,
                                                                         "origin", &Garden::Components::SpriteRenderer::origin,
                                                                         "textureId", &Garden::Components::SpriteRenderer::textureId,
                                                                         "flip", &Garden::Components::SpriteRenderer::flip,
                                                                         "type", &Garden::Components::SpriteRenderer::getType);
        luaManager.registerComponent<Garden::Components::SpriteAnimation>("SpriteAnimation",
                                                                          "width", &Garden::Components::SpriteAnimation::width,
                                                                          "height", &Garden::Components::SpriteAnimation::height,
                                                                          "rowCount", &Garden::Components::SpriteAnimation::rowCount,
                                                                          "frameCount", &Garden::Components::SpriteAnimation::frameCount,
                                                                          "speed", &Garden::Components::SpriteAnimation::speed,
                                                                          "loop", &Garden::Components::SpriteAnimation::loop,
                                                                          "type", &Garden::Components::SpriteAnimation::getType);
        luaManager.registerComponent<Garden::Components::PlayerCommand>("PlayerCommand",
                                                                        "type", &Garden::Components::PlayerCommand::getType);
        luaManager.registerComponent<Garden::Components::RigidBody>("RigidBody",
                                                                    "mass", &Garden::Components::RigidBody::mass,
                                                                    "gravity", &Garden::Components::RigidBody::gravity,
                                                                    "force", &Garden::Components::RigidBody::force,
                                                                    "friction", &Garden::Components::RigidBody::friction,
                                                                    "position", &Garden::Components::RigidBody::position,
                                                                    "velocity", &Garden::Components::RigidBody::velocity,
                                                                    "acceleration", &Garden::Components::RigidBody::acceleration,
                                                                    "type", &Garden::Components::RigidBody::getType);
        luaManager.registerObject<Garden::Components::TileSet>("TileSet",
                                                               "FirstId", &Garden::Components::TileSet::FirstId,
                                                               "LastId", &Garden::Components::TileSet::LastId,
                                                               "Rows", &Garden::Components::TileSet::Rows,
                                                               "Columns", &Garden::Components::TileSet::Columns,
                                                               "TileCount", &Garden::Components::TileSet::TileCount,
                                                               "TileSize", &Garden::Components::TileSet::TileSize,
                                                               "Name", &Garden::Components::TileSet::Name,
                                                               "Source", &Garden::Components::TileSet::Source);

        luaManager.registerComponent<Garden::Components::World>("World",
                                                                "addSets", &Garden::Components::World::luaAddSets,
                                                                //"addSets", &Garden::Components::World::luaAddLayers,
                                                                "type", &Garden::Components::World::getType);
        luaManager.executeScript("content/scripts/main.lua");

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