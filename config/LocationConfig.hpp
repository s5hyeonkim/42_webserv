#ifndef LOCATIONCONFIG_HPP
# define LOCATIONCONFIG_HPP
#include "AConfig.hpp"
# include "FileParser.hpp"
# define location_conf "../utils/conf.d/requirements/location.nginx_keys"

typedef enum e_priority{
	e_exactly, // =
	e_preferential_prefix_match, // ^~
	e_regex_match_with_sensitive_case, // ~
	e_regex_match_with_insensitive_case, // ~*
	e_prefix_match // ""
}	t_priority;

class ServerConfig;

class LocationConfig : public AConfig
{
	private:
		std::string m_api_point;
		t_priority	m_priority;
		static AConfig	*mp_default;
		LocationConfig(std::string file);

	public:
		LocationConfig();
		LocationConfig(std::string &api_point, std::string priority);
		LocationConfig&	operator=(const LocationConfig& obj);
		bool			operator==(const LocationConfig& obj);
		~LocationConfig();
		t_priority		getPriority() const;
		void			setPriority(std::string &priority);
		void			setConfig(const AConfig& obj);
		std::string		getEndPoint() const;
		virtual void			checkValidConfigs();
		virtual void	setApiPoint(std::string &end_point, std::string &priority);
		virtual void	inheritConfig(const AConfig& obj);
		virtual void	printConfigs() const;
		static void				deleteConfig();
		// virtual void	updateDefaultSettings();
		virtual AConfig	*getInstance();
};
# include "ServerConfig.hpp"

#endif
