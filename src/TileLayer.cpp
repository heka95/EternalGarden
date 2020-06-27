#include "TileLayer.hpp"
#include "OldTextureManager.hpp"

TileLayer::TileLayer(int tileSize, int rows, int columns, std::vector<std::vector<int>> tileMap, std::vector<TileSet> tileSets, std::string name)
    : m_tileSize(tileSize), m_rows(rows), m_columns(columns), m_tileMap(tileMap), m_tileSets(tileSets)
{
    m_name = name;
    for (unsigned int i = 0; i < m_tileSets.size(); i++)
    {
        OldTextureManager::getInstance().load(m_tileSets[i].Name, "assets/maps/" + m_tileSets[i].Source);
    }
}

std::vector<std::vector<int>> TileLayer::getTileMap()
{
    return m_tileMap;
}

void TileLayer::render()
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_columns; j++)
        {
            int tileId = m_tileMap[i][j];
            if (tileId == NO_GRAPHIC_TILE)
            {
                continue;
            }
            int tileSetIndex = getTileSetIndexFromTileId(tileId);
            auto tileSet = m_tileSets[tileSetIndex];
            auto tileRow = tileId / tileSet.Columns;
            auto tileColumn = tileId - tileRow * tileSet.Columns - 1;

            if (tileId % tileSet.Columns == 0)
            {
                tileRow--;
                tileColumn = tileSet.Columns - 1;
            }

            OldTextureManager::getInstance().drawTile(tileSet.Name, tileSet.Tilesize, Garden::Vector2I{j * tileSet.Tilesize, i * tileSet.Tilesize}, tileRow, tileColumn);
        }
    }
}

int TileLayer::getTileSetIndexFromTileId(int tileId)
{
    int tileSetIndex = 0;
    if (m_tileSets.size() > 1)
    {
        for (unsigned int k = 1; k < m_tileSets.size(); k++)
        {
            if (tileId > m_tileSets[k].FirstId && tileId < m_tileSets[k].LastId)
            {
                tileId = tileId + m_tileSets[k].TileCount - m_tileSets[k].LastId;
                tileSetIndex = k;
                break;
            }
        }
    }
    return tileSetIndex;
}

void TileLayer::update()
{
}