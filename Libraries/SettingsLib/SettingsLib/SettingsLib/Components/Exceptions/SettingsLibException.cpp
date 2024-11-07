#include "SettingsLibException.hpp"

SettingsLib::Types::GeneralException::GeneralException() noexcept
{
	this->exception_msg = "";
}

SettingsLib::Types::GeneralException::GeneralException(std::string exceptMsg)
{
	this->exception_msg = exceptMsg;
}

SettingsLib::Types::GeneralException::GeneralException(const char *exceptMsg)
{
	this->exception_msg = exceptMsg;
}

SettingsLib::Types::GeneralException::GeneralException(const SettingsLib::Types::GeneralException &other) noexcept
{
	this->exception_msg = other.exception_msg;
}

SettingsLib::Types::GeneralException::~GeneralException()
{
}

SettingsLib::Types::GeneralException &SettingsLib::Types::GeneralException::operator=(const SettingsLib::Types::GeneralException &other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->exception_msg = other.exception_msg;

	return *this;
}

const char *SettingsLib::Types::GeneralException::what() const noexcept
{
    return this->exception_msg.c_str();
}
