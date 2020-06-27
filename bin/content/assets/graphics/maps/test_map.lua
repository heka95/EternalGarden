return {
  version = "1.4",
  luaversion = "5.1",
  tiledversion = "1.4.1",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 18,
  height = 7,
  tilewidth = 64,
  tileheight = 64,
  nextlayerid = 5,
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
      image = "../../../../assets/maps/forest.png",
      imagewidth = 512,
      imageheight = 512,
      objectalignment = "unspecified",
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
    },
    {
      name = "collider_64",
      firstgid = 65,
      tilewidth = 64,
      tileheight = 64,
      spacing = 0,
      margin = 0,
      columns = 0,
      objectalignment = "unspecified",
      tileoffset = {
        x = 0,
        y = 0
      },
      grid = {
        orientation = "orthogonal",
        width = 1,
        height = 1
      },
      properties = {},
      terrains = {},
      tilecount = 1,
      tiles = {
        {
          id = 0,
          image = "C:/Users/Tom/Desktop/draw/collider_64.png",
          width = 64,
          height = 64
        }
      }
    }
  },
  layers = {
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 18,
      height = 7,
      id = 1,
      name = "main",
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
      x = 0,
      y = 0,
      width = 18,
      height = 7,
      id = 2,
      name = "back",
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
    },
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 18,
      height = 7,
      id = 4,
      name = "collider",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {
        ["collider"] = true
      },
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 65, 65, 65, 0, 0, 0, 0, 0, 0, 65, 65, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        65, 65, 65, 65, 65, 65, 65, 65, 0, 0, 65, 65, 65, 65, 65, 65, 65, 65,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    }
  }
}
