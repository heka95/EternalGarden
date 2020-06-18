#include "Game.hpp"
#include "GameEngine.hpp"
#include "TextureManager.hpp"
#include "MapLoader.hpp"
#include "Camera.hpp"
#include "CollisionHandler.hpp"
#include "Player.hpp"
#include "Types/GameTypes.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "Menu.hpp"
#include "ObjectFactory.hpp"
#include "Ennemy.hpp"
#include <Lua/lua.hpp>

#include "ecs/ecs.hpp"
#include "ecs/Components.hpp"

Manager m_manager;
auto &newPlayer(m_manager.addEntity());

Game::Game()
{
}

bool Game::initialize()
{
    m_editMode = false;
    m_renderContext = GameEngine::getInstance().getRenderer();

    TextureManager::getInstance().parseTextures("level1.json");
    if (!MapLoader::getInstance().load("level1", "assets/maps/test_map.json"))
    {
        std::cout << "Failed to load map" << std::endl;
        return false;
    }

    m_world = MapLoader::getInstance().getWorld("level1");
    TileLayer *collisionLayer = (TileLayer *)m_world->getLayers().front();

    /* loading parallax */
    m_backgroundParralax.push_back(new ImageLayer("parallax-sky", 0, -320, 0.1));
    m_backgroundParralax.push_back(new ImageLayer("parallax-sun", 0, -320, 0.1));
    //m_backgroundParralax.push_back(new ImageLayer("parallax-city-shadow3", 0, -320, 0.2));
    //m_backgroundParralax.push_back(new ImageLayer("parallax-city-shadow2", 0, -320, 0.2));
    //m_backgroundParralax.push_back(new ImageLayer("parallax-city-shadow", 0, -320, 0.2));
    m_backgroundParralax.push_back(new ImageLayer("parallax-city", 0, -320, 0.3));
    m_backgroundParralax.push_back(new ImageLayer("parallax-grass", 0, -320, 0.4));
    m_backgroundParralax.push_back(new ImageLayer("parallax-ground", 0, -320, 0.5));
    /* ---------------- */

    auto tileSize = collisionLayer->getTileSize();
    auto width = collisionLayer->getWidth() * tileSize;
    auto height = collisionLayer->getHeight() * tileSize;

    Camera::getInstance().setSceneSize(width, height);
    CollisionHandler::getInstance().setCollisionMap(collisionLayer->getTileMap(), tileSize);

    auto playerMetadata = new Garden::ObjectMetaData("player", Garden::Vector2I{10, 100}, Garden::Size{64, 58});
    Player *player = new Player(playerMetadata);
    Camera::getInstance().setTarget(player->getOrigin());
    m_gameObjects.push_back(player);

    // load ennemi
    auto skullMetaData = new Garden::ObjectMetaData("skull", Garden::Vector2I{100, 100}, Garden::Size{557, 468});
    auto skull = ObjectFactory::getInstance().createNew("ENNEMY", skullMetaData);
    m_gameObjects.push_back(skull);

    //Gui::getInstance().initialize(); // no gui
    std::cout << "Game is initialized" << std::endl;

    newPlayer.addComponent<PositionComponent>();

    return true;
}

ImageLayer *ImageLayer_new(lua_State *L)
{
    std::string textureId = luaL_checkstring(L, 1);
    int x = luaL_checknumber(L, 2);
    int y = luaL_checknumber(L, 3);
    float scrollRatio = luaL_checknumber(L, 4);
    float scaleX = luaL_checknumber(L, 5);
    float scaleY = luaL_checknumber(L, 6);
    return new ImageLayer(textureId, x, y, scrollRatio, scaleX, scaleY);
}

void Game::doDraw()
{
    SDL_SetRenderDrawColor(m_renderContext, 0x2B, 0x84, 0xAB, 0xFF);
    SDL_RenderClear(m_renderContext);

    for (auto imageLayer : m_backgroundParralax)
    {
        imageLayer->render();
    }

    //TextureManager::getInstance().draw("background", Garden::Vector2I{0, -128}, Garden::Size{1280, 720}, Garden::Vector2F{1.0f, 1.0f}, Garden::Flip::NONE, 0.2f);
    m_world->render();
    for (auto &object : m_gameObjects)
    {
        object->draw();
    }

    auto cameraViewbox = Camera::getInstance().getViewBox();

    if (m_editMode)
    {
        //Gui::getInstance().doDraw(m_renderContext);
        // no gui
    }

    SDL_RenderCopy(m_renderContext, nullptr, &cameraViewbox, nullptr);
    SDL_RenderPresent(m_renderContext);
}

void Game::doUpdate()
{
    events();

    if (!m_editMode)
    {
        auto deltaTime = Timer::getInstance().getDeltaTime();
        for (auto object : m_gameObjects)
        {
            object->update(deltaTime);
        }
        Camera::getInstance().update();
        m_world->update();
    }
    newPlayer.update();
    std::cout << "[x=" << newPlayer.getComponent<PositionComponent>().x();
    std::cout << "|y=" << newPlayer.getComponent<PositionComponent>().x() << "]" << std::endl;
}

void Game::events()
{
    if (m_editMode && Input::getInstance().getKeyDown(SDL_SCANCODE_P))
    {
        GameEngine::getInstance().changeState(new Menu());
    }
    if (!m_editMode && Input::getInstance().getKeyDown(SDL_SCANCODE_ESCAPE))
    {
        m_editMode = true;
    }
    if (m_editMode && Input::getInstance().getKeyDown(SDL_SCANCODE_F5))
    {
        m_editMode = false;
    }
    //SDL_Delay(100);
}

bool Game::release()
{
    m_world->release();
    delete m_world;

    for (auto &object : m_gameObjects)
    {
        object->release();
        delete object;
    }

    m_gameObjects.clear();
    TextureManager::getInstance().release();
    return true;
}

void Game::openMenu()
{
    GameEngine::getInstance().changeState(new Menu());
}

void Game::pause()
{
}