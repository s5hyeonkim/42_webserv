#include "Kqueue.hpp"

Kqueue* Kqueue::mp_instance = NULL;

Kqueue::Kqueue() { }

Kqueue::~Kqueue()
{
	if (mp_instance)
		delete mp_instance;	
}

Kqueue* Kqueue::getInstance() {
	if (!mp_instance)
	{
		mp_instance = new Kqueue();
		mp_instance->kq = kqueue();
		if (mp_instance->kq == -1)
			Exception::handleSystemError(errno);
	}
	return (mp_instance);
}

int Kqueue::getKqueue() {
	return (mp_instance->kq);
}

#include <iostream>
void Kqueue::addEvent(int fd, int filter, int flags) {
	struct kevent event;

	EV_SET(&event, fd, filter, flags, 0, 0, NULL);
	if (kevent(mp_instance->kq, &event, 1, NULL, 0, NULL) == -1)
		Exception::handleSystemError(errno);
	std::cout << "you add Event " << fd << std::endl;
}

void Kqueue::removeEvent(int fd, int filter) {
	struct kevent event;

	EV_SET(&event, fd, filter, EV_DELETE, 0, 0, NULL);
	if (kevent(mp_instance->kq, &event, 1, NULL, 0, NULL) == -1)
		Exception::handleSystemError(errno);
}
