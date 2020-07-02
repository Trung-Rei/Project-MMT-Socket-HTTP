#pragma once
#include "TCPServer.h"
#include <map>
#include <string>
#include "HTTPRequestParser.h"

// class HTTP server cơ bản kế thừa TCP server class
// cài đặt chi tiết HTTP server, xử lý 1 số response cơ bản
// chưa cài đặt các method cụ thể(cài đặt chi tiết theo yêu cầu cụ thể của server
// ở các class kế thừa)
// không sử dụng trực tiếp class này
class BaseHTTPServer :
    public TCPServer
{
public:
    std::map<std::string, std::string> headers; // các header của response
    std::map<int, std::string> statusCodes;

    BaseHTTPServer(short port) : TCPServer(port)
    {
        headers["Server"] = "Rei-Server";
        headers["Connection"] = "close";

        statusCodes[200] = "OK";
        statusCodes[400] = "Bad Request";
        statusCodes[404] = "Not Found";
        statusCodes[301] = "Moved Permanently";
        statusCodes[303] = "See Other";
        statusCodes[501] = "Not Implemented";
    }

    std::vector<char> handle_request(std::vector<char> data);
    virtual std::vector<char> select_method(HTTPRequestParser request) = 0;

    std::string response_line(int statusCode);
    std::string response_headers(std::map<std::string, std::string> extraHeaders);

    std::vector<char> HTTP_400_handler();
    std::vector<char> HTTP_501_handler();
};

