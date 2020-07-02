#include "SimpleHTTPServer.h"

int main()
{
	SimpleHTTPServer server(80);
	server.start();

	return 0;
}