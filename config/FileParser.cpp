#include "FileParser.hpp"
FileParser::FileParser():m_frags() {}

// FileParser::FileParser(std::string file) {
// 	if (file == "")
// 		file = "utils/conf.d/default.conf";
// 	getFile(file);
// }

FileParser::~FileParser() { }

std::map<std::string, std::string>	FileParser::getMap() {
	std::map<std::string, std::string>	ret;
	std::string							key, val;
	size_t								pos;

	while ((pos = findEndCharsetFromStrs(';')) != (size_t)-1) {
		bringKeyAndValue(key, val, pos);
		ret[key] = val;
	}
	return ret;
}
void	FileParser::bringKeyAndValue(std::string &key, std::string &val, size_t pos) {
	val = "";
	for (size_t i = 1; i <= pos; i++) {
		// if (i != pos)
			val += m_frags[i] + " ";
		// else
			// val += m_frags[pos].substr(0, m_frags[pos].size() - 1);
	}
	key = m_frags[0];
	m_frags.erase(m_frags.begin(), m_frags.begin() + pos + 1);
}

size_t	FileParser::findEndCharsetFromStrs(char end) {
	size_t	pos;

	for (pos = 0; pos < m_frags.size(); pos++) {
		if (m_frags[pos][m_frags[pos].size() - 1] == end)
			return pos;
	}
	return (size_t) -1;
}
void	FileParser::getFile(std::string file)
{
	std::deque<std::string>	frags;
	std::string				line;

	line = fileToStr(file);
	std::cout << "FileParser file start" << file << std::endl;
	setFragments(frags, line);
	// printFragments();
	m_frags.insert(m_frags.begin(), frags.begin(), frags.end());
}
std::string	FileParser::fileToStr(std::string file)
{
	std::ifstream		file_in;
	std::stringstream	ss;
	struct stat			sb;

	if (stat(file.c_str(), &sb) == -1)
	{
		std::cerr << "no File " << file << std::endl;
		Exception::handleInvalidFile(errno);
	}
	file_in.open(file.c_str());
	if (!file_in)
	{
		std::cerr << "DEBUG: No file to parse " << file << std::endl;
		Exception::handleInvalidFile();
	}
	ss << file_in.rdbuf();
	file_in.close();
	return ss.str();
}
void	FileParser::setFragments(std::deque<std::string> &frags, std::string &line) {
	size_t					prev, end;

	prev = 0;
	end = 0;
	// std::cout << line << std::endl;
	// std::cout << "line print end" << std::endl;
	while (end < line.size())
		splitBySpaces(frags, line, prev, end);
	if (prev != end)
		frags.push_back(line.substr(prev, end));
}
size_t	FileParser::splitBySpaces(std::deque<std::string> &frags, std::string &line, size_t &prev, size_t &end)
{
	if (line[end] == '#')
	{
		if (line.find('\n', prev) == std::string::npos)
			end = line.size();
		else
			end = line.find('\n', prev);
		prev = end + 1;
	}
	else if (line[end] == '\t' || line[end] == '\n' || line[end] == ' ')
	{
		if (prev != end)
			frags.push_back(line.substr(prev, end - prev));
		prev = end + 1;
	}
	return ++end;
}