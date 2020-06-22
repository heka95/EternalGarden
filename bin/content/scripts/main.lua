print("Lua start !")
require("data-loader")
require("player")
require("factory")

Factory:createPlayer(data.raw["entity"]["player"])