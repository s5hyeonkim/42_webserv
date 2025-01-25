#ifndef CONFIG_HPP
# define CONFIG_HPP
# include <iostream>
# include <deque>
# include "Parser.hpp"
# include "ServerConfig.hpp"
# include "../exception/Exception.hpp"
# define CONFIG_NUM 1

class Config : public AConfig
{
	private:
		ServerConfig	m_server;
	public:
		Config();
		Config(std::string file);
		Config& operator=(const Config& objs);
		~Config();
		virtual void	setConfig(const AConfig& obj);
		bool			isValidConfigs() const;
		bool			isValidKeyword(std::string key) const;
		virtual void	printConfigs() const;
		ServerConfig&	getServer() const;
};

#endif