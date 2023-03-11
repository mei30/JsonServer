#ifndef CONFIGURATION_SERVICE_H
#define CONFIGURATION_SERVICE_H

#include <string>
#include <list>
#include <tuple>

#include "ServerConfiguration.h"
#include "WriterConfiguration.h"

namespace core {

class ConfigurationService
{
public:
	ConfigurationService() = default;

	ConfigurationService(const ConfigurationService& other) = default;
	ConfigurationService(ConfigurationService&& other) = default;

	ConfigurationService& operator=(const ConfigurationService& other) = default;
	ConfigurationService& operator=(ConfigurationService&& other) = default;

	~ConfigurationService() = default;

	bool read(const std::string config_file_name) noexcept;

	const ServerConfiguration& get_server_configuration() const noexcept;
	const WriterConfiguratin& get_writer_configuration() const noexcept;

private:
	ServerConfiguration server_configuration;
	WriterConfiguratin writer_configuration;
};


}

#endif
