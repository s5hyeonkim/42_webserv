#include "LocationConfig.hpp"
// LocationConfig::LocationConfig(): AConfig(e_location), m_api_point(""), m_priority(e_prefix_match) {}
LocationConfig::LocationConfig(): AConfig(), m_api_point(""), m_priority(e_prefix_match) {}

// LocationConfig::LocationConfig(std::string& api_point, std::string priority): AConfig(e_location), m_api_point(api_point), m_priority() {
LocationConfig::LocationConfig(std::string& api_point, std::string priority): AConfig(), m_api_point(api_point), m_priority() {
	setPriority(priority);
}

LocationConfig::~LocationConfig() {}

LocationConfig	&LocationConfig::operator=(const LocationConfig &obj)
{
	if (this == &obj)
		return *this;
	m_api_point = obj.m_api_point;
	m_priority = obj.m_priority;
	// this->AConfig::setScope(obj.getScope());
	this->AConfig::updateConfig(obj.getConfigs());
	return *this;
}

bool	LocationConfig::operator==(const LocationConfig& obj) {
	return (m_api_point == obj.m_api_point && m_priority == obj.m_priority && getConfigs() == obj.getConfigs());
}

void	LocationConfig::setPriority(std::string &priority){
	if (priority == "=")
		m_priority = e_exactly;
	else if (priority == "^~")
		m_priority = e_preferential_prefix_match;
	else if (priority == "~")
		m_priority = e_regex_match_with_sensitive_case;
	else if (priority == "~*")
		m_priority = e_regex_match_with_insensitive_case;
	else if (priority == "")
		m_priority = e_prefix_match;
	else
	{
		std::cerr << "DEBUG: location priority is wrong." << std::endl;
		Exception::handleInvalidFile();
	}
}

void	LocationConfig::printConfigs() const {
	std::cout << "<----------------Location---------------->" << std::endl;
	this->AConfig::printConfigs();
}

// location 중첩일때
void	LocationConfig::setConfig(const AConfig &obj){
	LocationConfig	*is_location;

	is_location = dynamic_cast<LocationConfig*>(const_cast<AConfig*>(&obj));
	if (is_location)
		*this = *is_location;
	else
		Exception::handleInvalidFile();
	std::cout << "location called" << std::endl;
}


void	LocationConfig::setApiPoint(std::string &end_point, std::string &priority)
{
	if (priority != "location")
		setPriority(priority);
	m_api_point = end_point;
}

bool	LocationConfig::isValidKeyword(std::string key) const {
	if (key != "aa")
		return true;
	return false;
}

bool	LocationConfig::isValidConfigs() const {
	std::map<std::string, std::string>::const_iterator	it, ite;

	// if (getConfigSize() != ?)
		// return false;
	// it = getBeginIterator();
	// ite = getEndIterator();
	// for (; it != ite; it++)	{
	// 	if (!isValidKeyword(it->first))
	// 		return false;
	// }
	return true;
}

void	LocationConfig::readDefaultSettings() {
	Parser								parser("./utils/conf.d/requirements/location.nginx_keys");
	std::map<std::string, std::string>	ret;

	ret = parser.getMap();
	this->AConfig::updateDefault(ret);
}