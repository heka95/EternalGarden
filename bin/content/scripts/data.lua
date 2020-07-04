print("[LUA]    Lua start !")

-- Load templates
print("[LUA]    Load Libraries")
require("utils/data-loader")
require("templates/player")
require("templates/skull")

print("[LUA]    Generate C++ Accessor")
function getobject(category, name)
    if (data.raw[category] == nil) then return nil end
    if (data.raw[category][name] == nil) then return nil end
    return data.raw[category][name]
end

print("[LUA]    Loading complete!")
