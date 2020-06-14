#pragma once

#include <map>
#include <string>
#include "World.hpp"
#include "TileLayer.hpp"
#include <json.hpp>

class MapLoader
{
public:
    virtual ~MapLoader() = default;
    static MapLoader &getInstance();
    bool load(std::string id, std::string file);
    void release();
    World *getWorld(std::string id);

private:
    MapLoader() = default;
    MapLoader(const MapLoader &object) = delete;
    MapLoader &operator=(const MapLoader &object) = delete;
    static std::unique_ptr<MapLoader> m_instance;
    std::map<std::string, World *> m_worlds;
    bool parse(std::string id, std::string file);
    TileSet parseTileSet(nlohmann::json &tileSetNode);
    TileLayer *parseTileLayer(nlohmann::json &tileLayer, std::vector<TileSet> tileSets, int tileSize, int rows, int columns);
};