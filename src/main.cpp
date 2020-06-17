#define SOL_ALL_SAFETIES_ON 1

#include <iostream>
#include "ConfigurationLoader.hpp"
#include "Types/GameTypes.hpp"
#include "GameEngine.hpp"
#include "Layer.hpp"
#include "Timer.hpp"
#include "MapLoader.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
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

        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return EXIT_FAILURE;
}