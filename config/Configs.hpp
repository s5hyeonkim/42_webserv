#ifndef CONFIGS_HPP
# define CONFIGS_HPP
# include "MainConfig.hpp"
# include <string>

class Configs
{
	private:
		Configs(std::string file_cf);
		~Configs();
		static Configs	*mp_config;
		MainConfig		config;

	public:
		static Configs	*getInstance(std::string file_cf);

};


#endif