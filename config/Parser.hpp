#ifndef PARSER_HPP
# define PARSER_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include "./exception/Exception.hpp"

class Parser
{
    private:
    public:
        Parser(const char *file);
        ~Parser();
        // isValidKeyword?
        std::vector<std::string>	splitByDelimiters(std::stringstream &ss, const std::string delims);        
        void    parse();
        void    setKeyword(std::string lines);
        // isOpenBlock?
        bool    isClosedBlock(std::string lines);
        // isValidSimple?
        // find keyword which has '{}'
        std::string findBlockDirectives(std::string &lines);
        // find keyword which has ':'
        std::string findSimpleDirectives(std::string &lines);
        size_t     findStrsInVector(std::vector<std::string> &strs, std::string target, int beg);
        size_t     findCharInVector(std::vector<std::string> &strs, char target, int beg);
};



#endif