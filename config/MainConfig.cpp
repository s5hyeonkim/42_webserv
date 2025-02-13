#include "MainConfig.hpp"

AConfig	*MainConfig::mp_default = new MainConfig();
// MainConfig::MainConfig(std::string file): AConfig(e_main), m_server()
MainConfig::MainConfig(): AConfig(), m_servers() {
	FileParser								parser;
	std::map<std::string, std::string>		ret;

	std::cout << "default constructor called" << std::endl;
	parser.getFile(http_conf);
	ret = parser.getMap();
	updateDefaultConfig(ret);
// 	std::cout << "update Location Default Setting complete" << std::endl
}

MainConfig::MainConfig(std::string file): AConfig(), m_servers()
{
	Parser	parser(file);

	std::cout << "Main Directive parsing start" << std::endl;
	parser.handleDirectives(*this);
	std::cout << "parse finished" << std::endl;
	// printConfigs();
}

MainConfig::~MainConfig() {}

void	MainConfig::deleteConfig() {
	if (mp_default)
		delete mp_default;
}
AConfig	*MainConfig::getInstance()
{
	if (mp_default == NULL)
		mp_default = new MainConfig();
	return mp_default;
}
MainConfig&	MainConfig::operator=(const MainConfig& obj)
{
	if (this == &obj)
		return *this;
	m_servers.reserve(obj.m_servers.size());
	m_servers = obj.m_servers;
	// AConfig::setScope(obj.getScope());
	AConfig::updateConfig(obj.getConfigs());
	return *this;
}

void	MainConfig::printConfigs() const {
	std::cout << "<----------------MAINCONFIG---------------->" << std::endl;
	this->AConfig::printConfigs();
	for (size_t i = 0; i < m_servers.size(); i++)
	{
		std::cout << "<----------------SERVERCONFIG " << i << " ---------------->" << std::endl;
		m_servers[i].printConfigs();
	}
}

void	MainConfig::setConfig(const AConfig& obj) {
	MainConfig			*is_http;
	ServerConfig	*is_server;
	
	is_http = dynamic_cast<MainConfig*>(&(const_cast<AConfig&>(obj)));
	is_server = dynamic_cast<ServerConfig*>(&(const_cast<AConfig&>(obj)));
	if (is_http)
		*this = *is_http;
	else if (is_server)
		m_servers.push_back(*is_server);
	else
		Exception::handleInvalidFile();
}

// void	MainConfig::updateDefaultSettings() {
// 	Parser								parser("../utils/conf.d/requirements/http.nginx_keys");
// 	std::map<std::string, std::string>	ret;

// 	ret = parser.getMap();
// 	this->AConfig::updateDefault(ret);
// 	// std::cout << "update Main Default Setting complete" << std::endl;
// }

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

std::string	MainConfig::find(std::string server_name, std::string target) const {
	ServerConfig	ret;

	ret = findServer(server_name);
	return ret.AConfig::find(target);
}

std::string	MainConfig::find(std::string server_name, std::string api_name, std::string target) const {
	ServerConfig	ret;

	ret = findServer(server_name);
	return ret.find(api_name, target);
}

void	MainConfig::checkValidConfigs() {
	std::set<std::string>	server_names;
	std::string				name;

	AConfig::checkValidConfigs();
	for (size_t i = 0; i < m_servers.size(); i++)
	{
		name = m_servers[i].getServerName();
		if(server_names.find(name) == server_names.end())
			server_names.insert(name);
		else
			Exception::handleInvalidFile();
		m_servers[i].checkValidConfigs();
	}
}

ServerConfig	MainConfig::findServer(std::string &server_name) const {
	// struct addrinfo	v;
	size_t	priority, id;
	int		port;

	port = 80;
	priority = 5;
	id = (size_t) -1;
	for (size_t i = 0; i < m_servers.size(); i++)
	{
		if (m_servers[i].hasPort(port) && priority > m_servers[i].checkServerName(server_name))
		{
			priority = m_servers[i].checkServerName(server_name);
			id = i;
		}
		if (priority == 1)
			break ;
	}
	if (id == (size_t) -1)
		Exception::handleInvalidFile();
	return m_servers[id];
	// 없으면 에러 처리후 유유빈빈이  단에서 에ㅔ러페이지 호출
}