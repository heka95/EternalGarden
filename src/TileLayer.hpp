#pragma once

#include <string>
#include <vector>
#include "Layer.hpp"

struct TileSet
{
    int FirstId;
    int LastId;
    int Rows;
    int Columns;
    int TileCount;
    int Tilesize;
    std::string Name;
    std::string Source;
};

class TileLayer : public Layer
{
public:
    TileLayer(int tileSize, int rows, int columns, std::vector<std::vector<int>> tileMap, std::vector<TileSet> tileSets, std::string name);
    virtual void render();
    virtual void update();
    std::vector<std::vector<int>> getTileMap();

private:
    int m_tileSize;
    int m_rows;
    int m_columns;
    std::string m_name;
    std::vector<std::vector<int>> m_tileMap;
    std::vector<TileSet> m_tileSets;
    const int NO_GRAPHIC_TILE = 0;
    int getTileSetIndexFromTileId(int tileId);
};