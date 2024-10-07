#pragma once

#ifndef LOGGER_EXCEPTION_HPP
#define LOGGER_EXCEPTION_HPP

#ifdef WIN32
	#ifdef LOGGER_EXPORTS
		#define LOGGER_LIB_API __declspec(dllexport)
	#else
		#define LOGGER_LIB_API __declspec(dllimport)
	#endif //!LOGGER_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef LOGGER_EXPORTS
			#define LOGGER_LIB_API __attribute__((visibility("default")))
		#else
			#define LOGGER_LIB_API __attribute__((visibility("default")))
		#endif //!LOGGER_EXPORTS
	#else
		#ifdef LOGGER_EXPORTS
			#define LOGGER_LIB_API
		#else
			#define LOGGER_LIB_API
		#endif //!LOGGER_EXPORTS
	#endif
#endif // !WIN32

#ifdef WIN32
#include "pch.h"
#endif // !WIN32

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