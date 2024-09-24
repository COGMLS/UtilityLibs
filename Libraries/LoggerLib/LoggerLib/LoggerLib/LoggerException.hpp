#pragma once

#ifndef LOGGER_EXCEPTION_HPP
#define LOGGER_EXCEPTION_HPP

#include "pch.h"

#include <string>
#include <memory>

class LOGGER_LIB_API LoggerException
{
	private:

		std::unique_ptr<std::string> message;
		std::unique_ptr<std::wstring> messageW;

	public:

		LoggerException();

		LoggerException(std::string message);

		LoggerException(std::wstring message);

		LoggerException(const LoggerException& other);

		LoggerException(LoggerException&& other) noexcept;

		~LoggerException();

		const char* what();

		const wchar_t* whatW();
};

#endif // !LOGGER_EXCEPTION_HPP