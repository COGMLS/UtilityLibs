#include "LoggerException.hpp"

LoggerException::LoggerException()
{
	this->message.reset(nullptr);
	this->messageW.reset(nullptr);
}

LoggerException::LoggerException(std::string message)
{
	this->message.reset(new std::string(message));
	this->messageW.reset(nullptr);
}

LoggerException::LoggerException(std::wstring message)
{
	this->message.reset(nullptr);
	this->messageW.reset(new std::wstring(message));
}

LoggerException::LoggerException(const LoggerException &other)
{
	if (other.message)
	{
		this->message.reset(new std::string());
		*this->message = *other.message;
		this->messageW.reset(nullptr);
	}

	if (other.messageW)
	{
		this->message.reset(nullptr);
		this->messageW.reset(new std::wstring());
		*this->messageW = *other.messageW;
	}
}

LoggerException::LoggerException(LoggerException &&other) noexcept
{
	if (other.message)
	{
		this->message.swap(other.message);
		this->messageW.reset(nullptr);
	}

	if (other.messageW)
	{
		this->message.reset(nullptr);
		this->messageW.swap(other.messageW);
	}
}

LoggerException::~LoggerException()
{
	if (this->message)
	{
		this->message->~basic_string();
		this->message.reset(nullptr);
	}

	if (this->messageW)
	{
		this->messageW->~basic_string();
		this->messageW.reset(nullptr);
	}
}

const char *LoggerException::what()
{
	if (this->message)
	{
		return this->message->c_str();
	}

    return nullptr;
}

const wchar_t *LoggerException::whatW()
{
	if (this->messageW)
	{
		return this->messageW->c_str();
	}
	
    return nullptr;
}
