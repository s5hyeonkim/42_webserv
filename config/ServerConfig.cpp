#include "ServerConfig.hpp"

// server 에 필요한 키워드만 뽑는다.
// ServerConfig::ServerConfig(): AConfig(e_server), m_locations() { }
ServerConfig::ServerConfig(): AConfig(), m_locations() {
	updateDefaultSettings();
}

ServerConfig::~ServerConfig() {}


void	ServerConfig::clear() {
	this->AConfig::clear();
	m_locations.clear();
}

ServerConfig&	ServerConfig::operator=(const ServerConfig &obj) {
	if (this == &obj)
		return *this;
	updateConfig(obj.getConfigs());
	updateDefault(obj.getDefaultConfigs());
	// setScope(obj.getScope());
	for (size_t i = 0; i < obj.m_locations.size(); i++)
		setLocation(obj.m_locations[i]);
	return *this;
}

void	ServerConfig::printConfigs() const {
	std::cout << "<----------------SERVER---------------->" << std::endl;
	this->AConfig::printConfigs();

	for (size_t i = 0; i < m_locations.size(); i++)
		m_locations[i].printConfigs();
}

void	ServerConfig::setConfig(const AConfig &obj) {
	ServerConfig	*is_server;
	LocationConfig	*is_location;

	is_server = dynamic_cast<ServerConfig*>(const_cast<AConfig*>(&obj));
	is_location = dynamic_cast<LocationConfig*>(const_cast<AConfig*>(&obj));
	if (is_server)
		*this = *is_server;
	else if (is_location)
		this->addNewLocation(*is_location);
	else
		Exception::handleInvalidFile();
}

// size_t	ServerConfig::getSizeOfLocations() const {
// 	return m_locations.size();
// }

void	ServerConfig::setLocation(const LocationConfig& obj) {
	size_t	j;

	for (j = 0; j < m_locations.size(); j++) {
		if (m_locations[j] == obj)
			break ;
	}
	if (j == m_locations.size())
		addNewLocation(obj);
}

void	ServerConfig::inheritConfig(const AConfig& obj) {
	for (size_t i = 0; i < m_locations.size(); i++)
		m_locations[i].inheritConfig(*this);
	if (dynamic_cast<MainConfig*>(&(const_cast<AConfig&>(obj))))
		updateConfig(obj.getConfigs());
	else
		Exception::handleInvalidFile();
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
	m_locations.push_back(LocationConfig(api_point, priority));
}

void	ServerConfig::addNewLocation(const LocationConfig& obj) {
	m_locations.push_back(obj);
}

void	ServerConfig::updateDefaultSettings() {
	Parser								parser("../utils/conf.d/requirements/server.nginx_keys");
	std::map<std::string, std::string>	ret;

	ret = parser.getMap();
	this->AConfig::updateDefault(ret);
	std::cout << "update Server Default Setting complete" << std::endl;
}

// void	ServerConfig::inheritConfig(const AConfig& obj) {
// 	updateConfig(obj.getConfigs());
// }