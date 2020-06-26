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

        /*luaManager.registerComponent<Garden::Components::World>("World",
                                                                "addSets", &Garden::Components::World::luaAddSets,
                                                                //"addSets", &Garden::Components::World::luaAddLayers,
                                                                "type", &Garden::Components::World::getType);*/
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