#ifndef ASERVER_HPP
# define ASERVER_HPP
# include "ServerConfig.hpp"
# include "Location.hpp"

class AServer
{
    private:
        ServerConfig    config;
        Location        *locations;
    public:
        AServer(char *file);
        ~AServer();
};

#endif