#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP
# include <vector>
# include "LocationConfig.hpp"
# include "FileParser.hpp"
# define server_conf "../utils/conf.d/requirements/server.nginx_keys"
class MainConfig;

class ServerConfig : public AConfig
{
	private:
		static AConfig	*mp_default;
		std::vector<LocationConfig> m_locations[6];
		ServerConfig(std::string file);

	public:
		ServerConfig();
		ServerConfig(AConfig& srcs);
		~ServerConfig();
		ServerConfig&	operator=(const ServerConfig& objs);
		void			setLocation(size_t priority, const std::vector<LocationConfig> &obj);
		virtual void	setConfig(const AConfig& obj);
		virtual void	clear();
		size_t	getSizeOfLocations() const;
		std::string		getServerName() const;
		int				getPort() const;
		std::string		find(std::string api_point, std::string target) const;
		virtual void	inheritConfig(const AConfig& obj);
		void	addNewLocation(size_t priority, const LocationConfig& obj);
		void	addNewLocation(std::string& api_point, std::string priority);
		virtual void	printConfigs() const;
		virtual void			checkValidConfigs();
		virtual AConfig	*getInstance();
		static void				deleteConfig();

		void			clearLocation();
};
# include "MainConfig.hpp"

#endif