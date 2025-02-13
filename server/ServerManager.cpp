#include "ServerManager.hpp"

/* config */
#define PRX_IP "127.0.0.1"
#define WEB_IP "127.0.0.1"
#define PRX_PORT 2424
#define WEB_PORT 4242
#define PRX_QUE_SIZE 20
#define WEB_QUE_SIZE 20
#define KEVENT_CNT 100
#define PRX_REQUEST_SIZE 10000
#define WEB_REQUEST_SIZE 10000
#define PRX_RESPONSE_SIZE 10000
#define WEB_RESPONSE_SIZE 10000
#define PRX_SNDBUF 1000
#define WEB_SNDBUF 1000
#define PRX_RCVBUF 1000
#define WEB_RCVBUF 1000


uint32_t ipToInt(const std::string& ip) {
	uint32_t ret;

	inet_pton(AF_INET, ip.c_str(), &ret);
	return (ret);
}

t_server_info	getInfoProxy() {
	t_server_info info;

	info.name = "localhost";
	info.ip = ipToInt(PRX_IP);
	info.port = PRX_PORT;
	info.que_size = PRX_QUE_SIZE;
	info.so_sndbuf = PRX_SNDBUF;
	info.so_rcvbuf = PRX_RCVBUF;
	return (info);
}

t_server_info	getInfoWeb() {
	t_server_info info;

	info.name = "localhost";
	info.ip = ipToInt(WEB_IP);
	info.port = WEB_PORT;
	info.que_size = WEB_QUE_SIZE;
	info.so_sndbuf = WEB_SNDBUF;
	info.so_rcvbuf = WEB_RCVBUF;
	return (info);
}

/* ServerManager */
ServerManager::ServerManager() \
: kq(Kqueue::getInstance()->getKqueue()),proxy(getInfoProxy()), web(getInfoWeb()) {
	ptow_fd = proxy.addNewConnect(getInfoWeb());
	proxy_fd = proxy.getServerInfo().sockfd;
	// web_fd = web.getServerInfo().sockfd;
	wtop_fd = web.addNewAccept(web.getServerInfo().sockfd);
	Kqueue::addEvent(proxy_fd, EVFILT_READ, EV_ADD | EV_CLEAR);
	Kqueue::addEvent(ptow_fd, EVFILT_READ, EV_ADD | EV_CLEAR);
	Kqueue::addEvent(wtop_fd, EVFILT_READ, EV_ADD | EV_CLEAR);
	std::cout << "ptow_fd: " << ptow_fd << std::endl; 
	std::cout << "wtop_fd: " << ptow_fd << std::endl; 
	std::cout << "proxy_fd: " << proxy_fd << std::endl; 
	// std::cout << "web_fd: " << web_fd << std::endl; 
}

ServerManager::~ServerManager() {
	
}

void	ServerManager::runServer() {
	size_t		cycle;

	cycle = 0;
	while (true) {
		std::cout << "hello Server Loop" << std::endl;
		std::cout << "========================== Event Cycle " << cycle++ << " ==========================" << std::endl;
		handleEvent();
		// sleep(1);
	}
}

void	ServerManager::handleEvent() {
	struct kevent	events[KEVENT_CNT];
	int				active_n, idx, now_fd, new_client;

	// Kqueue::addEvent(proxy_fd, EVFILT_READ, EV_ADD);
	std::cout << "hello Event Loop. kq is " << kq << std::endl;
	active_n = kevent(kq, NULL, 0, events, KEVENT_CNT, NULL);
	std::cout << "active_n:" << active_n << std::endl;
	for (idx = 0; idx < active_n; ++idx) {
		now_fd = events[idx].ident;
		if (now_fd == proxy_fd) {
			std::cout << "now_fd is proxy fd: " << now_fd << std::endl;
			// 새로운 클라이언트 생성
			Kqueue::addEvent(proxy.addNewAccept(now_fd), EVFILT_READ, EV_ADD | EV_CLEAR);
		}
		else if (now_fd == wtop_fd) {
			std::cout << "now_fd is web fd: " << now_fd << std::endl;
			// 2. web에서 proxy로부터 요청을 받음 > 응답 생성 > web으로 전송
			web.sendToClient(now_fd, now_fd);
		}
		else if (now_fd == ptow_fd) {
			std::cout << "now_fd is proxy's connect fd: " << now_fd << std::endl;
			// 3. proxy에서 web으로부터 응답을 받음 > client로 전송 
			proxy.sendToClient(now_fd, new_client);
		}
		else if (proxy.getAcceptInfoMap().find(now_fd) != proxy.getAcceptInfoMap().end()) {
			std::cout << "now_fd is proxy's accept fd: " << now_fd << std::endl;
			new_client = now_fd;
			std::cout << new_client << std::endl;
			// 1. proxy에서 client로부터 요청을 받음 > web으로 요청 전달 
			proxy.sendToServer(now_fd, ptow_fd);
		}
	}
}
