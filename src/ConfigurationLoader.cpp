#include <fstream>
#include <iostream>
#include "ConfigurationLoader.hpp"
#include <sol.hpp>

ConfigurationLoader::ConfigurationLoader()
{
}

Garden::Configuration ConfigurationLoader::getConfiguration(std::string workingDirectory)
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.script_file("scripts/Configuration.lua");
    Garden::Configuration configuration;
    configuration.windowSize.width = lua["config"]["resolution"]["width"].get_or(800);
    configuration.windowSize.height = lua["config"]["resolution"]["height"].get_or(600);
    configuration.luaDirectory = directoryNameof(workingDirectory) + "\\scripts\\";
    configuration.executionPath = directoryNameof(workingDirectory);
    lua.collect_garbage();
    return configuration;
}

std::string ConfigurationLoader::directoryNameof(const std::string &fileName)
{
    size_t position = fileName.find_last_of("\\/");
    return (std::string::npos == position) ? "" : fileName.substr(0, position);
}