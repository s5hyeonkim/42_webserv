#include "Parser.hpp"

Parser::Parser(const char *file) {
    std::ifstream       file_in(file);
    std::stringstream   ss;

    if (!file_in)
        Exception::handleInvalidFile();
    ss << file_in.rdbuf();
    splitByDelimiters(ss, "\n\t ");
	file_in.close();;
}

Parser::~Parser() { }

std::vector<std::string>	Parser::splitByDelimiters(std::stringstream &ss, const std::string delims) {
    std::vector <std::string>	frags;
    std::string 				line;
    size_t      				prev;

	prev = 0;
    ss >> line;
    for (size_t i = 0; i < line.size(); i++) {
        if (prev != i && delims.find(line[i]) != std::string::npos) {
            frags.push_back(line.substr(prev, i));
			prev = i + 1;
        }
    }
}

// size_t	Parser::findStrsInVector(std::vector<std::string> &strs, std::string target, int beg)
// {
// 	for (; beg < strs.size(); beg++)
// 	{
// 		if (strs[beg] == target)
// 			return beg;
// 	}
// 	return -1;
// }

// size_t	Parser::findCharInVector(std::vector<std::string> &strs, char target, int beg)
// {
// 	for (; beg < strs.size(); beg++)
// 	{
// 		if (strs[beg].back() == target)
// 			return beg;
// 	}
// 	return -1;
// }

