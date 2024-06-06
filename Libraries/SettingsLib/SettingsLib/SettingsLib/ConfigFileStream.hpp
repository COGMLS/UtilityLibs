#pragma once 

#ifndef SETTINGS_LIB_CONFIG_FILE_STREAM_HPP
#define SETTINGS_LIB_CONFIG_FILE_STREAM_HPP

#ifndef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "SettingsLibTools.hpp"

// Maximum exceptions/errors the Configuration File Stream will store.
#define CONFIG_FILE_STREAM_MAXIMUM_ERRORS 50

namespace SettingsLib
{
	/**
	 * @brief Configuration File Stream to manage the file manipulation.
	 */
	class SETTINGS_LIB_API ConfigFileStream
	{
		protected:
			// Configuration file path:
			std::filesystem::path cfgFilePath;

			// Configuration file stream:
			std::fstream* cfgFileStream = nullptr;
			std::wfstream* wCfgFileStream = nullptr;
			std::ios_base::openmode cfgFileMode;

			// Configuration local memory store:
			std::vector<std::string>* cfgStore = nullptr;
			std::vector<std::wstring>* wCfgStore = nullptr;

			// Variable controls:
			bool isWideData;
			bool isReadonly;
			bool isNewFile;
			bool isCfgFileOk;
			bool keepCfgStore;

			// Exception history:
			std::vector<std::exception>* errorsList = nullptr;

		public:
			/// @brief This constructor is only for inheritance.
			ConfigFileStream();

			/**
			 * @brief Create an object to control the configuration file stream and it's lines
			 * @param cfgFilePath Path to the configuration line.
			 * @param useWideData Define to use wstrings for (UTF-16) format. This definition can't be changed after the object creation.
			 * @param useReadonly Define if it will block for changes in file stream. This definition can't be changed after the object creation.
			 * @param keepCfgStore Define to keep the configuration vector memory stored or clean after the reading file operation.
			 * @note Use wide data (UTF-16) is not recomended.
			 * @note Keeping the configuration lines in memory can allow easily verify the data was changed for some applications but can use unnecessary memory depending on the number of lines.
			 * @note When freeCfgStore is called, the memory is cleaned. To have access again to memory store, call refreshCfgStore.
			 * @note To access the configuration lines when keepCfgStore is not set, is necessary call extractLines. It's possible access directly the file stream but isn't recomended because it's not possible to control if the stream will be closed or changed.
			 */
			ConfigFileStream (std::filesystem::path cfgFilePath, bool useWideData, bool useReadonly, bool keepCfgStore);

			/**
			 * @brief Close the file stream.
			 * @note This method only close the file stream and doesn't free the vector confguration store.
			 */
			void closeConfigStream();

			/**
			 * @brief Reopen the configuration file stream
			 * @return True if a successfull operation occur.
			 */
			bool openConfigStream();

			/**
			 * @brief Check if the configuration file stream is opened.
			 */
			bool isConfigStreamOpen();

			/**
			 * @brief Get the configuration lines stored in memory
			 * @param vMemStore Pointer to receave the access to the vector
			 * @return Return the value from Tools::storeFstream2Memory function
			 */
			int getConfigLines (std::vector<std::string>* vMemStore);

			/**
			 * @brief Get a configuration line stored in memory
			 * @param nLine Line number that is compatible with the vector's index.
			 * @param line Pointer to receave the access to the string line
			 * @return Return the value from Tools::storeFstream2Memory function
			 * @note If nLine receave a number bigger than the vector size, the function will return 5.
			 */
			int getConfigLine (unsigned long long nLine, std::string* line);

			/**
			 * @brief Access the configuration file stream.
			 * @param cfgFileStream 
			 * @return 
			 * @warning The configuration stream object can't control how the file stream is used outside. Carefull when using this method!
			 */
			int getConfigStream (std::fstream* cfgFileStream);

			/**
			 * @brief Set the configuration lines to store in memory and be able to save into the file
			 * @param new_vMemStore Vector with configuration lines
			 * @return 
			 */
			int setConfigLines (std::vector<std::string>* new_vMemStore);

			/**
			 * @brief Set a configuration line in memory. It's possible to change it or add the line.
			 * @param lineN Line number
			 * @param line String repreesnting the configuration line
			 * @param overWrite If true will change the actual line. Otherwise, will add a new line in lineN position.
			 * @return 
			 * @note If lineN is bigger than vMemStore, the line will be inserted in the end.
			 */
			int setConfigLine (unsigned long long lineN, std::string* line, bool overWrite);

			/**
			 * @brief Get the size of the vector that is stored in memory with the configuration lines.
			 * @note Zero can represent an empty vector or that keepCfgStore was disable. Check the keepCfgStore status with getKeepCfgStore method.
			 */
			size_t getvMemStoreSize();

			/**
			 * @brief Free the memory from configuration lines that was stored.
			 * @return 0 if the memory was freed.
			 * @return 1 if the memory was already free.
			 */
			int freeCfgStore();

			/**
			 * @brief Refresh the configuration lines store in memory
			 * @return Return the value from Tools::storeFstream2Memory function
			 * @note If memory was free, it will reallocate to store again.
			 * @note If keepCfgStore is not set, will return 5.
			 */
			int refreshCfgStore();

			/**
			 * @brief Refresh the configuration lines store in memory
			 * @param externCfgStore External configuration line store.
			 * @return Return the value from Tools::storeFstream2Memory function
			 */
			int refreshCfgStore(std::vector<std::string>* externCfgStore);

			/**
			 * @brief Get the status of configuration memory store
			 */
			bool getKeepCfgStore();

			/**
			 * @brief Define the keepCfgStore setting.
			 * @param keepCfgStore Value to define the configuration memory store behavior.
			 * @note Disabling keepCfgStore, will call freeCfgStore automatically
			 */
			void setKeepCfgStore (bool keepCfgStore);

			/**
			 * @brief Check if the configuration file stream accept changes.
			 * @note If the file was created during the object creation and readonly was defined, the property will be disabled to allow write access to file stream. 
			 */
			bool isReadonlyMode();

			/**
			 * @brief Access the error list. If no error or status was created, an empty vector will return.
			 * @return Return a vector of exceptions founded.
			 */
			std::vector<std::exception> getErrorList();
	};
}

#endif //! SETTINGS_LIB_CONFIG_FILE_STREAM_HPP