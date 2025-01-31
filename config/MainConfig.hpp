#ifndef MAINCONFIG_HPP
# define MAINCONFIG_HPP
# include <iostream>
# include <deque>
# include "Parser.hpp"
# include "ServerConfig.hpp"
# include "../exception/Exception.hpp"
# define CONFIG_NUM 1

class MainConfig : public AConfig
{
	private:
		ServerConfig	m_server;
	public:
		MainConfig();
		MainConfig(std::string file);
		MainConfig& operator=(const MainConfig& objs);
		~MainConfig();
		virtual void	setConfig(const AConfig& obj);
		// bool			isValidConfigs() const;
		// bool			isValidKeyword(std::string key) const;
		virtual void	inheritConfig(const AConfig &obj);
		virtual void	printConfigs() const;
		ServerConfig&	getServer() const;
		virtual void	updateDefaultSettings();
};

#endif