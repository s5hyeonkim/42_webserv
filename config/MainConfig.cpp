#include "MainConfig.hpp"

// MainConfig::MainConfig(std::string file): AConfig(e_main), m_server()
MainConfig::MainConfig(std::string file): AConfig(), m_server()
{
	Parser	parser(file);

	updateDefaultSettings();
	parser.handleDirectives(*this);
	// printConfigs();
}

MainConfig::~MainConfig() {}

MainConfig&	MainConfig::operator=(const MainConfig& obj)
{
	if (this == &obj)
		return *this;
	m_server = obj.m_server;
	// AConfig::setScope(obj.getScope());
	AConfig::updateConfig(obj.getConfigs());
	AConfig::updateDefault(obj.getDefaultConfigs());
	return *this;
}

void	MainConfig::printConfigs() const {
	std::cout << "<----------------CONFIG---------------->" << std::endl;
	this->AConfig::printConfigs();
	m_server.printConfigs();
}

void	MainConfig::setConfig(const AConfig& obj) {
	MainConfig			*is_http;
	ServerConfig	*is_server;
	
	is_http = dynamic_cast<MainConfig*>(&(const_cast<AConfig&>(obj)));
	is_server = dynamic_cast<ServerConfig*>(&(const_cast<AConfig&>(obj)));
	if (is_http)
		*this = *is_http;
	else if (is_server)
		this->m_server = *is_server;
	else
		Exception::handleInvalidFile();
}


// bool	MainConfig::isValidKeyword(std::string key) const
// {
// 	if (key != "aa")
// 		return true;
// 	return false;
// }

void	MainConfig::updateDefaultSettings() {
	Parser								parser("../utils/conf.d/requirements/http.nginx_keys");
	std::map<std::string, std::string>	ret;

	ret = parser.getMap();
	this->AConfig::updateDefault(ret);
	std::cout << "update Main Default Setting complete" << std::endl;
}

void	MainConfig::inheritConfig(const AConfig& obj) {
	MainConfig			*is_http;
	ServerConfig	*is_server;
	
	is_http = dynamic_cast<MainConfig*>(&(const_cast<AConfig&>(obj)));
	is_server = dynamic_cast<ServerConfig*>(&(const_cast<AConfig&>(obj)));
	if (is_http)
		updateConfig(obj.getConfigs());
	else if (is_server)
		is_server->inheritConfig(*this);
	// else
		// Exception::handleInvalidFile();
}