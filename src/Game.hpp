#pragma once
#include <SDL2/SDL.h>
#include "GameState.hpp"
#include "World.hpp"
#include "GameObject.hpp"
#include "ImageLayer.hpp"

class Game : public GameState
{
public:
    Game();
    void events();
    virtual bool initialize();
    virtual bool release();
    virtual void doUpdate();
    virtual void doDraw();
    inline World *getWorld() { return m_world; }
    static void openMenu();
    static void pause();

private:
    bool m_editMode;
    World *m_world;
    std::vector<GameObject *> m_gameObjects;
    std::vector<ImageLayer *> m_backgroundParralax;
};