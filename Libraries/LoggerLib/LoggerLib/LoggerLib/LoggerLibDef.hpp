#pragma once

#ifndef LOGGER_LIB_DEF_HPP
#define LOGGER_LIB_DEF_HPP

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

#endif //!LOGGER_LIB_DEF_HPP