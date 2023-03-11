#include "WriterConfiguration.h"

#include <filesystem>

using namespace core;

void WriterConfiguratin::validate()
{
	if (path.empty())
		std::runtime_error("Directory path is invalid");

	if (!std::filesystem::exists(path))
		std::runtime_error("Directory path is not exist");
}

void WriterConfiguratin::set_path(const std::string &path)
{
	this->path = path;
}

void WriterConfiguratin::set_queue_size(uint16_t queue_size)
{
	this->queue_size = queue_size;
}

uint16_t WriterConfiguratin::get_queue_size() const noexcept
{
	return queue_size;
}

std::filesystem::path WriterConfiguratin::get_path() const noexcept
{
	return path;
}
