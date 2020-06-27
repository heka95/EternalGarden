#include "scripting/LuaWorldLoader.hpp"
#include <array>

namespace Garden::Scripting
{
    Garden::Components::World *LuaWorldLoader::loadWorld(Manager *manager, const sol::table &rootTable)
    {
        auto world = new Garden::Components::World();
        world->columns = rootTable["width"];
        world->rows = rootTable["height"];
        world->tileHeight = rootTable["tileheight"];
        world->tileWidth = rootTable["tilewidth"];

        // Generate tilesets
        sol::table tilesets = rootTable["tilesets"];
        if (tilesets != sol::nil && tilesets.valid())
        {
            for (const auto &key_value_pair : tilesets)
            {
                sol::table tileSetNode = key_value_pair.second;
                auto tileSet = Garden::Components::TileSet{};
                tileSet.Columns = tileSetNode["columns"];
                tileSet.FirstId = tileSetNode["firstgid"];
                tileSet.Name = tileSetNode["name"];
                tileSet.Source = tileSetNode["image"];
                tileSet.TileCount = tileSetNode["tilecount"];
                tileSet.TileSize = tileSetNode["tilewidth"];
                tileSet.LastId = (tileSet.FirstId + tileSet.TileCount) - 1;
                if (tileSet.Columns > 0)
                {
                    tileSet.Rows = tileSet.TileCount / tileSet.Columns;
                }
                world->tileSets.push_back(tileSet);
            }
        }

        // Generate layers
        sol::table layers = rootTable["layers"];
        if (layers != sol::nil && layers.valid())
        {
            for (const auto &key_value_pair : layers)
            {
                sol::table layerNode = key_value_pair.second;
                std::string name = layerNode["name"];
                sol::as_table_t<std::vector<int>> containerData = layerNode["data"];
                auto data = containerData.value();
                world->tileMapLayers[name] = data;
                auto properties = layerNode["properties"];
                if (properties != sol::nil && properties.valid())
                {
                    auto collider = properties["collider"];
                    if (collider != sol::nil && collider.valid())
                    {
                        world->physicLayer = name;
                    }
                }
            }
        }

        return world;
    }

} // namespace Garden::Scripting