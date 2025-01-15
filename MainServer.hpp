#ifndef MAINSERVER_HPP
# define MAINSERVER_HPP
# include "AServer.hpp"

class MainServer : public AServer
{
    private:
        MainServer& operator=(const MainServer &other);
        MainServer(const MainServer &other);
    public:
        MainServer(char *config);
        ~MainServer();
};

#endif