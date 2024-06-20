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
		 * @param readLines Number of lines to store. If zero is passed, all line from current position will be stored. If a number bigger of lines was passed, the function will send all lines to the vMemStore.
		 * @param resetPosBeforeOp Reset the position before starting the operation. Otherwise, will not take the full file content.
		 * @param seekBeginPostOp Back to the start position.
		 * @return 0 for a successful operation.
		 * @return 1 if the file stream is not open.
		 * @return 2 if fs is a nullptr.
		 * @return 3 if the VMemStore is a nullptr.
		 * @return 4 if an unkwnown error occur.
		 */
		int storeFstream2Memory (std::fstream* fs, std::vector<std::string>* vMemStore, unsigned long long readLines, bool resetPosBeforeOp, bool seekBeginPostOp);

		/**
		 * @brief Create a ConfigDataUnion type
		 * @param pData Pointer to ConfigDataUnion
		 * @return If a successful operation occur, will return 0
		 * @return If a not nullptr was send, will return 1
		 * @return In any catch fail will return 2
		 */
		int initializeDataUnion (SettingsLib::Types::ConfigDataUnion* pData);

		/**
		 * @brief Create a ConfigDataUnion type and initialyze the data
		 * @param pData Pointer to ConfigDataUnion
		 * @param type Data type to define in initialization
		 * @return If a successful operation occur, will return 0
		 * @return If a non nullptr was send, will return 1
		 * @return In any catch fail in create the data will return 2
		 * @return In any catch fail of initialyze the data, will return 3
		 * @return Will return 4, if a invalid configuration was send
		 */
		int initializeDataUnion (SettingsLib::Types::ConfigDataUnion* pData, SettingsLib::Types::ConfigDataType type);

		/**
		 * @brief Destroy a ConfigDataUnion type
		 * @param pData Pointer to ConfigDataUnion
		 * @param type Data type used in creation time
		 * @return If a successful operation occur, will return 0
		 * @return If a nullptr was send, will return 1
		 * @return In any catch fail will return 2
		 * @return Will return 3, if a invalid configuration was send
		 */
		int destroyDataUnion (SettingsLib::Types::ConfigDataUnion* pData, SettingsLib::Types::ConfigDataType type);

		//
		// Inline or header-only methods:
		//

		/**
		 * @brief Initialize a data without set a value
		 * @tparam t Data type set
		 * @param pData Pointer to be initialized
		 * @return -1 if fail in initialize the data
		 * @return 0 if success in initialize the data
		 * @return 1 if the pointer is not nullptr (already was initialized)
		 */
		template<typename T> inline int initializeData (T* pData)
		{
			try
			{
				if (pData == nullptr)
				{
					pData = new T;
				}
				else
				{
					return 1;		// Not a nullptr
				}

				return 0;			// Data created with success
			}
			catch(const std::exception&)
			{
				return -1;			// Fail to create the data
			}
		}

		/**
		 * @brief Initialize a data and set a value
		 * @tparam t Data type set
		 * @param pData Pointer to be initialized
		 * @param data Data to set in pointer data
		 * @return -2 error in initialize the data
		 * @return -1 fail to initialize the data, because the helper function returned a nullptr.
		 * @return 0 if success in initialize the data and set the value
		 * @return 1 if the pointer is not nullptr (already was initialized) and was set a new value
		 */
		template<typename T> inline int initializeData (T* pData, T data)
		{
			try
			{
				int r = initializeData<T>(pData);

				if (r == 0 && pData != nullptr)
				{
					*pData = data;

					return 0;			// Successful operation
				}
				
				if (r == 1 && pData != nullptr)
				{
					*pData = data;

					return 1;			// Successful operation. The pData wasn't a nullptr
				}

				return -1;				// Fail. pData returned as nullptr
			}
			catch(const std::exception&)
			{
				return -2;				// An exception occur
			}
			
		}

		/**
		 * @brief Initialize a data and set a value
		 * @tparam t Data type set
		 * @param pData Pointer to be initialized
		 * @param data Data to set in pointer data
		 * @return -2 error in initialize the data
		 * @return -1 fail to initialize the data, because the helper function returned a nullptr.
		 * @return 0 if success in initialize the data and set the value
		 * @return 1 if the pointer is not nullptr (already was initialized) and was set a new value
		 */
		template<typename T> inline int initializeData (T* pData, T* data)
		{
			try
			{
				int r = initializeData<T>(pData);

				if (r == 0 && pData != nullptr)
				{
					*pData = *data;

					return 0;			// Successful operation
				}
				
				if (r == 1 && pData != nullptr)
				{
					*pData = *data;

					return 1;			// Successful operation. The pData wasn't a nullptr
				}

				return -1;				// Fail. pData returned as nullptr
			}
			catch(const std::exception&)
			{
				return -2;				// An exception occur
			}
		}
	}
}

#endif //! SETTINGS_LIB_TOOLS_HPP