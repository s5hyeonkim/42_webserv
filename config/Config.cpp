#include "Config.hpp"

Config::Config(std::string file): AConfig(e_main), m_server()
{
	Parser	parser(file);

	parser.handleDirectives(*this);
	printConfigs();
}

Config::~Config() {}

Config&	Config::operator=(const Config& obj)
{
	if (this == &obj)
		return *this;
	m_server = obj.m_server;
	AConfig::setScope(obj.getScope());
	AConfig::setConfigs(obj.getConfigs());
	return *this;
}

void	Config::printConfigs() const {
	std::cout << "<----------------CONFIG---------------->" << std::endl;
	this->AConfig::printConfigs();
	m_server.printConfigs();
}

void	Config::setConfig(const AConfig& obj) {
	Config			*is_http;
	ServerConfig	*is_server;
	
	is_http = dynamic_cast<Config*>(&(const_cast<AConfig&>(obj)));
	is_server = dynamic_cast<ServerConfig*>(&(const_cast<AConfig&>(obj)));
	if (is_http)
		*this = *is_http;
	else if (is_server)
		this->m_server = *is_server;
	else
		Exception::handleInvalidFile();
}


bool	Config::isValidKeyword(std::string key) const
{
	if (key != "aa")
		return true;
	return false;
}

bool	Config::isValidConfigs() const
{
	std::map<std::string, std::string>::const_iterator	it, ite;

	// ite = getEndIterator();
	// for (it = getBeginIterator(); it != ite; it++)	{
	// 	if (!isValidKeyword(it->first))
	// 		return false;
	// }
	return true;
}
