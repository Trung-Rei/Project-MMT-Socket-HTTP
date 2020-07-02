#pragma once
#include <vector>

// server TCP
// cài các chức năng cơ bản của 1 TCP server
// không sử dụng trực tiếp class này, sử dụng các class kế thừa
class TCPServer
{
private:
	short _port;
public:
	TCPServer(short port);

	void start();
	virtual std::vector<char> handle_request(std::vector<char> data);
};

