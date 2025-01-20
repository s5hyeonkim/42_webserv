#ifndef CONFIG_HPP
# define CONFIG_HPP
# include <iostream>
# include <vector>
# include <map>
# include "./exception/Exception.hpp"
# include "ServerConfig.hpp"

class Config
{
    private:
        std::map<std::string, int>  configs;
        std::vector<ServerConfig>   servers;

    public:
        Config(char *file);
        ~Config();
        void    addBlockConfigs(std::vector<std::string> &configs, int beg);
        void    addSimpleConfigs(std::vector<std::string> &configs, int beg);
        void    addExtraConfigs(std::vector<std::string> &configs, int beg);
        void    parse(std::vector<std::string> &configs);
};

#endif