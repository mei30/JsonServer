#include "ConfigurationService.h"

#include <iostream>
#include <fstream>

#include "configuration.pb.h"
#include "Logger.h"

using namespace core;
using namespace CPlusPlusLogging;

bool ConfigurationService::read(const std::string config_file_name) noexcept
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	std::fstream config_stream(config_file_name,
			std::ios::in);

	if (!config_stream)
	{
		LOG_ERROR("ConfigurationService::read: Specified file could'nt be opend");
		return false;
	}

	config::Configurations configs;

	if (configs.ParseFromIstream(&config_stream))
	{
		LOG_ERROR("ConfigurationService::read: protobuf couldn't parse input");
		return false;
	}

	server_configuration.set_server_address(configs.server().server_address());
	server_configuration.set_server_port(configs.server().server_port());
	writer_configuration.set_path(configs.writer().file_path());
	writer_configuration.set_queue_size(configs.writer().queue_size());

	return true;
}

const ServerConfiguration &ConfigurationService::get_server_configuration() const noexcept
{
	return server_configuration;
}

const WriterConfiguratin &ConfigurationService::get_writer_configuration() const noexcept
{
	return writer_configuration;
}
