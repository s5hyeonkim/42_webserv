#ifndef APPCONFIG_HPP
# define APPCONFIG_HPP
# include <iostream>
# include <string>
# include "Parser.hpp"
# include "MainConfig.hpp"
# define default_cf "../utils/conf.d/requirements/setting.conf"

class AppConfig
{
	private:
		AppConfig(std::string file_cf);
		~AppConfig();
		static AppConfig	*mp_config;
		MainConfig			m_config;

	public:
		static AppConfig	*getInstance(std::string file_cf);
		ServerConfig		getServerConfig(std::string &server_name) const;
		std::string			getter(std::string target) const;
		// reference check
		std::string			getter(std::string server_name, std::string target) const;
		std::string			getter(std::string server_name, std::string api_name, std::string target) const;
		void				checkKey(std::string key, const AConfig &config) const;
		// validation
		// void				checkValidConfigs() const;
};

#endif