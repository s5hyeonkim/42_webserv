#ifndef PARSER_HPP
# define PARSER_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ServerConfig.hpp"
#include "LocationConfig.hpp"
# include "../exception/Exception.hpp"
class AConfig;

class Parser {
	private:
		std::deque<std::string>	m_frags;
		void					bringKeyAndValue(std::string& key, std::string& val, size_t pos);
		std::deque<std::string>	handleWildcard(std::string file);
		void					getFile(std::string file);
		void					getFiles(std::string& val);
		void					getKeywords(std::stringstream& ss);
		size_t					splitBySpaces(std::deque<std::string> &frags, std::string& line, size_t& prev, size_t& end);
		void					handleBlockDirectives(AConfig& obj);
		void					handleTypeDirectives(AConfig& obj);
		void					handleSimpleDirectives(AConfig& obj);
		size_t					findEndOfSimpleDirectives();
		void					preCheckBlock(AConfig& obj);
		void					postCheckBlock();
		size_t					findValueDeque(const std::string& val) const;

	public:
		Parser(std::string file);
		~Parser();
		void					handleDirectives(AConfig& obj);
		void					printFragments() const;
};

#include "AConfig.hpp"
#endif