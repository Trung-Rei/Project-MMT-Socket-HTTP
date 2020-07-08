# Hướng dẫn viết 1 HTTP server xử lý yêu cầu đơn giản (C++)
## Kế thừa class BaseHTTPServer
```c++
#pragma once
#include "BaseHTTPServer.h"

class MyHTTPServer :
    public BaseHTTPServer
{
};
```
## Constructor và ghi đè phương thức select_method
### Constructor
```c++
MyHTTPServer(short port) : BaseHTTPServer(port) {}
```
### select_method
Lựa chọn phương thức xử lý theo yêu cầu của **request**
```c++
std::vector<char> MyHTTPServer::select_method(HTTPRequestParser request)
{
    if (request.method == "GET")
        return handle_GET(request);
    else if (request.method == "POST")
        return handle_POST(request);
    else if (request.method == "XXX")
        return handle_XXX(request);
    // thêm các phương thức khác nếu có
    else
        return HTTP_501_handler(); // lỗi: phương thức chưa được cài đặt xử lý
}
```
Với **XXX** là tên phương thức của request.
## Các thuộc tính của `HTTPRequestParser request`
```c++
class HTTPRequestParser
{
public:
    std::string method; // phương thức
    std::string uri; // đường dẫn yêu cầu
    std::string query_string; // chuỗi query
    std::string http_version; // mặc định là HTTP/1.1 nếu request ko để
    std::map<std::string, std::string> headers; // các header của request
    std::string body; // phần thân request
  
    /*
    Class's methods
    */
};
```
## Cài đặt phương thức xử lý Status code
Cấu trúc chung:

`std::vector<char> HTTP_XXX_handler(/* các tham số thêm nếu có */);`

Với **XXX** là status code
```c++
std::vector<char> MyHTTPServer::HTTP_XXX_handler()
{
    // phần header cơ bản
    auto responseLine = response_line(XXX);
    auto responseHeaders = response_headers(map<string, string>());
    string blankLine = "\r\n";
    
    // thêm những thứ khác vào response ở đây

    auto response = responseLine + responseHeaders + blankLine;
    return vector<char>(response.begin(), response.end());
    // trả về chuỗi dưới dạng vector
}
```
**Chú ý:** Status code **400** và **501** đã được cài đặt ở **BaseHTTPServer**
## Cài đặt phương thức xử lý Method
Cấu trúc chung:

`std::vector<char> handle_XXX(HTTPRequestParser request);`

Với **XXX** là status code

Cài đặt tương tự các phương thức xử lý Status code.
## Các hàm phát sinh khác
Cài đặt trong **private** hoặc **protected**
## Chạy server
```c++
#include "MyHTTPServer.h"

int main()
{
    MyHTTPServer server(80);
    server.start();

    return 0;
}
```
