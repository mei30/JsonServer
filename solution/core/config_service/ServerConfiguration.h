#ifndef SERVERCONFIGURATION_H
#define SERVERCONFIGURATION_H

#include <stdint.h>
#include <string>

#include "AbstractConfiguration.h"

namespace core {

class ServerConfiguration: public AbstractConfiguration
{
public:
	ServerConfiguration() = default;
	ServerConfiguration(uint16_t port, std::string address);

	ServerConfiguration(const ServerConfiguration& other) = default;
	ServerConfiguration(ServerConfiguration&& other) = default;

	ServerConfiguration& operator=(const ServerConfiguration& other) = default;
	ServerConfiguration& operator=(ServerConfiguration&& other) = default;

	~ServerConfiguration() = default;

	void validate() override;

	void set_server_address(const std::string& address);
	void set_server_port(uint16_t port);

private:
	int16_t port;
	std::string address;
};

}

#endif // SERVERCONFIGURATION_H
