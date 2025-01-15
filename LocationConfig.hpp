#ifndef LOCATIONCONFIG_HPP
# define LOCATIONCONFIG_HPP
# include "AConfig.hpp"

class LocationConfig: public AConfig
{
    std::string  apiAddr;
    std::string  returnVal;
    public:
        LocationConfig(char *file);
        ~LocationConfig();
};

#endif
