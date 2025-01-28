#include "ServerConfig.hpp"

// server 에 필요한 키워드만 뽑는다.
ServerConfig::ServerConfig(): AConfig(e_server), m_locations() { }

ServerConfig::~ServerConfig() {}

bool	ServerConfig::isValidKeyword(std::string key) const
{
	if (key == "aa")
		return true;
	return false;
}

void	ServerConfig::clear() {
	this->AConfig::clear();
	m_locations.clear();
}

ServerConfig&	ServerConfig::operator=(const ServerConfig &obj) {
	if (this == &obj)
		return *this;
	setConfigs(obj.getConfigs());
	setScope(obj.getScope());
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

bool	ServerConfig::isValidConfigs() const {
	std::map<std::string, std::string>::const_iterator	it, ite;

	// if (getConfigSize() != )
		// return false;
	// ite = getEndIterator();
	// for (it = getBeginIterator(); it != ite; it++)	{
	// 	if (!isValidKeyword(it->first))
	// 		return false;
	// }
	return true;
}

void	ServerConfig::addNewLocation(std::string& api_point, std::string priority) {
	m_locations.push_back(LocationConfig(api_point, priority));
}

void	ServerConfig::addNewLocation(const LocationConfig& obj) {
	m_locations.push_back(obj);
}
