#ifndef KQUEUE_HPP
# define KQUEUE_HPP

#include <sys/event.h>
#include <stdexcept> 
#include "../exception/Exception.hpp"

class Kqueue {
	private:
		static Kqueue	*mp_instance;
		int				kq;
						Kqueue();
						~Kqueue();
	public:
		static Kqueue	*getInstance();
		static int		getKqueue();
};

#endif