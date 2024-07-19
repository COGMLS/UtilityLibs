#pragma once 

#ifndef SETTINGS_LIB_TOOLS_HPP
#define SETTINGS_LIB_TOOLS_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32

#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <stdexcept>

#include "SettingsLibDefinitions.hpp"
#include "SettingsLibErrorCodes.hpp"
#include "SettingsLibDataTypes.hpp"

namespace SettingsLib
{
	namespace Tools
	{
		/**
		 * @brief Store the file stream into the memory using a vector, allowing manipulate the line without change the file
		 * @param fs File stream object. The file need be already opened.
		 * @param vMemStore Vector to store in memory.
		 * @param readLines Number of lines to store. If zero is passed, all lines from current position will be stored. If a number bigger of lines was passed, the function will send all lines to the vMemStore.
		 * @param resetPosBeforeOp Reset the position before starting the operation. Otherwise, will not take the full file content.
		 * @param seekBeginPostOp Back to the start position.
		 * @return 0 for a successful operation.
		 * @return 1 if the file stream is not open.
		 * @return 2 if fs is a nullptr.
		 * @return 3 if the VMemStore is a nullptr.
		 * @return 4 if an unknown error occur.
		 */
		int storeFstream2Memory (std::fstream* fs, std::vector<std::string>* vMemStore, unsigned long long readLines, bool resetPosBeforeOp, bool seekBeginPostOp);

		/**
		 * @brief Store the vector memory into the file stream
		 * @param fs File stream object. The file need be already opened.
		 * @param vMemStore Vector with line stored in memory.
		 * @param resetPosBeforeOp Reset the position before starting the operation. Otherwise, will not take the full file content.
		 * @param seekBeginPostOp Back to the start position.
		 * @return 0 for a successful operation.
		 * @return 1 if the file stream is not open.
		 * @return 2 if fs is a nullptr.
		 * @return 3 if the vMemStore is a nullptr.
		 * @return 4 if an unknown error occur.
		 */
		int storeMemory2FStream (std::fstream* fs, std::vector<std::string>* vMemStore, bool resetPosBeforeOp, bool seekBeginPostOp);
	}
}

#endif //! SETTINGS_LIB_TOOLS_HPP