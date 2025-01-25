#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP
# include <vector>
# include "LocationConfig.hpp"

class ServerConfig : public AConfig
{
	private:
		std::vector<LocationConfig> m_locations;
	public:
		ServerConfig();
		ServerConfig(AConfig& srcs);
		~ServerConfig();
		ServerConfig&	operator=(const ServerConfig& objs);
		void			setLocation(const LocationConfig& obj);
		virtual void	setConfig(const AConfig &obj);
		virtual void	clear();
		size_t	getSizeOfLocations() const;
		bool	isValidConfigs() const;
		bool	isValidKeyword(std::string key) const;
		void	addNewLocation(const LocationConfig& obj);
		void	addNewLocation(std::string& api_point, std::string priority);
		virtual void	printConfigs() const;
};


#endif