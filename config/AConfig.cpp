
#include "AConfig.hpp"

AConfig::AConfig(/* args */): m_configs(), m_default() { }
// AConfig::AConfig(/* args */): m_configs(), m_default(), m_scope(e_main) { }
// AConfig::AConfig(t_scope scope): m_configs(), m_default(), m_scope(scope) { }

AConfig::~AConfig() { }

AConfig::AConfig(const AConfig &srcs) {
	*this = srcs;
}

AConfig&	AConfig::operator=(const AConfig& obj) {
	std::map<std::string, std::string>::iterator it;

	if (this == &obj)
		return *this;
	// m_scope = obj.getScope();
	m_configs = obj.getConfigs();
	return *this;
}

void	AConfig::clear() {
	m_configs.clear();
}

std::map<std::string, std::string>	AConfig::getConfigs() const {
	return m_configs;
}
void	AConfig::setConfig(const AConfig& obj) {
	*this = obj;
}

// recent value update
void	AConfig::updateConfig(std::map<std::string, std::string> obj) {
	std::map<std::string, std::string>::iterator	it;

	for (it = obj.begin(); it != obj.end(); it++)
		m_configs[it->first] = it->second;
}

void	AConfig::updateDefault(std::map<std::string, std::string> obj) {
	std::map<std::string, std::string>::iterator	it;

	for (it = obj.begin(); it != obj.end(); it++)
		m_default[it->first] = it->second;
}


void	AConfig::setApiPoint(std::string &end_point, std::string &priority) {
	(void) end_point;
	(void) priority;
	Exception::handleInvalidFile();
}

size_t	AConfig::getConfigSize() const {
	return m_configs.size();
}

void	AConfig::addVal(std::string &key, std::string &val) {
	m_configs[key] = val;
}

void	AConfig::printConfigs() const {
	std::map<std::string, std::string>::const_iterator	it;

	std::cout << "<----------------DEBUG---------------->" << std::endl;
	for (it = m_configs.begin(); it != m_configs.end(); it++)
	{
		std::cout << "key: " << it->first << " val: " << it->second << std::endl;
	}
	std::cout << "<----------------PRINT END---------------->" << std::endl;
}

// std::map<std::string, std::string>::const_iterator	AConfig::getBeginIterator() const {
// 	return m_configs.cbegin();
// }

// std::map<std::string, std::string>::const_iterator	AConfig::getEndIterator() const {
// 	return m_configs.cend();
// }

// t_scope	AConfig::getScope(void) const {
// 	return m_scope;
// }

// void	AConfig::setScope(t_scope scope) {
// 	m_scope = scope;
// }