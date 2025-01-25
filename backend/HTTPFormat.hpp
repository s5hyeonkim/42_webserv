#ifndef HTTPFORMAT_HPP
# define HTTPFORMAT_HPP
#include <string>

//https://for-earth88.tistory.com/30
typedef struct s_http_request {
	std::string	req_line, header, empty_line, body;
}	t_req;

typedef struct s_request_form {
	std::string	method, end_point, http_ver;
	std::string	host, user_agent, accept, accept_lang, accept_encode, accept_charset;
	std::string	keep_alive, connection, cookie, pragma, cache_control; 
}	t_reqform;

typedef struct s_http_response {
	std::string status_line, header, empty_line, body;
}	t_resform;

typedef struct s_response_form {
	std::string status_line, header, empty_line, body;
}	t_resform;

class HTTPFormat
{
	private:
		std::string	m_host;
		std::string	m_user_agent;
		std::string	content_type;
	public:
		HTTPFormat(/* args */);
		~HTTPFormat();
		std::string	makeRequestForm(std::string lines);
		std::string	makeResponseForm(std::string lines);
		std::string	makeReponseHeader(std::string body);
		void		handleRequestForm(std::string lines);
		void		handleResponseForm(std::string lines);
};

#endif