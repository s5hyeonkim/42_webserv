#include "AServer.hpp"
/* ************************************************************************** */
/* ------------------------------     OCCF    ------------------------------- */
/* ************************************************************************** */

AServer::AServer(char *file): config(ServerConfig(file)), locations()
{
    locations = new Location(file);
}

AServer::~AServer() {
    delete locations;
}