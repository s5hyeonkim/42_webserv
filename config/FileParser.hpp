#ifndef FILEPARSER_HPP
# define FILEPARSER_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <map>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "../exception/Exception.hpp"
class FileParser {
    private:
		std::deque<std::string>				m_frags;
		size_t								findEndCharsetFromStrs(char end);
		void								bringKeyAndValue(std::string& key, std::string& val, size_t pos);
		size_t								splitBySpaces(std::deque<std::string> &frags, std::string& line, size_t& prev, size_t& end);
		std::string							fileToStr(std::string file);
		void								setFragments(std::deque<std::string> &frags, std::string &line);

    public:
        FileParser();
		void								getFile(std::string file);
      
        FileParser(std::string file);
        ~FileParser();
		std::map<std::string, std::string>	getMap();

};

#endif