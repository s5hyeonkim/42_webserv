#ifndef HTTPMSG_HPP
# define HTTPMSG_HPP

# include <iostream>
# include <string>
# include <map>

typedef enum e_read_state {
	READ_LINE,
	READ_HEAD,
	READ_BODY,
	COMPLETE
}	t_read_state;

typedef enum e_http_status_code {
	BAD_REQUEST = 400,
	REQUEST_TIMEOUT = 408,
	INTERNAL_SERVER_ERROR = 500,
	SERVICE_UNAVAILABLE = 503
}	t_http_status_code;

typedef std::map<std::string, std::string> t_msg_map;

class HttpMsg {
	private:
		t_msg_map		m_startline, m_head, m_body;
		t_read_state	m_read_status;
	public:
					HttpMsg();
		virtual		~HttpMsg();
		// void		splitKeyValue(const std::string &buffer, bool reqres);
		std::string	getChunck(const std::string &buffer, std::string delim, size_t &begin, size_t &end);
		void		splitline(const std::string &line, bool reqres);
		
		//status code 
		static int	getHttpStatusCode();
		//parsing - return : http status code 
		int			setRequestLine(const std::string &request);

		//valid
		int			validRequestMsg(const std::string &request);
		int			validRequestStartline(const std::string &line);
		//getter
		t_read_state getReadStatus();
		//setter
		void		setReadStatus(t_read_state new_status);
		int			setRequestMsg(const std::string &line);
};

#endif