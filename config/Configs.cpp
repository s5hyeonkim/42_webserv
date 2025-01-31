#include "Configs.hpp"

Configs	*Configs::mp_config = NULL;

Configs::Configs(std::string file_cf): config(MainConfig(file_cf)) { }

Configs::~Configs() {
	if (mp_config)
		delete mp_config;
}

Configs	*Configs::getInstance(std::string file_cf) {
	if (!mp_config)
		mp_config = new Configs(file_cf);
	return mp_config;
}

