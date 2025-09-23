#pragma once

#ifndef TOKEN_DEBUGGER_HPP
#define TOKEN_DEBUGGER_HPP

#ifdef WIN32
	#ifdef VERSION_LIB_EXPORTS
		#define VERSION_LIB_API __declspec(dllexport)
	#else
		#define VERSION_LIB_API __declspec(dllimport)
	#endif //!VERSION_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef VERSION_LIB_EXPORTS
			#define VERSION_LIB_API __attribute__((visibility("default")))
		#else
			#define VERSION_LIB_API __attribute__((visibility("default")))
		#endif //!VERSION_LIB_EXPORTS
	#else
		#ifdef VERSION_LIB_EXPORTS
			#define VERSION_LIB_API
		#else
			#define VERSION_LIB_API
		#endif //!VERSION_LIB_EXPORTS
	#endif
#endif // !WIN32

#include "../ExperimentalFeatures.hpp"

#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER)

#include <vector>
#include <string>
#include <memory>

#define VERSION_LIB_TOKEN_DEBUGGER_MAX_SIZE 80	// Default maximum size of vector/deque used to store the log entries

namespace VersionLib
{
	namespace Debugger
	{
		class VERSION_LIB_API DbgToken
		{
			private:

				unsigned int dbg_max_entries = 0;
				unsigned int dbg_entries = 0;
				bool overwrite = false;
				std::unique_ptr<std::vector<std::string>> pDbgEntries;

			public:

				//
				// Constructors:
				//

				DbgToken (unsigned int dbgMaxEntries, bool overwrite);

				//
				// Destructor:
				//

				~DbgToken();

				//
				// Operators:
				//

				VersionLib::Debugger::DbgToken& operator= (const VersionLib::Debugger::DbgToken& other);

				VersionLib::Debugger::DbgToken& operator= (VersionLib::Debugger::DbgToken&& other) noexcept;

				//
				// Methods:
				//

				/**
				 * @brief Insert a new log entry
				 * @param entry String value to store in logger
				 */
				void push_log (std::string entry);

				/**
				 * @brief Export the log entries and clear the internal logger
				 * @return Return a vector of strings managed by a unique pointer.
				 * @note The unique pointer is the internal log, exported to make it accessible to write or access the data. The internal pointer is swapped by a new one and the internal counter is zeroed.
				 */
				std::unique_ptr<std::vector<std::string>> export_log();
		};
	}
}

#endif // !(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY && !VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER && VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER)

#endif // !TOKEN_DEBUGGER_HPP