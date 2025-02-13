#include "HttpMsg.hpp"

HttpMsg::HttpMsg() {
	memset(&m_startline, 0, sizeof(m_startline));
	memset(&m_head, 0, sizeof(m_head));
	memset(&m_body, 0, sizeof(m_body));
}

HttpMsg::~HttpMsg() {
	
}

//request
/*
<메서드> <요청URL> <버전>
<헤더>

<본문>
*/

//response 
/*
<버전> <상태코드> <사유구절>
<헤더>

<본문>
*/

std::string HttpMsg::getChunck(const std::string &buffer, std::string delim, size_t &begin, size_t &end) {
	std::string line;

	end = buffer.find(delim);
	line = buffer.substr(begin, end - begin);
	begin = end + 1;
	return (line);
}

int	HttpMsg::getHttpStatusCode() {
	int	http_status_code;

	switch (errno) {
		case EINVAL: // 잘못된 인수나 데이터가 전달된 경우
		case EPIPE: // 클라이언트가 소켓을 닫은 상태에서 데이터를 전송하려고 한 경우
			http_status_code = BAD_REQUEST; // Bad Request
			break ;
		case ETIMEDOUT: //요청 시간 초과
		case ECONNRESET: //클라이언트가 비정상적으로 연결을 종료한 경우
			http_status_code = REQUEST_TIMEOUT; // Request Timeout
			break ;
		case ENOMEM: // 메모리가 부족하여 요청을 처리할 수 없는 경우.
			http_status_code = INTERNAL_SERVER_ERROR; // Internal Server Error
			break ;
		case EMFILE: // 서버에서 열 수 있는 파일 디스크립터를 모두 소진
		case ENFILE: // 시스템 전체의 파일 디스크립터 제한 초과
			http_status_code = SERVICE_UNAVAILABLE; //Service Unavailable
			break ;
		default:
			http_status_code = INTERNAL_SERVER_ERROR; //예상하지 못한 에러
			break ;
	}
	return (http_status_code);
}

void HttpMsg::splitline(const std::string &line, bool reqres) {
	std::string	chunck;
	size_t		begin, end, idx;
	std::string key[3] = {"method", "uri", "http_version"};
	// char		*key_res[3] = {"http_version", "status_code", "status_message"};
	(void) reqres;
	begin = 0, end = 0;
	for (idx = 0; idx < 3; ++idx) {
		if (idx != 2)
			chunck = getChunck(line, " ", begin, end);
		else
			chunck = getChunck(line, "\r\n", begin, end);
		m_startline[key[idx]] = chunck;
	}
}


size_t	cntSubstr(const std::string &str, std::string substr) {
	size_t	cnt, pos;

	cnt = 0, pos = 0;
	while ((pos = str.find(substr, pos)) != std::string::npos) {
		++cnt;
		pos += substr.length();
	}
	return (cnt);
}	


int HttpMsg::setRequestMsg(const std::string &request) {
	size_t begin, end;
	std::string line;

	begin = 0, end = 0;
	line = getChunck(request, "\r\n", begin, end);
	if (cntSubstr(line, " ") != 2)
		return (BAD_REQUEST);
	setRequestLine(line);
	return (0);
}

int	HttpMsg::setRequestLine(const std::string &line) {
	std::string	key[3] = {"method", "uri", "http_version"};
	size_t		begin, end, idx;

	begin = 0; end = 0;
	for (idx = 0; idx < 3; ++idx)
		m_startline[key[idx]] = getChunck(line, " ", begin, end);
	return (0);
}

t_read_state	HttpMsg::getReadStatus() {
	return (m_read_status);
}

void HttpMsg::setReadStatus(t_read_state new_status) {
	m_read_status = new_status;
}

int HttpMsg::validRequestMsg(const std::string &request) {
	size_t		begin, end;
	std::string	line;
	
	begin = 0, end = 0;
	line = getChunck(request, "\r\n", begin, end);
	//validstartline

	
	//validheader

	//validbody

	return (0);
}


bool isValidMethod(const std::string& method) {
	const std::string	valid_method[] = {"GET", "POST", "DELETE"};
	size_t				cnt_method;
	
	cnt_method = sizeof(valid_method) / sizeof(valid_method[0]);
	if (std::find(valid_method, valid_method + cnt_method, method) == valid_method + cnt_method)
		return (false);
	return (true);
}


bool isValidHttpVersion(const std::string& version) {
	const std::string	major = "HTTP/";
	std::string			minor;
	size_t				cnt_dot, idx, size;

	if (version.size() < 6 || version.substr(0, 5) != major)
		return (false);
	minor = version.substr(5);
	size = minor.size();
	cnt_dot = 0;
	for (idx = 0; idx < size; ++idx) {
		if (minor[idx] == '.') {
			if (idx == 0 || idx == size - 1)
				return (false);
			++cnt_dot;
			if (cnt_dot > 1)
				return (false);
		}
		else if (!isdigit(minor[idx]))
			return (false);
	}
	return (true);
}

bool isValidUri(const std::string& uri) {
	size_t	idx, size;

	size = uri.size();
	for (idx = 0; idx < size; ++idx) {
		if (!isalpha(uri[idx]))
			return (false);
	}
	return (true);
}

int HttpMsg::validRequestStartline(const std::string &line) {
	size_t		begin, end;
	std::string	chunck;

	if (cntSubstr(line, " ") != 2)
		return (BAD_REQUEST);
	begin = 0, end = 0;
	//method valid
	chunck = getChunck(line, " ", begin, end);
	if (isValidMethod(chunck) == false)
		return (BAD_REQUEST);
	//uri valid
	chunck = getChunck(line, " ", begin, end);
	if (isValidUri(chunck) == false)
		return (BAD_REQUEST);
	//http_version 
	chunck = getChunck(line, " ", begin, end);
	if (isValidHttpVersion(chunck) == false)
		return (BAD_REQUEST);
	return (0);
}
