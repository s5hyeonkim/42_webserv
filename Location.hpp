#ifndef LOCATION_HPP
# define LOCATION_HPP
#include "LocationConfig.hpp"

class Location
{
    private:
        LocationConfig  config;    
        std::string  apiAddr;
        std::string  returnVal;

    public:
        Location(char *file);
        ~Location();
};

#endif