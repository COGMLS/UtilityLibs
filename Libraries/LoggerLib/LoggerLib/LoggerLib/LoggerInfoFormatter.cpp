#include "LoggerInfoFormatter.hpp"

LogFormatToken::LogFormatToken()
{
	this->id = LogFormatId::Unknown;
	this->info = "";
}

LogFormatToken::LogFormatToken(LogFormatId id, std::string info)
{
	this->id = id;
	this->info = info;
}

LogFormatToken::LogFormatToken(const LogFormatToken &other)
{
	this->id = other.id;
	this->info = other.info;
}

LogFormatToken::LogFormatToken(LogFormatToken &&other) noexcept
{
	this->id = std::move(other.id);
	this->info = std::move(other.info);
}

LogFormatToken::~LogFormatToken()
{
}

LogFormatToken &LogFormatToken::operator=(const LogFormatToken &other)
{
    this->id = other.id;
	this->info = other.info;
	return *this;
}

LogFormatToken &LogFormatToken::operator=(LogFormatToken &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	this->id = std::move(other.id);
	this->info = std::move(other.info);

	return *this;
}

std::string LogFormatToken::operator+(const LogFormatToken &other)
{
    return other.info + this->info;
}

std::string LogFormatToken::operator+(const std::string &str)
{
    return str + this->info;
}

LogFormatId LogFormatToken::getId()
{
    return this->id;
}

std::string LogFormatToken::getInfo()
{
    return this->info;
}

void LogFormat::createFormat(std::string &format)
{
	for (size_t i = 0; i < format.size(); i++)
	{

	}
}

LogFormat::LogFormat()
{
	
}

LogFormat::LogFormat(std::string format, std::string emptyDataReplacer)
{
	
}

LogFormat::LogFormat(const LogFormat &other)
{
	this->format = other.format;
}

LogFormat::LogFormat(LogFormat &&other) noexcept
{
	this->format = std::move(other.format);
}

LogFormat::~LogFormat()
{
}

LogFormat &LogFormat::operator=(const LogFormat &other)
{
    this->format = other.format;
	return *this;
}

LogFormat &LogFormat::operator=(LogFormat &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}
	this->format = std::move(other.format);
	return *this;
}

std::string LogFormat::formatInfo(std::vector<std::string> info)
{
	std::string formattedInfo = "";

	for (std::string& s : info)
	{

	}

    return formattedInfo;
}
