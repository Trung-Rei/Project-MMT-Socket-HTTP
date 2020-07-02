#pragma once
#include "BaseHTTPServer.h"

/*

Cài đặt http server cụ thể theo yêu cầu đồ án
Bao gồm 2 phương thức GET và POST

*/
class SimpleHTTPServer :
    public BaseHTTPServer
{
public:
    SimpleHTTPServer(short port) : BaseHTTPServer(port) {}

    std::vector<char> select_method(HTTPRequestParser request);

    std::vector<char> handle_GET(HTTPRequestParser request);
    std::vector<char> handle_POST(HTTPRequestParser request);

    std::vector<char> HTTP_404_handler();
};

