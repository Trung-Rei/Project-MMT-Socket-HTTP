#include "BaseHTTPServer.h"

using namespace std;

// nhận request từ data, trả về response
std::vector<char> BaseHTTPServer::handle_request(std::vector<char> data)
{
	HTTPRequestParser* request;
	try
	{
		// parse request từ data
		request = new HTTPRequestParser(string(data.begin(), data.end()));
	}
	catch (...) // request ko hợp lệ
	{
		return HTTP_400_handler(); 
	}

	// chọn hàm xử lý yêu cầu cụ thể request
	auto response = select_method(*request);
	delete request;
	return response;
}

// trả về chuỗi response line theo statusCode
std::string BaseHTTPServer::response_line(int statusCode)
{
	string reason = statusCodes[statusCode];
	auto ret = "HTTP/1.1 " + to_string(statusCode) + " " + reason + "\r\n";
	return ret;
}

// trả về chuỗi response headers
std::string BaseHTTPServer::response_headers(std::map<std::string, std::string> extraHeaders)
{
	auto headers_copy = map<string, string>(headers);
	if (!extraHeaders.empty()) // thêm các header khác nếu có
	{
		headers_copy.insert(extraHeaders.begin(), extraHeaders.end());
	}

	string headers = "";

	for (auto i : headers_copy)
	{
		headers += i.first + ": " + i.second + "\r\n";
	}
	return headers;
}

// response với statusCode = 400
std::vector<char> BaseHTTPServer::HTTP_400_handler()
{
	auto responseLine = response_line(400);
	auto responseHeaders = response_headers(map<string, string>());
	string blankLine = "\r\n";

	auto response = responseLine + responseHeaders + blankLine;
	return vector<char>(response.begin(), response.end());
}

// response với statusCode = 501
std::vector<char> BaseHTTPServer::HTTP_501_handler()
{
	auto responseLine = response_line(501);
	auto responseHeaders = response_headers(map<string, string>());
	string blankLine = "\r\n";

	auto response = responseLine + responseHeaders + blankLine;
	return vector<char>(response.begin(), response.end());
}
