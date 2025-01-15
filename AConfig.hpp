#ifndef ACONFIG_HPP
# define ACONFIG_HPP
#include <string>
#include <map>

class AConfig
{
    private:
    //simple directive
        std::map<std::string, std::string> error_page; // errorPage 404 /404.html
       const int   workerprocess;

    // block directive
    // http context
        
        bool    absolute_redirect_on; // true
        std::string  default_type; // mime-type; // type{} 으로도 지시가능.
        
        // bool    aio; //false
        // aio 사용시 directio 활성화 시켜줘야 한다.
		// int		directio
        // 기본적으로 NGINX는 파일 전송을 자체 처리하고 파일을 보내기 전에 버퍼에 복사합니다. 
        // sendfile 지시문을 사용하면 데이터를 버퍼에 복사하는 단계가 없어지고 한 파일 설명자에서 다른 파일 설명자로 데이터를 직접 복사할 수 있습니다. 
        // 또는 하나의 빠른 연결이 Worker Process를 완전히 점유하는 것을 방지하려면 sendfile_max_chunk 지시문을 사용하여 단일 sendfile() 호출에서 전송되는 데이터의 양을 제한할 수 있습니다(이 예에서는 1MB로 제한).

		bool	sendfile; //false
        // 단일 호출에서 전송할 수 있는 데이터 양을 제한합니다 sendfile(). 제한이 없으면 빠른 연결 하나가 작업자 프로세스를 완전히 점유할 수 있습니다.
		int		sendfile_max_chunk; // 2m
        // 클라이언트에 응답을 전송하기 위한 시간 초과를 설정합니다. 시간 초과는 전체 응답을 전송하는 것이 아니라 두 개의 연속적인 쓰기 작업 사이에만 설정됩니다. 클라이언트가 이 시간 내에 아무것도 수신하지 못하면 연결이 닫힙니다.
        int     send_timeout; // 60s
        //tcp_nopush 지시문은 sendfile on; 지시문과 함께 사용합니다. 이렇게 하면 NGINX가 sendfile()로 데이터 Chunk를 가져온 직후 하나의 패킷으로 HTTP 응답 헤더를 전송할 수 있습니다.
        bool    tcp_nopush; // false;

        //tcp_nodelay 지시문을 사용하면 원래 느린 네트워크에서 작은 패킷 문제를 해결하기 위해 설계된 Nagle의 알고리즘을 재정의할 수 있습니다. 이 알고리즘은 여러 개의 작은 패킷을 큰 패킷으로 통합하여 200ms의 지연을 두고 패킷을 전송합니다. NGINX static file을 전송할 때 패킷 크기에 관계없이 데이터를 즉시 전송할 수 있습니다. 지연은 온라인 애플리케이션(ssh, 온라인 게임, 온라인 거래 등)에도 영향을 미칩니다. 기본적으로 tcp_nodelay 지시문은 on으로 설정되어 있는데, 이는 Nagle의 알고리즘이 비활성화되어 있음을 의미합니다. 이 지시문은 Keepalive 연결에만 사용하세요.
        bool    tcp_nodelay;

        // 인가받지 않은 요청(로그인 실패에 대해)에 대해 타이밍 공격을 방지하기 위해 지연시간을 둠.
        // int     auth_delay; // 0s

        bool    chunked_transfer_encoding; //on
        // set buffer size to read request body of client. (client body 가 buffer size보다 크면 임시파일에 기록한다.(post action))
        int     client_body_buffer_size; // 16k
        // header의 경우
        int     client_header_buffer_size; // 1k
        // 서버가 클라이언트에게 요청한후 기다리는 시간. 넘을 시 408 code(Request Timeout)
        int     client_body_timeout; // 60s
        int     client_header_timeout; // 60s
        // client request body의 최대 size. 초과시, return 413; 0으로 설정시 확인안함.
        int     client_max_body_size; // 1m
        // request Body를 임시 파일로 가지고 있고 싶을떄 쓰는 설정. 다른 곳에서 바디를 받아 쓰고 싶거나, 디버깅할때 이용(clean은 요청 처리후 임시 파일을 삭제한다.)
        int     client_body_in_file_only; //off (on | clean | off);
        bool    client_body_in_single_buffer; // off
        // client body 임시로 보관할 경로 설정
        bool    client_body_temp_path; 
        // 큰 클라이언트 요청 헤더를 읽는데 사용되는 버퍼의 최대값. 요청 라인이 버퍼 초과시 414(Request-URI too large error), 요청  헤더가 버퍼 초과시, 400(Bad request)
        int     large_client_header_buffers; // 8k

        // symlink을 열때 허용할 것인지.
        bool    disable_symlinks;    // off
        // GET / HEAD 가 아닌 메소드일 경우, GET 으로 바꿔주는 과정이 필요하다.
        // map<int, string> errorPage;

        // 잘못 동작하는 브라우저에 대해 비활성화할 수 있음. Safari로 설정하면 Safari를 비롯한 mac에 있는 browser에 대해 연결을 끊을 수 있다. none은 모두 지원.
        std::string  keep_alive_disable; // msie6, 

    // server context
        std::string  server_name; // ""
        // keep alive 클라이언트 연결이 서버측에서 열려있는 시간제한을 설정. 
        int keep_alive_timeout;
        // keep alive 연결을 통해 요청을 처리할 수 있는 최대 시간 제한. 이 시간에 도달하면 후속 요청 처리에 따라 연결 닫음.
        int keep_alive_time;
        // keep alive 연결을 통해 제공될 수 있는 최대 요청 수
        int keep_alive_requests; //1000
        int keep_cache_connection_alive;

        int connect_timeout;
        int read_timeout;
    public:
        AConfig(char *file);
        AConfig(const AConfig& other);
        ~AConfig();
        AConfig  &operator=(const AConfig& other);
};

#endif