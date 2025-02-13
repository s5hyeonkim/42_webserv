
#include "AConfig.hpp"

AConfig::AConfig(/* args */): m_configs() { }
// AConfig::AConfig(/* args */): m_configs(), m_default(), m_scope(e_main) { }
// AConfig::AConfig(t_scope scope): m_configs(), m_default(), m_scope(scope) { }

AConfig::~AConfig() { }

// AConfig::AConfig(const AConfig &srcs) {
// 	*this = srcs;
// }

AConfig&	AConfig::operator=(const AConfig& obj) {
	std::map<std::string, std::string>::iterator it;

	if (this == &obj)
		return *this;
	// m_scope = obj.getScope();
	m_configs = obj.m_configs;
	// m_default = obj.getDefaultConfigs();
	return *this;
}

void	AConfig::clear() {
	m_configs.clear();
}

// std::map<std::string, std::string>	AConfig::getDefaultConfigs() const {
// 	return m_default;
// }

std::map<std::string, std::string>	AConfig::getConfigs() const {
	return m_configs;
}
// void	AConfig::setConfig(const AConfig& obj) {
// 	*this = obj;
// }

// if default value exist, the config value update // inherit 할때 씀
// void	AConfig::updateConfig(std::map<std::string, std::string> obj, AConfig& default_config) {
// 	std::map<std::string, std::string>::const_iterator	it;

// 	for (it = obj.begin(); it != obj.end(); it++)
// 	{
// 		try {
// 			default_config.find(it->first);
// 			m_configs[it->first] = it->second;		
// 		}
// 		catch(const std::exception& e) {
// 			std::cerr << "No : " << e.what() << '\n';
// 		}
// 	}
// }

void	AConfig::updateDefaultConfig(std::map<std::string, std::string> obj) {
	std::map<std::string, std::string>::iterator	it;

	for (it = obj.begin(); it != obj.end(); it++)
		m_configs[it->first] = it->second;
}

void	AConfig::updateConfig(std::map<std::string, std::string> obj) {
	std::map<std::string, std::string>::iterator	it;

	for (it = obj.begin(); it != obj.end(); it++)
		m_configs[it->first] = it->second;
}

void	AConfig::setApiPoint(std::string &end_point, std::string &priority) {
	(void) end_point;
	(void) priority;
	Exception::handleInvalidFile();
}

size_t	AConfig::getConfigSize() const {
	return m_configs.size();
}

unsigned int	strfyInt(std::string &num_str, int max, bool isNum)
{
	char	*ptr;
	double	d;

	d = strtod(num_str.c_str(), &ptr);
	if ((isNum && *ptr) || d > max || *(ptr + 1))
	{
		std::cout << num_str << std::endl;
		Exception::handleInvalidFile();
	}
	if (*ptr == 'k' || *ptr == 'K')
		d *= 1000;
	else if (*ptr == 'M' || *ptr == 'm')
		d *= 1000000;
	if (d > max || d < 0)
		Exception::handleInvalidFile();
	return static_cast<unsigned int>(d);
}

void	AConfig::addVal(std::deque<std::string> &deq) {
	std::stringstream	ss;

	getInstance()->find(deq[0]);
	if (deq[0] != "internal" && deq.size() == 1)
		Exception::handleInvalidFile();
	if (deq[0] == "error_page")
	{
		if (deq.size() <= 2)
			Exception::handleInvalidFile();
		for (size_t i = 1; i < deq.size() - 1; i++)
			m_configs[deq[i]] = deq.back();
	}
	else if (deq[0] == "listen")
	{
		for (size_t i = 1; i < deq.size(); i++)
			ports.push_back(strfyInt(deq[i], 65535, true));
	}
	else if (deq[0] == "server_name")
	{
		for (size_t i = 1; i < deq.size(); i++)
		{
			if (deq[i].find('*') != std::string::npos)
			{
				if (deq[i][0] != '*' && deq[i][deq[i].size() - 1] != '*')
					Exception::handleInvalidFile();
				else if ((deq[i][0] == '*' && deq[i][1] != '.') || deq.size() == 1)
					Exception::handleInvalidFile();
				else if (deq[i][deq[i].size() - 1] == '*' && deq[i][deq[i].size() - 2] != '.')
					Exception::handleInvalidFile();
			}
			server_names.push_back(deq[i]);
		}
	}

}

