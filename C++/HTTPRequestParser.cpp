#include "HTTPRequestParser.h"

using namespace std;

HTTPRequestParser::HTTPRequestParser(std::string data)
{
	http_version = "HTTP/1.1";

	parse(data);
}

// parse chuỗi data
void HTTPRequestParser::parse(std::string data)
{
	auto lines = split(data, "\r\n", 1);

	auto request_line = lines.at(0);
	parse_request_line(request_line);

	lines = split(lines.at(1), "\r\n\r\n", 1);
	if (lines.at(1) != "")
		body = lines.at(1);
}

// parse dòng đầu của request
void HTTPRequestParser::parse_request_line(std::string request_line)
{
	auto words = split(request_line, " ");
	method = words.at(0);
	auto tmp = split(words.at(1), "?");
	if (tmp.size() > 1)
	{
		query_string = tmp.at(1);
	}
	uri = tmp.at(0);

	if (words.size() > 2)
	{
		http_version = words[2];
	}
}

// tách chuỗi str thành vector các chuỗi con với delimiter là delim, số lần tách tối đa maxSplit
std::vector<std::string> HTTPRequestParser::split(std::string str, std::string delim, int maxSplit)
{
	if (maxSplit == -1)
		maxSplit = INT_MAX;

	vector<string> tokens;
	int pos;
	while ((pos = str.find(delim)) != string::npos && maxSplit > 0)
	{
		tokens.push_back(str.substr(0, pos));
		int len = str.length() - pos - delim.length();
		str = str.substr(pos + delim.length(), len);
		--maxSplit;
	}
	tokens.push_back(str);

	return tokens;
}
