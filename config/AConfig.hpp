#ifndef ACONFIG_HPP
# define ACONFIG_HPP
#include <iostream>
#include <map>
#include <deque>
#include <string>
#include "../exception/Exception.hpp"

class AConfig
{
	private:
		std::map<std::string, std::string>  m_configs;
		std::map<std::string, std::string>  m_default;
		std::map<std::string, std::string>  m_type;
	public:
		AConfig(/* args */);
		// AConfig(t_scope scope);
		AConfig(const AConfig &srcs);
		AConfig&	operator=(const AConfig& objs);
		virtual ~AConfig();
		std::map<std::string, std::string>  				getConfigs() const;
		std::map<std::string, std::string>  				getDefaultConfigs() const;
		virtual void										setConfig(const AConfig& obj) = 0;
		virtual void										inheritConfig(const AConfig& obj) = 0;
		// t_scope												getScope() const;
		// void												setScope(t_scope scope);
		virtual void										setApiPoint(std::string &end_point, std::string &priority);
		// std::map<std::string, std::string>::const_iterator  getBeginIterator() const;
		// std::map<std::string, std::string>::const_iterator  getEndIterator() const;
		size_t												getConfigSize() const;
		void												updateConfig(const AConfig& obj);
		void												updateConfig(std::map<std::string, std::string> obj);
		void												updateDefault(std::map<std::string, std::string> obj);
		void												addType(std::string& key, std::string& val);
		void												addVal(std::string& key, std::string& val);
		virtual void										clear();
		virtual void										printConfigs() const;
		virtual void										updateDefaultSettings() = 0;
		void												checkValidConfigs() const;
		// virtual void										checkValidConfigs() const = 0;
		// virtual bool										isValidKeyword(std::string key) const = 0;
};

#endif