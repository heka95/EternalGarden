data = {}
data.raw = {}
local table_string = "table"

function data.extend(self, otherdata)
    if type(otherdata) ~= table_string or #otherdata == 0 then
        error("[LUA]    Invalid prototype array ")
    end

    for _, e in ipairs(otherdata) do

        if not e.type then
            error("[LUA]    Missing type in the following prototype definition")
        end

        if not e.name then
            error("[LUA]    Missing name in the following prototype definition")
        end

        local t = self.raw[e.type]
        if t == nil then
            t = {}
            self.raw[e.type] = t
        end
        t[e.name] = e
        print("[LUA]    NEW PROTOTYPE - category:" .. e.type .. " | name:" .. e.name)
    end
end