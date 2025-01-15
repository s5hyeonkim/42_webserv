#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP
# include "AConfig.hpp"

class ServerConfig : public AConfig
{
    private: 
        std::string server_name;
    public:
        ServerConfig(char *file);
        ~ServerConfig();
};

#endif