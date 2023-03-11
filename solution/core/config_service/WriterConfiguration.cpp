#include "WriterConfiguration.h"

#include <filesystem>
#include <iostream>

using namespace core;

void WriterConfiguratin::validate()
{
	printf("validdd\n");
	if (path.empty())
		throw std::runtime_error("Directory path is invalid");

	std::cout << path;
	if (!std::filesystem::exists(path))
		throw std::runtime_error("Directory path is not exist");
}

void WriterConfiguratin::set_path(const std::string &path)
{
	this->path = path;
	validate();
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
