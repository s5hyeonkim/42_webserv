#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP
# include <string>
# include <map>

class ServerConfig
{
    private: 
        std::map <std::string, int> configs;
    public:
        ServerConfig(char *file);
        ~ServerConfig();
};

#endif