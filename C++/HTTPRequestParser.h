#pragma once
#include <string>
#include <map>
#include <vector>

// class parse request từ chuỗi
class HTTPRequestParser
{
public:
	std::string method; // phương thức
	std::string uri; // đường dẫn yêu cầu
	std::string query_string; // chuỗi query
	std::string http_version; // mặc định là HTTP/1.1 nếu request ko để
	std::map<std::string, std::string> headers; // các header của request
	std::string body; // phần thân request

	HTTPRequestParser(std::string data);

	void parse(std::string data);

	void parse_request_line(std::string request_line);

private:
	std::vector<std::string> split(std::string str, std::string delim, int maxSplit = -1);
};

