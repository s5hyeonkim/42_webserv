#include "LocationConfig.hpp"
// LocationConfig::LocationConfig(): AConfig(e_location), m_api_point(""), m_priority(e_prefix_match) {}
AConfig	*LocationConfig::mp_default = new LocationConfig(location_conf);
// MainConfig::MainConfig(std::string file): AConfig(e_main), m_server()
LocationConfig::LocationConfig(): AConfig(), m_api_point(""), m_priority(e_prefix_match) { }

LocationConfig::LocationConfig(std::string file): AConfig(), m_api_point(""), m_priority(e_prefix_match) {
	FileParser								parser;
	std::map<std::string, std::string>		ret;

	parser.getFile(file);
	ret = parser.getMap();
	updateDefaultConfig(ret);
// 	std::cout << "update Location Default Setting complete" << std::endl
}

// LocationConfig::LocationConfig(std::string& api_point, std::string priority): AConfig(e_location), m_api_point(api_point), m_priority() {
LocationConfig::LocationConfig(std::string& api_point, std::string priority): AConfig(), m_api_point(api_point), m_priority() {
	setPriority(priority);
}
AConfig	*LocationConfig::getInstance()
{
	if (!mp_default)
		mp_default = new LocationConfig(location_conf);
	return mp_default;
}
LocationConfig::~LocationConfig() {}

void	LocationConfig::deleteConfig() {
	if (mp_default)
		delete mp_default;
}

LocationConfig	&LocationConfig::operator=(const LocationConfig &obj)
{
	if (this == &obj)
		return *this;
	m_api_point = obj.m_api_point;
	m_priority = obj.m_priority;
	updateConfig(obj.getConfigs());
	return *this;
}

bool	LocationConfig::operator==(const LocationConfig& obj) {
	return (m_api_point == obj.m_api_point && m_priority == obj.m_priority && getConfigs() == obj.getConfigs());
}

t_priority	LocationConfig::getPriority() const {
	return m_priority;
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

// void	LocationConfig::updateDefaultSettings() {
// 	Parser								parser("../utils/conf.d/requirements/location.nginx_keys");
// 	std::map<std::string, std::string>	ret;

// 	ret = parser.getMap();
// 	this->AConfig::updateDefault(ret);
// 	std::cout << "update Location Default Setting complete" << std::endl;
// }
void	LocationConfig::inheritConfig(const AConfig& obj) {
	if (dynamic_cast<ServerConfig *>(&(const_cast<AConfig&>(obj))))
		updateConfig(obj.getConfigs());
	// else if (dynamic_cast<LocationConfig *>(&(const_cast<AConfig&>(obj))))
	else
		Exception::handleInvalidFile();
}

std::string	LocationConfig::getEndPoint() const {
	return m_api_point;
}

void	LocationConfig::checkValidConfigs(){
	AConfig::checkValidConfigs();
	// root 경로 검사
}