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
		static void		addEvent(int fd, int filter, int flags);
		static void		removeEvent(int fd, int filter);
};

#endif