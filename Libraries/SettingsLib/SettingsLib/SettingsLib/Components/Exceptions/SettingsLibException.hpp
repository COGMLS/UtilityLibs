#pragma once

#ifndef SETTINGS_LIBRARY_EXCEPTIONS_HPP
#define SETTINGS_LIBRARY_EXCEPTIONS_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef SETTINGS_LIB_EXPORTS
			#define SETTINGS_LIB_API __attribute__((visibility("default")))
		#else
			#define SETTINGS_LIB_API __attribute__((visibility("default")))
		#endif //!SETTINGS_LIB_EXPORTS
	#else
		#ifdef SETTINGS_LIB_EXPORTS
			#define SETTINGS_LIB_API
		#else
			#define SETTINGS_LIB_API
		#endif //!SETTINGS_LIB_EXPORTS
	#endif
#endif // !WIN32

#include "SettingsLibExperimentalFeatures.hpp"

#include <exception>
#include <string>
#include <cstring>
#include <memory>
#include <stdexcept>

namespace SettingsLib
{
	namespace Types
	{
		class GeneralException : public std::exception
		{
			protected:

				std::string exception_msg;

			public:

				GeneralException() noexcept;

				GeneralException (std::string exceptMsg);

				GeneralException (const char* exceptMsg);

				GeneralException (const SettingsLib::Types::GeneralException& other) noexcept;

				~GeneralException();

				SettingsLib::Types::GeneralException& operator= (const SettingsLib::Types::GeneralException& other) noexcept;

				const char* what() const noexcept;
		};
	}
}

#endif // !SETTINGS_LIBRARY_EXCEPTIONS_HPP