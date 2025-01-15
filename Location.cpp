#include "Location.hpp"

Location::Location(char *file): config(LocationConfig(file)), apiAddr(), returnVal()
{
}

Location::~Location() {}