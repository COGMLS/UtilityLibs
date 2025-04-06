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
		int storeFstream2Memory (std::wfstream* fs, std::vector<std::wstring>* vMemStore, unsigned long long readLines, bool resetPosBeforeOp, bool seekBeginPostOp);

		/**
		 * @brief Store the vector memory into the file stream
		 * @param fs File stream object. The file need be already opened.
		 * @param vMemStore Vector with line stored in memory.
		 * @param resetPosBeforeOp Reset the position before starting the operation. Otherwise, will not take the full file content.
		 * @param seekBeginPostOp Back to the start position.
		 * @param newLineByVecEntry Insert a new line in the file to each vector entry.
		 * @param lastLineEmpty If the new line insertion is active, define if a empty line will be added in the end of the file.
		 * @return 0 for a successful operation.
		 * @return 1 if the file stream is not open.
		 * @return 2 if fs is a nullptr.
		 * @return 3 if the vMemStore is a nullptr.
		 * @return 4 if an unknown error occur.
		 */
		int storeMemory2Fstream (std::fstream* fs, std::vector<std::string>* vMemStore, bool resetPosBeforeOp, bool seekBeginPostOp, bool newLineByVecEntry, bool lastLineEmpty);

		/**
		 * @brief Store the vector memory into the file stream
		 * @param fs File stream object. The file need be already opened.
		 * @param vMemStore Vector with line stored in memory.
		 * @param resetPosBeforeOp Reset the position before starting the operation. Otherwise, will not take the full file content.
		 * @param seekBeginPostOp Back to the start position.
		 * @param newLineByVecEntry Insert a new line in the file to each vector entry.
		 * @param lastLineEmpty If the new line insertion is active, define if a empty line will be added in the end of the file.
		 * @return 0 for a successful operation.
		 * @return 1 if the file stream is not open.
		 * @return 2 if fs is a nullptr.
		 * @return 3 if the vMemStore is a nullptr.
		 * @return 4 if an unknown error occur.
		 */
		int storeMemory2Fstream (std::wfstream* fs, std::vector<std::wstring>* vMemStore, bool resetPosBeforeOp, bool seekBeginPostOp, bool newLineByVecEntry, bool lastLineEmpty);
	}
}

#endif //! SETTINGS_LIB_TOOLS_HPP