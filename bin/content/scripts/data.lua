print("[LUA]    Lua start !")

-- Load templates
print("[LUA]    Load Libraries")
require("utils/data-loader")
require("templates/player")
require("templates/skull")

print("[LUA]    Generate C++ Accessor")
function getobject(category, name)
    local object = data.raw[category][name]
    return object
end

print("[LUA]    Loading complete!")