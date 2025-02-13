#include "AppConfig.hpp"

AppConfig	*AppConfig::mp_config = NULL;

AppConfig::AppConfig(std::string file_cf): m_config(file_cf) { }

AppConfig::~AppConfig() {
	if (mp_config)
		delete mp_config;
	MainConfig::deleteConfig();
	ServerConfig::deleteConfig();
	LocationConfig::deleteConfig();
}

AppConfig	*AppConfig::getInstance(std::string file_cf) {
	if (!mp_config)
		mp_config = new AppConfig(file_cf);
	return mp_config;
}

std::string	AppConfig::getter(std::string target) const {
	// return m_conf.AConfig::find(target);
	return m_config.AConfig::find(target);
}

std::string	AppConfig::getter(std::string server_name, std::string target) const {
	return m_config.find(server_name, target);
}

std::string	AppConfig::getter(std::string server_name, std::string api_point, std::string target) const {
	return m_config.find(server_name, api_point, target);
}

ServerConfig	AppConfig::getServerConfig(std::string &server_name) const {
	return m_config.findServer(server_name);
}

// void	AppConfig::checkKey(std::string key, const AConfig &config) const {
// 	MainConfig		*is_main;
// 	ServerConfig	*is_server;
// 	LocationConfig	*is_location;

// 	is_main = dynamic_cast<MainConfig*>(const_cast<AConfig*>(&config));
// 	is_server = dynamic_cast<ServerConfig*>(const_cast<AConfig*>(&config));
// 	is_location = dynamic_cast<LocationConfig*>(const_cast<AConfig*>(&config));
// 	if (is_main)
// 		is_main->AConfig::find(key);
// 	else if (is_server)
// 		is_server->AConfig::find(key);
// 	else if (is_location)
// 		is_location->find(key);
// }