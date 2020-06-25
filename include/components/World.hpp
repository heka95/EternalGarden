#pragma once

#include <vector>
#include <map>
//#include "sol.hpp"
#include "core/ECSTypes.hpp"
#include "BaseComponent.hpp"

namespace Garden::Components
{
    class TileSet
    {
    public:
        TileSet() = default;
        int FirstId = 0;
        int LastId = 0;
        int Rows = 0;
        int Columns = 0;
        int TileCount = 0;
        int TileSize = 0;
        std::string Name = "";
        std::string Source = "";
    };

    class World : public Garden::BaseComponent
    {
    public:
        static const ComponentType type = Types::WorldType;
        World()
        {
            m_type = Types::WorldType;
        }

        int rows = 0;
        int columns = 0;
        int tileWidth = 0;
        int tileHeight = 0;
        std::vector<TileSet> tileSets;
        std::map<std::string, std::vector<int>> tileMapLayers;
        std::string physicLayer = "";

        void luaAddSets(sol::as_table_t<std::vector<TileSet>> src)
        {
            const auto &listmap = src.value();
            tileSets.insert(tileSets.end(), listmap.begin(), listmap.end());
        }
/*
        //void luaAddLayers(sol::as_table_t<std::map<std::string, sol::as_table_t<std::vector<int>>>> src)
        void luaAddLayers(std::string key, sol::as_table_t<std::vector<int>> value)
        {
            const auto &data = value.value();
            tileMapLayers.emplace(key, data);
            
            //const auto &listmap = src.value();
            //for (const auto &kvp : listmap)
            //{
            //    const auto& data = kvp.second.value();
            //    tileMapLayers.emplace(kvp.first, data);
            //}
            
        }
        */
    };
} // namespace Garden::Components