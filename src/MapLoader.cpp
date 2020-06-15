#include "MapLoader.hpp"
#include <iostream>
#include <fstream>

std::unique_ptr<MapLoader> MapLoader::m_instance;
MapLoader &MapLoader::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new MapLoader());
    }
    return *m_instance.get();
}

bool MapLoader::parse(std::string id, std::string file)
{
    std::ifstream file_input(file.c_str(), std::ios::in);
    if (file_input.fail())
    {
        std::cerr << "Can't load the the map: " << file << std::endl;
        return false;
    }
    nlohmann::json jsonData{};
    file_input >> jsonData;

    std::vector<TileSet> tileSets;

    for (auto &element : jsonData["tilesets"])
    {
        tileSets.push_back(parseTileSet(element));
    }

    auto world = new World();
    for (auto &element : jsonData["layers"])
    {
        auto layer = parseTileLayer(element, tileSets, jsonData["tilewidth"], jsonData["height"], jsonData["width"]);
        world->m_layers.push_back(layer);
    }

    m_worlds[id] = world;
    return true;
}

TileSet MapLoader::parseTileSet(nlohmann::json &tileSetNode)
{
    auto tileSet = TileSet{};
    tileSet.Columns = tileSetNode["columns"];
    tileSet.FirstId = tileSetNode["firstgid"];
    tileSet.Name = tileSetNode["name"];
    tileSet.Source = tileSetNode["image"];
    tileSet.TileCount = tileSetNode["tilecount"];
    tileSet.Tilesize = tileSetNode["tilewidth"];
    tileSet.LastId = (tileSet.FirstId + tileSet.TileCount) - 1;
    tileSet.Rows = tileSet.TileCount / tileSet.Columns;
    return tileSet;
}

TileLayer *MapLoader::parseTileLayer(nlohmann::json &tileLayer, std::vector<TileSet> tileSets, int tileSize, int rows, int columns)
{
    std::vector<int> data = tileLayer["data"];

    std::vector<std::vector<int>> tilemap(rows, std::vector<int>(columns, 0));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int value = data[(i * columns) + j];
            tilemap[i][j] = value;
        }
    }

    return (new TileLayer(tileSize, rows, columns, tilemap, tileSets, tileLayer["name"]));
}

bool MapLoader::load(std::string id, std::string file)
{
    std::cout << "Loading map [" << id << "] from " << file << std::endl;
    return parse(id, file);
}

void MapLoader::release()
{
    for (auto &world : m_worlds)
    {
        world.second = nullptr;
    }
    m_worlds.clear();
}

World *MapLoader::getWorld(std::string id)
{
    return m_worlds[id];
}