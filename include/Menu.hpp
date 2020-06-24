#pragma once

#include "SDL.h"
#include "GameState.hpp"

class Menu : public GameState
{
    public:
    virtual bool initialize();
    virtual bool release();
    virtual void doUpdate();
    virtual void doDraw();

    private:
    static void startGame();
    static void Settings();
    static void Editor();
    static void Quit();
};