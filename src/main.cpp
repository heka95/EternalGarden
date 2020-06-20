#define SOL_ALL_SAFETIES_ON 1

#include <iostream>
#include "ConfigurationLoader.hpp"
#include "Types/GameTypes.hpp"
#include "GameEngine.hpp"
#include "Layer.hpp"
#include "Timer.hpp"
#include "MapLoader.hpp"
#include "Types/GameTypes.hpp"
#include "core/Core.hpp"
#include "components/Components.hpp"
#include "systems/Render.hpp"
#include "systems/AnimatorSystem.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        std::string appPath{argv[0]};
        Garden::Configuration configuration = ConfigurationLoader::getConfiguration(appPath);
        GameEngine::getInstance().configureAndInit(configuration);

        // test personnal ECS
        Garden::Manager manager;

        manager.createStoreFor(Garden::Components::Transform::type);
        manager.createStoreFor(Garden::Components::SpriteRenderer::type);
        manager.createStoreFor(Garden::Components::SpriteAnimation::type);

        auto SDLRenderer = GameEngine::getInstance().getRenderer();
        manager.addSystem<Garden::Systems::Render>(&manager, SDLRenderer);
        manager.addSystem<Garden::Systems::AnimatorSystem>(&manager);
        manager.initSystems();

        // test to create and draw a simple sprite
        auto simpleSprite = manager.createEntity();
        manager.addComponent(simpleSprite, new Garden::Components::Transform(Garden::Vector2D::zero()));
        manager.addComponent(simpleSprite, new Garden::Components::SpriteRenderer(768, 58, Garden::Vector2D{1, 1}, "player", SDL_RendererFlip::SDL_FLIP_NONE));
        manager.addComponent(simpleSprite, new Garden::Components::SpriteAnimation(64, 58, 1, 12, 100, true));
        manager.subscribeEntityToSystems(simpleSprite);

        while (GameEngine::getInstance().isRunning())
        {
            GameEngine::getInstance().doEvents();
            manager.updateSystems(Timer::getInstance().getDeltaTime());
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
        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return EXIT_FAILURE;
}