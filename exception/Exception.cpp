#include "Exception.hpp"

void    Exception::handleInvalidArgs() const
{
    throw std::logic_error("invalid arguments.");
}