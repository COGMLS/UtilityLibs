#pragma once

#ifndef LOGGER_LIB_DEF_HPP
#define LOGGER_LIB_DEF_HPP

	#ifdef LOGGER_EXPORTS
		#define LOGGER_LIB_API __declspec(dllexport)
	#else
		#define LOGGER_LIB_API __declspec(dllimport)
	#endif //!LOGGER_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)

#endif //!LOGGER_LIB_DEF_HPP