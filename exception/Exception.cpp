#include "Exception.hpp"

void    Exception::handleInvalidFile()
{
    throw std::logic_error("invalid config file.");
}

