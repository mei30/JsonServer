#ifndef CONFIGURATION_SERVICE_H
#define CONFIGURATION_SERVICE_H

#include <string>
#include <list>
#include <tuple>

#include "ServerConfiguration.h"

namespace core {

class ConfigurationService
{
public:
//	using LogMessage = std::tuple<google::protobuf::LogLevel, std::string, int,
//			std::string>;  // C++11
//	using LogStack = std::list<LogMessage>;

	ConfigurationService() = default;

	ConfigurationService(const ConfigurationService& other) = default;
	ConfigurationService(ConfigurationService&& other) = default;

	ConfigurationService& operator=(const ConfigurationService& other) = default;
	ConfigurationService& operator=(ConfigurationService&& other) = default;

	~ConfigurationService() = default;

	bool read(const std::string config_file_name) noexcept;

	const ServerConfiguration& get_server_configuration() const noexcept;

private:
	ServerConfiguration server_configuration;
};


}

#endif
