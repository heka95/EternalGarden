#include "scripting/LuaWorldLoader.hpp"
#include <array>
#include "Utilities.hpp"
#include "SDL.h"

namespace Garden::Scripting
{
    Garden::Components::World *LuaWorldLoader::loadWorld(Manager *manager, const sol::table &rootTable, const std::string &mapFolderName)
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

                sol::table tiles = tileSetNode["tiles"];
                if (tiles != sol::nil && tiles.valid() && !tiles.empty())
                {
                    for (const auto &tilePair : tiles)
                    {
                        sol::table singleTile = tilePair.second;
                        auto tileSet = Garden::Components::TileSet{};
                        tileSet.Columns = 1;
                        int firstGuid = tileSetNode["firstgid"];
                        int imageGuid = singleTile["id"];
                        tileSet.FirstId = firstGuid + imageGuid;
                        std::string name = tileSetNode["name"];
                        std::string nameGid = singleTile["id"];
                        tileSet.Name = name + "#" + nameGid;
                        tileSet.Source = singleTile["image"];
                        tileSet.TileCount = 1;
                        tileSet.TileSize = 1;
                        tileSet.LastId = tileSet.FirstId;
                        if (!tileSet.Name.empty() && !tileSet.Source.empty())
                        {
                            auto filePath = mapFolderName + "/" + tileSet.Source;
                            manager->textureStore()->load(tileSet.Name, filePath);
                        }
                        world->tileSets.push_back(tileSet);
                    }
                }
                else
                {
                    auto tileSet = extractTileSet(manager, tileSetNode, mapFolderName);
                    world->tileSets.push_back(tileSet);
                }
            }
        }

        // Generate layers
        sol::table layers = rootTable["layers"];
        if (layers != sol::nil && layers.valid())
        {
            for (const auto &key_value_pair : layers)
            {
                sol::table layerNode = key_value_pair.second;
                std::string type = layerNode["type"];
                if (type == "tilelayer")
                {
                    loadLayer(manager, layerNode, world);
                }
                if (type == "group")
                {
                    sol::table subLayers = layerNode["layers"];
                    if (subLayers != sol::nil && subLayers.valid())
                    {
                        for (const auto &sub_key_value_pair : subLayers)
                        {
                            sol::table sublayerNode = sub_key_value_pair.second;
                            loadLayer(manager, sublayerNode, world);
                        }
                    }
                }
                if (type == "objectgroup")
                {
                    sol::table objects = layerNode["objects"];
                    if (objects != sol::nil && objects.valid())
                    {
                        for (const auto &entityPair : objects)
                        {
                            sol::table entityTable = entityPair.second;
                            Garden::Core::WorldObjectDefinition definition{};
                            definition.type = entityTable["type"];
                            definition.name = entityTable["name"];
                            definition.spawnX = entityTable["x"].get_or(0);
                            definition.spawnY = entityTable["y"].get_or(0);
                            definition.width = entityTable["width"].get_or(0);
                            definition.height = entityTable["height"].get_or(0);
                            definition.rotation = entityTable["rotation"].get_or(0);
                            if (definition.type == "background")
                            {
                                auto tileSetIndex = world->getTileSetIndexFromTileId(entityTable["gid"].get_or(0));
                                auto tileSet = world->tileSets.at(tileSetIndex);
                                definition.name = tileSet.Name;
                            }
                            else
                            {
                                auto properties = entityTable["properties"];
                                if (properties != sol::nil && properties.valid())
                                {
                                    auto cameraTarget = properties["cameraTarget"];
                                    if (cameraTarget != sol::nil && cameraTarget.valid())
                                    {
                                        definition.isCameraTarget = properties["cameraTarget"];
                                    }
                                }
                            }
                            world->entities.push_back(definition);
                        }
                    }
                }
            }
        }

        return world;
    }

    Garden::Components::TileSet LuaWorldLoader::extractTileSet(Manager *manager, const sol::table &tileSetNode, const std::string &mapFolderName)
    {
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
        if (!tileSet.Name.empty() && !tileSet.Source.empty())
        {
            auto filePath = mapFolderName + "/" + tileSet.Source;
            manager->textureStore()->load(tileSet.Name, filePath);
        }
        return tileSet;
    }

    void LuaWorldLoader::loadLayer(Manager *manager, const sol::table &layerNode, Garden::Components::World *world)
    {
        unsigned int FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
        unsigned int FLIPPED_VERTICALLY_FLAG = 0x40000000;
        unsigned int FLIPPED_DIAGONALLY_FLAG = 0x20000000;

        std::string name = layerNode["name"];
        std::cout << "add layer: " << name << std::endl;

        sol::as_table_t<std::vector<unsigned int>> containerData = layerNode["data"];
        auto data = containerData.value();

        auto layer = new Garden::Components::Layer{};
        layer->name = name;
        for (auto &tile_index : data)
        {
            bool flipped_horizontally = (tile_index & FLIPPED_HORIZONTALLY_FLAG);
            bool flipped_vertically = (tile_index & FLIPPED_VERTICALLY_FLAG);
            //bool flipped_diagonally = (tile_index & FLIPPED_DIAGONALLY_FLAG);
            tile_index &= ~(FLIPPED_HORIZONTALLY_FLAG |
                            FLIPPED_VERTICALLY_FLAG |
                            FLIPPED_DIAGONALLY_FLAG);
            auto tile = new Garden::Components::Tile{};
            tile->TileId = tile_index;
            tile->flip = SDL_RendererFlip::SDL_FLIP_NONE;
            if (flipped_horizontally)
                tile->flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
            if (flipped_vertically)
                tile->flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
            if (flipped_horizontally & flipped_vertically)
            {
                auto flip = (SDL_RendererFlip::SDL_FLIP_HORIZONTAL | SDL_RendererFlip::SDL_FLIP_VERTICAL);
                tile->flip = (SDL_RendererFlip)flip;
            }
            layer->tiles.push_back(tile);
        }

        auto properties = layerNode["properties"];
        if (properties != sol::nil && properties.valid())
        {
            auto collider = properties["collider"];
            if (collider != sol::nil && collider.valid())
            {
                // Current tile index = length - 1
                world->physicLayer = world->tileMapLayers.size();
                layer->isCollider = true;
            }
        }

        world->tileMapLayers.push_back(layer);
    }

} // namespace Garden::Scripting