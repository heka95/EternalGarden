#include "scripting/LuaLevelLoader.hpp"
#include <tuple>
#include <string>
#include <vector>

namespace Garden::Scripting
{
    Garden::Core::LevelDefinition *LuaLevelLoader::loadLevel(Manager *manager, const sol::table &rootTable)
    {
        auto levelDefinition = new Garden::Core::LevelDefinition();
        levelDefinition->debugMode = rootTable["World"]["Debug"];
        levelDefinition->mapFile = rootTable["World"]["File"];

/* todo
        sol::table entitiesDefinitions = rootTable["Entities"];
        if (entitiesDefinitions != sol::nil && entitiesDefinitions.valid())
        {
            for (const auto &entityPair : entitiesDefinitions)
            {
                sol::table entityTable = entityPair.second;
                std::string type = entityTable["Type"];
                std::string name = entityTable["Name"];
                levelDefinition->entities.push_back(std::make_tuple(type, name));
            }
        }
        */
        return levelDefinition;
    }
} // namespace Garden::Scripting