bool	AConfig::checkValueIsNumber(std::string &key, std::string &val)
{
	char	*ptr;
	double	value;
	int		coeff;

	// if (key == "listen")
	// 	ip_with_port.push_back(convertIP(val));
	// else if (key == "server_names")
	// 	server_names.push_back(val);
	coeff = 1;
	value = strtod(val.c_str(), &ptr);
	if (*(ptr + 1) || value > 1000 || value < 0)
		return false;
	if (*ptr == 'K' || *ptr == 'k')
		coeff = 1000;
	else if (*ptr == 'm' || *ptr == 'M')
		coeff = 60;
	// else if (*ptr == 'h')
	// 	coeff = 3600;
	m_configs_int[key] = value * coeff;
	return true;
}


void	AConfig::addVal(std::string &key, std::string &val) {

	getInstance()->find(key);
	m_configs[key] = val;
	// if (!checkValueIsNumber(key, val))
		// checkValidValue(key, val);
}

// void	AConfig::addType(std::string &key, std::string &val) {
// 	m_configs[key] = val;
// }

void	AConfig::printConfigs() const {
	std::map<std::string, std::string>::const_iterator	it;

	std::cout << "<----------------DEBUG---------------->" << std::endl;
	std::cout << "<----------------FILECONFIG---------------->" << std::endl;
	for (it = m_configs.begin(); it != m_configs.end(); it++)
	{
		// std::cout << "key: " << it->first << " val: " << it->second << std::endl;
		std::cout << "File: " << it->first << " " << it->second << std::endl;
	}
	// std::cout << "<----------------DEFAULT---------------->" << std::endl;
	// for (it = m_default.begin(); it != m_default.end(); it++)
	// {
	// 	std::cout << "Default: " << it->first << " val: " << it->second << std::endl;
	// }
	// std::cout << "<----------------PRINT END---------------->" << std::endl;
}

void	AConfig::checkValidConfigs() {
	std::map<std::string, std::string>::const_iterator	it;

	for (it = m_configs.cbegin(); it != m_configs.cend(); it++)
		getInstance()->find(it->first);
}

std::string	AConfig::find(std::string target) const {
	std::map<std::string, std::string>::const_iterator	it;

	if ((it = m_configs.find(target)) != m_configs.cend())
		return it->second;
	std::cerr << "the context is " << target << std::endl;
	Exception::handleInvalidAccess();
	return "";
}

bool	AConfig::hasPort(unsigned short port) const {
	for (size_t	i = 0; i < ports.size(); i++)
	{
		if (ports[i] == port)
			return true;
	}
	return false;
}

size_t	AConfig::checkServerName(std::string &server_name) const {
	size_t	j;

	for (size_t i = 0; i < server_names.size(); i++)
	{
		if (server_name == server_names[i] || server_name == "." + server_names[i])
			return 1;
		else if (server_names[i].find('*') == std::string::npos || server_names[i].size() > server_name.size())
			continue ;
		else if (server_names[i][0] == '*')
		{
			for (j = 0; j < server_names[i].size(); j++)
			{
				if (server_names[i][server_names[i].size() - 1 - j] != server_name[server_name.size() - j - 1] && j != server_names[i].size() - 1)
					break ;					
			}
			if (j == server_names[i].size())
				return 2;
		}
		else
		{
			for (j = 0; j < server_names[i].size(); j++)
			{
				if (server_names[i][j] != server_name[j] && j != server_names[i].size() - 1)
					break ;					
			}
			if (j == server_names[i].size())
				return 3;		
		}
	}
	return 4;
}