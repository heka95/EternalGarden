#if !defined(__CONFIGURATION_LOADER__)
#define __CONFIGURATION_LOADER__

#include <string>
#include "Configuration.hpp"

class ConfigurationLoader
{
    public:
        static Garden::Configuration getConfiguration(std::string workingDirectory);
    private:
        ConfigurationLoader();
        static std::string directoryNameof(const std::string &fileName);
};

#endif