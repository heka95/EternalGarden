#define SOL_ALL_SAFETIES_ON 1

#include <iostream>
#include <memory>
#include "ConfigurationLoader.hpp"
#include "GameEngine.hpp"
#include "Timer.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        std::string appPath{argv[0]};
        Garden::Configuration configuration = ConfigurationLoader::getConfiguration(appPath);
        auto gameEngine = std::make_unique<GameEngine>();

        gameEngine->configureAndInit(configuration);
        auto manager = gameEngine->getManager();

        while (gameEngine->isRunning())
        {
            manager->updateSystems(Timer::getInstance().getDeltaTime());
            Timer::getInstance().tick();
        }

        gameEngine->release();
        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return EXIT_FAILURE;
}