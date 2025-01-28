#include "Exception.hpp"
#include <cerrno>
#include <string.h>

void    Exception::handleInvalidFile()
{
    throw std::logic_error("invalid config file.");
}

void    Exception::handleInvalidFile(int _errno)
{
    std::string lines;

    lines = "invalid config file.\n";
    throw std::logic_error(lines + strerror(_errno));
}

void    Exception::handleInvalidRequest()
{
    throw std::logic_error("invalid request.");
}

void    Exception::handleInvalidResponse()
{
    throw std::logic_error("invalid response.");
}