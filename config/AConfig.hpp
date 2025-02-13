#ifndef ACONFIG_HPP
# define ACONFIG_HPP
#include <iostream>
#include <sstream>
#include <map>
#include <deque>
#include <string>
#include <vector>
#include <set>
#include "../exception/Exception.hpp"

struct cmp {
	bool operator()(std::string &s1, std::string &s2) {
		if (s1.find('*') != s1.find('*'))
			return s1.find('*') < s2.find('*');
		return false;		
	}
};

class AConfig
{
	private:
		std::map<std::string, std::string>  m_configs;
		std::map<std::string, int>  		m_configs_int;
		std::vector<unsigned short>			ports;
		std::vector<std::string>			server_names;
		// std::map<std::string, std::string>  m_type;
		AConfig&	operator=(const AConfig& objs);

	public:
		AConfig(/* args */);
		// AConfig(const AConfig &srcs);
		virtual ~AConfig();
		std::map<std::string, std::string>  				getConfigs() const;
		// std::map<std::string, std::string>  				getDefaultConfigs() const;
		virtual void										setConfig(const AConfig& obj) = 0;
		virtual void										inheritConfig(const AConfig& obj) = 0;
		virtual void										setApiPoint(std::string &end_point, std::string &priority);
		size_t												getConfigSize() const;
		void												updateConfig(const AConfig& obj);
		void												updateDefaultConfig(std::map<std::string, std::string> obj);
		void												updateConfig(std::map<std::string, std::string> obj);
		// void												updateDefault(std::map<std::string, std::string> obj);
		void												addType(std::string& key, std::string& val);
		void												addVal(std::string& key, std::string& val);
		void												addVal(std::deque<std::string>& deque);
		virtual void										clear();
		std::string											find(std::string target) const;
		// virtual void										updateDefaultSettings() = 0;
		virtual void										checkValidConfigs();
		virtual void										printConfigs() const;
		bool												checkValueIsNumber(std::string &key, std::string &val);
		bool												checkValidValue(std::string &key, std::string &val);
		bool			hasPort(unsigned short port) const;
		size_t			checkServerName(std::string &server_name) const;
		virtual AConfig	*getInstance() = 0;
};

#endif