#pragma once

#ifndef SETTINGS_LIB_DEF_HPP
#define SETTINGS_LIB_DEF_HPP

	#ifdef SETTINGSLIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGSLIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)

#endif //!SETTINGS_LIB_DEF_HPP