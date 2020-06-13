#include <fstream>
#include <iostream>
#include "ConfigurationLoader.hpp"
#include "json.hpp"

ConfigurationLoader::ConfigurationLoader()
{ }

Garden::Configuration ConfigurationLoader::getConfiguration(std::string workingDirectory)
{
    auto configFilePath{directoryNameof(workingDirectory) + "\\game-config.json"};
    std::cout << "Loading configuration from " << configFilePath << std::endl;

    std::ifstream file_input(configFilePath.c_str(), std::ios::in);
    if (file_input.fail())
    {
        throw "Can't load the configuration file";
    }
    nlohmann::json jsonData{};
    file_input >> jsonData;

    Garden::Configuration configuration;
    configuration.windowSize.width = jsonData["window"]["width"];
    configuration.windowSize.height = jsonData["window"]["height"];
    configuration.luaDirectory = directoryNameof(workingDirectory) + "\\scripts\\";
    configuration.executionPath = directoryNameof(workingDirectory);

    return configuration;
}

std::string ConfigurationLoader::directoryNameof(const std::string &fileName)
{
    size_t position = fileName.find_last_of("\\/");
    return (std::string::npos == position) ? "" : fileName.substr(0, position);
}