#include "Config.hpp"

Config::Config(char *file) {
    
}

Config::~Config() {}

void	Config::addBlockConfigs(std::vector<std::string> &configs, int beg) {
    std::vector<std::string>::iterator  it;

    if (configs[beg] == "http" && configs.find(configs.begin() + beg, configs.end()))
    {
    }
    else if (configs[beg] == "event")
    {

    }
    else if (configs[beg] == "server")
    {

    }
    else if (configs[beg] == "location")
    {

    }
    else
    {
        std::cerr << "invalid block name" << std::endl;
        Exception::handleInvalidFile();
    }

}

void	Config::parse(std::vector<std::string> &configs)
{
	size_t	beg, blockPos, simplePos;

	beg = 0;
	while (beg < configs.size())
	{
		if (configs[beg] != "{" && configs[beg].back() != ';')
		{
            if (beg == configs.size() - 1)
            {
                std::cerr << "invalid syntax" << std::endl;
                Exception::handleInvalidFile();
            }
			if (configs[beg + 1] == "{")
                addBlockConfigs(configs, beg);
            else if (configs[beg + 1].back() == ';')
                addSimpleConfigs(configs, beg);
            else
                addExtraConfigs(configs, beg);
		}
		
	}
}