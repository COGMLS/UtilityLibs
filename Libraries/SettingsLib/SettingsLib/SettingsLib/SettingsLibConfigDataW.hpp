#pragma once 

#ifndef SETTINGS_LIB_CONFIG_DATA_W_HPP
#define SETTINGS_LIB_CONFIG_DATA_W_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32



#endif //! SETTINGS_LIB_CONFIG_DATA_W_HPP