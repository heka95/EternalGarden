#pragma once
#include "SDL.h"
#include "GameState.hpp"
#include "OldWorld.hpp"
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
    inline OldWorld *getWorld() { return m_world; }
    static void openMenu();
    static void pause();

private:
    bool m_editMode;
    OldWorld *m_world;
    std::vector<GameObject *> m_gameObjects;
    std::vector<ImageLayer *> m_backgroundParralax;
};