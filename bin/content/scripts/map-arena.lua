return {
  version = "1.2",
  luaversion = "5.1",
  tiledversion = "1.3.5",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 18,
  height = 7,
  tilewidth = 64,
  tileheight = 64,
  nextlayerid = 4,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    {
      name = "forest",
      firstgid = 1,
      tilewidth = 64,
      tileheight = 64,
      spacing = 0,
      margin = 0,
      columns = 8,
      image = "forest.png",
      imagewidth = 512,
      imageheight = 512,
      tileoffset = {
        x = 0,
        y = 0
      },
      grid = {
        orientation = "orthogonal",
        width = 64,
        height = 64
      },
      properties = {},
      terrains = {},
      tilecount = 64,
      tiles = {}
    }
  },
  layers = {
    {
      type = "tilelayer",
      id = 1,
      name = "main",
      x = 0,
      y = 0,
      width = 18,
      height = 7,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        9, 9, 9, 9, 9, 9, 9, 9, 52, 52, 9, 9, 9, 9, 9, 9, 9, 9,
        29, 29, 29, 29, 29, 29, 29, 29, 39, 39, 29, 29, 29, 29, 29, 29, 29, 29
      }
    },
    {
      type = "tilelayer",
      id = 2,
      name = "back",
      x = 0,
      y = 0,
      width = 18,
      height = 7,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 2, 0, 0, 3, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 27, 0, 0, 1, 2,
        0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 16, 16, 3, 0, 0,
        53, 0, 11, 19, 0, 53, 0, 19, 0, 0, 0, 11, 0, 0, 0, 11, 19, 19,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    }
  }
}
