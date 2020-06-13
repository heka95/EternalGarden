#include <iostream>
#include "ConfigurationLoader.hpp"
#include "Types/GameTypes.hpp"
#include "WorkingPlatform.hpp"
#include "LuaScript.hpp"
#include "Layer.hpp"
#include "Component/TransformerComponent.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        std::string appPath{argv[0]};
        Garden::Configuration configuration = ConfigurationLoader::getConfiguration(appPath);
        WorkingPlatform platform;
        platform.load(configuration);

        World world;
        Layer layer;
        Entity entity(1);
        TransformerComponent component;

        entity.addComponent(&component);
        layer.addEntity(&entity);
        world.addLayer(&layer);
        platform.setWorld(world);

        platform.run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return EXIT_FAILURE;
}

void testing()
{
    //std::string luaFile = configuration.luaDirectory + "hello.lua";
    //LuaScript script(luaFile.c_str());
    //script.execute();
    /*
        
        lua_State *lua = luaL_newstate();
        luaL_openlibs(lua);
        luaL_dofile(lua, luaFile.c_str());
        lua_getglobal(lua, "hello world");
        lua_call(lua, 0,0);
        lua_close(lua);
*/
}