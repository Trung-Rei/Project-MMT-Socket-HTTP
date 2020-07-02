#include "TCPServer.h"
#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

// khởi tạo để lắng nghe tại PORT
TCPServer::TCPServer(short port)
{
	_port = port;
}

// Bắt đầu server
void TCPServer::start()
{
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(_port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);

	cout << "Listening at port " << _port << endl;

	// Wait for a connection
	while (true)
	{
		sockaddr_in client;
		int clientSize = sizeof(client);

		SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

		char host[NI_MAXHOST];		// Client's remote name
		char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

		ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
		ZeroMemory(service, NI_MAXSERV);

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			cout << host << " connected on port " << service << endl;
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			cout << host << " connected on port " <<
				ntohs(client.sin_port) << endl;
		}

		vector<char> data(4096);
		char* buf = data.data();

		ZeroMemory(buf, 4096);

		// Wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		data.resize(bytesReceived);

		// Xử lý dữ liệu
		vector<char> response = handle_request(data);

		// Send message back to client
		send(clientSocket, response.data(), response.size(), 0);

		// Close the socket
		closesocket(clientSocket);
	}
}

// Xử lý request từ client (cài đặt chi tiết ở các class kế thừa)
std::vector<char> TCPServer::handle_request(std::vector<char> data)
{
	return data;
}
