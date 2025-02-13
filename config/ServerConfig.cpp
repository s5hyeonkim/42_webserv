#include "ServerConfig.hpp"

// server 에 필요한 키워드만 뽑는다.
// ServerConfig::ServerConfig(): AConfig(e_server), m_locations() { }
AConfig	*ServerConfig::mp_default = new ServerConfig(server_conf);
// MainConfig::MainConfig(std::string file): AConfig(e_main), m_server()
ServerConfig::ServerConfig(): AConfig(), m_locations() { }

ServerConfig::ServerConfig(std::string file): AConfig(), m_locations() {
	std::map<std::string, std::string>		ret;
	FileParser								parser;

	parser.getFile(file);
	ret = parser.getMap();
	updateDefaultConfig(ret);
// 	std::cout << "update Location Default Setting complete" << std::endl
}

ServerConfig::~ServerConfig() { }

AConfig	*ServerConfig::getInstance()
{
	if (mp_default == NULL)
		mp_default = new ServerConfig(server_conf);
	return mp_default;
}

void	ServerConfig::deleteConfig() {
	if (mp_default)
		delete mp_default;
}

void	ServerConfig::clear() {
	this->AConfig::clear();
	clearLocation();
}

ServerConfig&	ServerConfig::operator=(const ServerConfig &obj) {
	if (this == &obj)
		return *this;
	updateConfig(obj.getConfigs());
	// setScope(obj.getScope());
	for (size_t priority = 0; priority < 6;priority++)
	{
		m_locations[priority].clear();
		m_locations[priority].reserve(obj.m_locations[priority].size());
		m_locations[priority] = obj.m_locations[priority];
	}
		// setLocation(priority, obj.m_locations[priority]);
	return *this;
}

void	ServerConfig::clearLocation() {
	for (size_t i = 0; i < 6; i++)
		m_locations[i].clear();
}

void	ServerConfig::printConfigs() const {
	std::cout << "<----------------SERVER---------------->" << std::endl;
	this->AConfig::printConfigs();

	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < m_locations[i].size(); j++)
			m_locations[i][j].printConfigs();
	}
}

void	ServerConfig::setConfig(const AConfig &obj) {
	ServerConfig	*is_server;
	LocationConfig	*is_location;

	is_server = dynamic_cast<ServerConfig*>(const_cast<AConfig*>(&obj));
	is_location = dynamic_cast<LocationConfig*>(const_cast<AConfig*>(&obj));
	if (is_server)
		*this = *is_server;
	else if (is_location)
		addNewLocation(is_location->getPriority(), *is_location);
	else
		Exception::handleInvalidFile();
}

// size_t	ServerConfig::getSizeOfLocations() const {
// 	return m_locations.size();
// }

void	ServerConfig::setLocation(size_t priority, const std::vector<LocationConfig>& obj) {
	m_locations[priority].clear();
	m_locations[priority] = obj;
}

void	ServerConfig::inheritConfig(const AConfig& obj) {
	if (dynamic_cast<MainConfig*>(&(const_cast<AConfig&>(obj))))
		updateConfig(obj.getConfigs());
	else
		Exception::handleInvalidFile();
	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < m_locations[i].size(); j++)
			m_locations[i][j].inheritConfig(*this);
	}
}
// bool	ServerConfig::isValidKeyword(std::string key) const {
// 	if (key == "aa")
// 		return true;
// 	return false;
// }

// bool	ServerConfig::isValidConfigs() const {
// 	std::map<std::string, std::string>::const_iterator	it, ite;

// 	if (getConfigSize() != )
// 		return false;
// 	ite = getEndIterator();
// 	for (it = getBeginIterator(); it != ite; it++)	{
// 		if (!isValidKeyword(it->first))
// 			return false;
// 	}
// 	return true;
// }

void	ServerConfig::addNewLocation(std::string& api_point, std::string priority) {
	LocationConfig	lconfig(api_point, priority);

	m_locations[lconfig.getPriority()].push_back(lconfig);
}

void	ServerConfig::addNewLocation(size_t priority, const LocationConfig& obj) {
	m_locations[priority].push_back(obj);
}

// void	ServerConfig::updateDefaultSettings() {
// 	Parser								parser("../utils/conf.d/requirements/server.nginx_keys");
// 	std::map<std::string, std::string>	ret;

// 	ret = parser.getMap();
// 	// std::cout << "update Server Default Setting complete" << std::endl;
// }

// void	ServerConfig::inheritConfig(const AConfig& obj) {
// 	updateConfig(obj.getConfigs());
// }
std::string	ServerConfig::find(std::string api_name, std::string target) const {
	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < m_locations[i].size(); j++)
		// if (checkExpression(i, api_name))
		if (m_locations[i][j].getEndPoint() == api_name)
			return m_locations[i][j].find(target);
	}
	std::cerr << "check api name" << std::endl;
	Exception::handleInvalidAccess();
	return "";
}

std::string	ServerConfig::getServerName() const {
	return this->AConfig::find("server_name");
}

int	ServerConfig::getPort() const {
	std::string	portStr;
	int			port;

	port = 0;
	portStr = this->AConfig::find("listen");
	for (size_t i = 0; i < portStr.size(); i++)
		port = port * 10 + (portStr[i] - '0');
	return port;
}

void	ServerConfig::checkValidConfigs() {
	std::set<std::string>	api_names;
	std::string				name;

	AConfig::checkValidConfigs();
	for (size_t i = 0; i < 6; i++)
	{
		api_names.clear();
		for (size_t	j = 0; j < m_locations[i].size(); j++)
		{
			name = m_locations[i][j].getEndPoint();
			if(api_names.find(name) == api_names.end())
				api_names.insert(name);
			else
				Exception::handleInvalidFile();
			m_locations[i][j].checkValidConfigs();
		}
	}
}

