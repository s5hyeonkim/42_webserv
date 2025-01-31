#ifndef LOCATIONCONFIG_HPP
# define LOCATIONCONFIG_HPP
#include "AConfig.hpp"
class	Parser;

typedef enum e_priority{
	e_exactly, // =
	e_preferential_prefix_match, // ^~
	e_regex_match_with_sensitive_case, // ~
	e_regex_match_with_insensitive_case, // ~*
	e_prefix_match // ""
}	t_priority;

class LocationConfig : public AConfig
{
	private:
		std::string m_api_point;
		t_priority	m_priority;

	public:
		LocationConfig();
		LocationConfig(std::string &api_point, std::string priority);
		LocationConfig&	operator=(const LocationConfig& obj);
		bool			operator==(const LocationConfig& obj);
		~LocationConfig();
		void			setConfig(const AConfig& obj);
		void			setPriority(std::string &priority);
		virtual void	setApiPoint(std::string &end_point, std::string &priority);
		virtual void	inheritConfig(const AConfig& obj);
		virtual void	printConfigs() const;
		// virtual void	checkValidConfigs() const;
		// bool			isValidKeyword(std::string key) const;
		virtual void	updateDefaultSettings();
};

#include "Parser.hpp"
#endif
