#pragma once 

#ifndef SETTINGS_LIB_ERROR_CODES_HPP
#define SETTINGS_LIB_ERROR_CODES_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32

namespace SettingsLib
{
	namespace ErrorCodes
	{
		
	}
}

#endif //! SETTINGS_LIB_ERROR_CODES_HPP