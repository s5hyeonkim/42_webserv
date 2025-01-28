#include "Format.hpp"

Format::Format(/* args */) {

}

Format::~Format() {

}

// try로 감싸기
void	Format::handleRequestForm(std::string lines) { 
    
    std::stringstream   ss(lines);
    size_t              pos;

    if (std::getline(ss, lines))
    while(std::getline(ss, lines))
    {
        if (line.find(':') == std::string::npos || line.find('\r') != line.size() - 1)
            throw Exception::handleInvalidRequest();
        
        pos = line.find(':');
        if (pos == std::string::npos)
        
    }
}
