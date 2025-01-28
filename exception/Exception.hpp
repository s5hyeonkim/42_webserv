#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP
#include <stdexcept>

class Exception 
{
    public:
        static void handleInvalidFile();
        static void handleInvalidFile(int _errno);
        static void handleInvalidRequest();
        static void handleInvalidResponse();
};

#endif
