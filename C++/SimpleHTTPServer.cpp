#include "SimpleHTTPServer.h"
#include <fstream>

using namespace std;

// chọn handler theo method
std::vector<char> SimpleHTTPServer::select_method(HTTPRequestParser request)
{
    if (request.method == "GET")
        return handle_GET(request);
    else if (request.method == "POST")
        return handle_POST(request);
    else
        return HTTP_501_handler(); // phương thức chưa được cài đặt xử lý
}

// xử lý GET request
std::vector<char> SimpleHTTPServer::handle_GET(HTTPRequestParser request)
{
    return std::vector<char>();
}

// xử lý POST request
std::vector<char> SimpleHTTPServer::handle_POST(HTTPRequestParser request)
{
    return std::vector<char>();
}

// trả về response 404
std::vector<char> SimpleHTTPServer::HTTP_404_handler()
{
    return std::vector<char>();
}
