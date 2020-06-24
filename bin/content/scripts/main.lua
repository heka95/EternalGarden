print("Lua start !")

require("data-loader")
require("player")
require("factory")

Factory:createPlayer(data.raw["entity"]["player"])

local map = require("map-arena")

local world = World.new()

-- Map tilesets
local tileSets = {}
for _, element in ipairs(map["tilesets"]) do
    local set = TileSet.new()
    set.FirstId = element["firstgid"]
    set.TileCount = element["tilecount"]
    set.LastId = set.TileCount + set.FirstId
    set.Columns = element["columns"]
    set.Rows = set.TileCount // set.Columns -- force int to divide result
    set.TileSize = element["tilewidth"]
    set.Name = element["name"]
    set.Source = element["image"]
    table.insert(tileSets, set)
end
world:addSets(tileSets)

-- Map Layers
local layers = {}
for _, element in ipairs(map["layers"]) do
    local layer = {}
    layer.name = element["name"]
    layer.data = element["data"]
    table.insert(layers, layer)
end
-- after move to avoid file too big
--world:addLayers(layers)




--local tile = TileSet.new()
--tile.FirstId = map[]