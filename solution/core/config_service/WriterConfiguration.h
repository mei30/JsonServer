#ifndef WRITERCONFIGURATION_H
#define WRITERCONFIGURATION_H

#include <cstdint>
#include <string>
#include <filesystem>

#include "AbstractConfiguration.h"

namespace core {

class WriterConfiguratin: public AbstractConfiguration
{
public:
	WriterConfiguratin() = default;

	WriterConfiguratin(const WriterConfiguratin& other) = default;
	WriterConfiguratin(WriterConfiguratin&& other) = default;

	WriterConfiguratin& operator=(const WriterConfiguratin& other) = default;
	WriterConfiguratin& operator=(WriterConfiguratin&& other) = default;

	~WriterConfiguratin() = default;

	void validate() override;

	void set_path(const std::string& path);
	void set_queue_size(uint16_t queue_size);

	uint16_t get_queue_size() const noexcept;
	std::filesystem::path get_path() const noexcept;

private:
	int16_t queue_size;
	std::filesystem::path path;
};

}

#endif // WRITERCONFIGURATION_H
