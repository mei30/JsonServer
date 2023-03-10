#include "ConfigurationService.h"

#include <iostream>
#include <fstream>

#include "configuration.pb.h"

using namespace core;

bool ConfigurationService::read(const std::string config_file_name) noexcept
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	std::fstream config_stream(config_file_name,
			std::ios::in);

	if (!config_stream)
	{
		printf("ConfigurationService::read: Specified file could'nt be opend");
		return false;
	}

	config::Configurations configs;

	if (configs.ParseFromIstream(&config_stream))
	{
		printf("ConfigurationService::read: protobuf couldn't parse input");
		return false;
	}

	server_configuration.server().set_server_address(configs.server_address());
	server_configuration.server().set_server_port(configs.server_port());

	return true;
}

const ServerConfiguration &ConfigurationService::get_server_configuration() const noexcept
{
	return server_configuration;
}
