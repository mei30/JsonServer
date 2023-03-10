#include "ServerConfiguration.h"

#include <regex>
#include <exception>

using namespace core;

using std::string;
using std::regex;

ServerConfiguration::ServerConfiguration(uint16_t port, string address)
	: port(port)
	, address(address)
{
	validate();
}

void ServerConfiguration::validate()
{
	// We do not need to validate port

	const regex ip_regex(
			"^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$");

	if (!std::regex_search(address, ip_regex))
		std::runtime_error(
					"Entered IP address is invalid Please proivde valid IP Address");
}

void ServerConfiguration::set_server_address(const std::string &address)
{
	this->address = address;
	validate();
}

void ServerConfiguration::set_server_port(uint16_t port)
{
	this->port = port;
}
