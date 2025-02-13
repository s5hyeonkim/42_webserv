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
