#pragma once 

#ifndef SETTINGS_LIB_CONFIG_FILE_STREAM_HPP
#define SETTINGS_LIB_CONFIG_FILE_STREAM_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32

#include <climits>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

#include "SettingsLibTools.hpp"

// Maximum exceptions/errors the Configuration File Stream will store.
#define CONFIG_FILE_STREAM_MAXIMUM_ERRORS 50

namespace SettingsLib
{
	namespace Types
	{
		/**
		 * @brief Configuration File Stream to manage the file manipulation.
		 */
		class SETTINGS_LIB_API ConfigFileStream
		{
			protected:
				// Configuration file path:
				std::filesystem::path cfgFilePath;

				//
				// Configuration file stream:
				//

				std::unique_ptr<std::fstream> cfgFileStream;
				std::unique_ptr<std::wfstream> wCfgFileStream;
				std::ios_base::openmode cfgFileMode;

				//
				// Configuration local memory store:
				//

				std::unique_ptr<std::vector<std::string>> cfgStore;
				std::unique_ptr<std::vector<std::wstring>> wCfgStore;

				//
				// Variable controls:
				//

				bool isWideData;					// Define if the string data will be wstring or string
				bool isReadonly;					// Define if a protection against write operations in the file and vector memory
				bool isNewFile;						// Define if the file was created in the same moment of the object's creation
				bool isCfgFileOk;					// Determinate if the configuration file is ok
				bool keepCfgStore;					// Determinate if the Vector Memory Store is enabled
				bool errorReportEnabled;			// Define if the error report is enabled

				short errorListMaxReports;			// Maximum reports to store in errorList

				// Exception history:
				std::unique_ptr<std::vector<std::exception>> errorsList;

				//
				// Internal methods:
				//

				/**
				 * @brief Save the configuration lines into the Vector
				 * @return Return -1 if a exception was found
				 * @return Return 0 if keepCfgStore is false
				 * @return Return 1 if the data line was successfully saved into the vector
				 */
				int save2Store();

				/**
				 * @brief Create the vector store in memory if doesn't exist and keepCfgStore is true
				 * @return -1 if the Vector Store is disabled.
				 * @return 0 if the Vector Memory Store was created.
				 * @return 1 if the Vector Memory Store already exist in memory.
				 */
				int makeVMemStore();

				/**
				 * @brief Check if Vector Memory Store exist in memory
				 * @return False if the vector is not prepared to save into the memory. True if the vector is ready to save into the memory.
				 */
				bool vMemStoreExist();

				/**
				 * @brief Save a error report into the Error List, if enabled.
				 * @param e Exception report
				 */
				void saveErrorReport (std::exception e);

				/// @brief This constructor is only for inheritance.
				ConfigFileStream();

			public:

				//
				// Constructors and Destructor:
				//

				/**
				 * @brief Create an object to control the configuration file stream and it's lines
				 * @param cfgFilePath Path to the configuration line.
				 * @param useWideData Define to use wstring for (UTF-16) format. This definition can't be changed after the object creation.
				 * @param useReadonly Define if it will block for changes in file stream. This definition can't be changed after the object creation.
				 * @param keepCfgStore Define to keep the configuration vector memory stored or clean after the reading file operation.
				 * @note Use wide data (UTF-16) is not recommended.
				 * @note Keeping the configuration lines in memory can allow easily verify the data was changed for some applications but can use unnecessary memory depending on the number of lines.
				 * @note When freeCfgStore is called, the memory is cleaned. To have access again to memory store, call refreshCfgStore.
				 * @note To access the configuration lines when keepCfgStore is not set, is necessary call extractLines. It's possible access directly the file stream but isn't recommended because it's not possible to control if the stream will be closed or changed.
				 */
				ConfigFileStream (std::filesystem::path cfgFilePath, bool useWideData, bool useReadonly, bool keepCfgStore);

				/**
				 * @brief Destroy the configuration file stream.
				 */
				~ConfigFileStream();

				//
				// File Stream Controls:
				//

				/**
				 * @brief Close the file stream.
				 * @note This method only close the file stream and doesn't free the vector configuration store.
				 */
				void closeConfigStream();

				/**
				 * @brief Reopen the configuration file stream
				 * @param refreshCfgStore Refresh configuration memory, if previous enabled
				 * @param useReadonly Define or redefine open mode
				 * @return True if a successful operation occur.
				 */
				bool openConfigStream(bool refreshCfgStore, bool useReadonly);

				/**
				 * @brief Check if the configuration file stream is opened.
				 */
				bool isConfigStreamOpen();

				/**
				 * @brief Access the configuration file stream.
				 * @param cfgFileStream  
				 * @warning The configuration stream object can't control how the file stream is used outside. Careful when using this method!
				 */
				void getConfigStream (std::fstream* cfgFileStream);

				/**
				 * @brief Access the configuration file stream.
				 * @param wCfgFileStream  
				 * @warning The configuration stream object can't control how the file stream is used outside. Careful when using this method!
				 */
				void getConfigStream (std::wfstream* wCfgFileStream);

				//
				// Configuration Line Insertion, Deletion and Change methods:
				//

				/**
				 * @brief Get the configuration lines stored in memory
				 * @param vMemStore Pointer to receive the access to the vector
				 * @return -3 if an exception occur.
				 * @return -2 if the Vector Memory is not ready in memory.
				 * @return -1 if object is configured to work with wstring.
				 * @return 0 if the Vector Memory is disabled.
				 * @return 1 if the operation was successful.
				 */
				int getConfigLines (std::vector<std::string>* vMemStore);

				/**
				 * @brief Get the configuration lines stored in memory
				 * @param vMemStore Pointer to receive the access to the vector
				 * @return -3 if an exception occur.
				 * @return -2 if the Vector Memory is not ready in memory.
				 * @return -1 if object is configured to work with string.
				 * @return 0 if the Vector Memory is disabled.
				 * @return 1 if the operation was successful.
				 */
				int getConfigLines (std::vector<std::wstring>* vMemStore);

				/**
				 * @brief Get a configuration line stored in memory or read directly from the file stream.
				 * @param nLine Line number that is compatible with the vector's index or line number from file stream.
				 * @param line Pointer to receive the access to the string line.
				 * @param useCfgStore Define to read from configuration stored in memory or use directly from file stream.
				 * @return Return 0 if the operation was completed with success.
				 * @return Return 1 if the configuration file stream is not open.
				 * @return Return 2 if line is nullptr.
				 * @return Return 3 if an unknown exception occur.
				 * @return Return 4 in case nLine is bigger than vector's size.
				 * @return Return 5 in case the object is configured to use wstring.
				 * @return Return 6 when useCfgStore is true but keep the configuration lines into memory is disabled.
				 * @return Return 7 if the vMemStore is not ready into the memory.
				 */
				int getConfigLine (size_t nLine, std::string* line, bool useCfgStore);

				/**
				 * @brief Get a configuration line stored in memory or read directly from the file stream.
				 * @param nLine Line number that is compatible with the vector's index or line number from file stream.
				 * @param line Pointer to receive the access to the string line.
				 * @param useCfgStore Define to read from configuration stored in memory or use directly from file stream.
				 * @return Return 0 if the operation was completed with success.
				 * @return Return 1 if the configuration file stream is not open.
				 * @return Return 2 if line is nullptr.
				 * @return Return 3 if an unknown exception occur.
				 * @return Return 4 in case nLine is bigger than vector's size.
				 * @return Return 5 in case the object is configured to use string.
				 * @return Return 6 when useCfgStore is true but keep the configuration lines into memory is disabled.
				 * @return Return 7 if the vMemStore is not ready into the memory.
				 */
				int getConfigLine (size_t nLine, std::wstring* line, bool useCfgStore);

				/**
				 * @brief Set the configuration lines to store in memory and be able to save into the file
				 * @param new_vMemStore Vector with configuration lines
				 * @param overrideVector Override the Vector Memory if true. Otherwise will add into the end of the Vector Memory.
				 * @return 0 if the operation was successful.
				 * @return 1 when the object is configured to use wstring.
				 * @return 2 if the Vector Memory is disabled.
				 * @return 3 if an exception occur.
				 */
				int setConfigLines (std::vector<std::string>* new_vMemStore, bool overrideVector);

				/**
				 * @brief Set the configuration lines to store in memory and be able to save into the file
				 * @param new_vMemStore Vector with configuration lines
				 * @param overrideVector Override the Vector Memory if true. Otherwise will add into the end of the Vector Memory.
				 * @return 0 if the operation was successful.
				 * @return 1 when the object is configured to use string.
				 * @return 2 if the Vector Memory is disabled.
				 * @return 3 if an exception occur.
				 */
				int setConfigLines (std::vector<std::wstring>* new_vMemStore, bool overrideVector);

				/**
				 * @brief Set a configuration line in memory. It's possible to change it or add the line.
				 * @param lineN Line number
				 * @param line String representing the configuration line
				 * @param overwrite If true will change the actual line. Otherwise, will add a new line in lineN position, moving the rest of the content.
				 * @return 0 if the operation was successful.
				 * @return 1 when the object is configured to use wstring.
				 * @return 2 if the Vector Memory Store is disabled.
				 * @return 3 if an exception occur.
				 * @note If lineN is bigger than vMemStore, the line will be inserted in the end.
				 */
				int setConfigLine (size_t lineN, std::string line, bool overwrite);

				/**
				 * @brief Set a configuration line in memory. It's possible to change it or add the line.
				 * @param lineN Line number
				 * @param line String representing the configuration line
				 * @param overwrite If true will change the actual line. Otherwise, will add a new line in lineN position, moving the rest of the content.
				 * @return 0 if the operation was successful.
				 * @return 1 when the object is configured to use string.
				 * @return 2 if the Vector Memory Store is disabled.
				 * @return 3 if an exception occur.
				 * @note If lineN is bigger than vMemStore, the line will be inserted in the end.
				 */
				int setConfigLine (size_t lineN, std::wstring line, bool overwrite);

				/**
				 * @brief Set a configuration line in file stream.
				 * @param line String representing the configuration line
				 * @param refLine Reference line with partial content to use to identify the first occurrence
				 * @param lineN Line number
				 * @param useRefLine Define to use reference line or line number if false
				 * @return 
				 * @note If lineN is bigger than file, the line will be put in the end of the file.
				 * @note This method uses a temporary vector, but doesn't use Vector Memory Store.
				 */
				int setConfigLine (std::string line, std::string refLine, size_t lineN, bool useRefLine);

				int setConfigLine (std::wstring line, std::wstring refLine, size_t lineN, bool useRefLine);

				/**
				 * @brief Insert a new line in the file
				 * @param line Line that will be inserted
				 * @param insertOnBegin Insert the line on begin of the file if true
				 * @param resetPos Reset the file stream to the begin of the file
				 * @return 0 if the operation was successful.
				 * @return 1 if the file is not open.
				 * @return 2 if the object is configured to wstring.
				 * @return 3 if fail to load the file.
				 * @return 4 if fail to save the file.
				 * @note This method is better to be use only for a few lines insertions to avoid excessive use of I/O. To reduce the I/O use, enable the Vector Memory Store and update the vector lines.
				 */
				int insertConfigLine (std::string line, bool insertOnBegin, bool resetPos);

				/**
				 * @brief Insert a new line in the file
				 * @param line Line that will be inserted
				 * @param insertOnBegin Insert the line on begin of the file if true
				 * @param resetPos Reset the file stream to the begin of the file
				 * @return 0 if the operation was successful.
				 * @return 1 if the file is not open.
				 * @return 2 if the object is configured to string.
				 * @return 3 if fail to load the file.
				 * @return 4 if fail to save the file.
				 * @note This method is better to be use only for a few lines insertions to avoid excessive use of I/O. To reduce the I/O use, enable the Vector Memory Store and update the vector lines.
				 */
				int insertConfigLine (std::wstring line, bool insertOnBegin, bool resetPos);

				//
				// Vector Memory Store Controls:
				//

				/**
				 * @brief Get the size of the vector that is stored in memory with the configuration lines.
				 * @note Zero can represent an empty vector or that keepCfgStore was disable. Check the keepCfgStore status with getKeepCfgStore method.
				 */
				size_t getvMemStoreSize();

				/**
				 * @brief Free the memory from configuration lines that was stored.
				 * @return -1 if the keepCfgStore is disabled.
				 * @return 0 if the memory was freed.
				 * @return 1 if the memory was already free.
				 */
				int freeCfgStore();

				/**
				 * @brief Refresh the configuration lines store in memory
				 * @return 0 in successful operation.
				 * @return 1 if the file stream is not open.
				 * @return 2 if the Vector Memory Store is disabled.
				 * @return 3 fail to save into the memory the file lines.
				 */
				int refreshCfgStore();

				/**
				 * @brief Refresh the configuration lines store in memory with a external data
				 * @param externCfgStore External configuration line store.
				 * @return 0 in successful operation.
				 * @return 1 if the file stream is not open.
				 * @return 2 if the Vector Memory Store is disabled.
				 * @return 3 fail to save into the memory the file lines.
				 * @return 4 if the file stream is configured to use wide strings.
				 * @return 5 in case the readonly mode is active.
				 */
				int refreshCfgStore(std::vector<std::string>* externCfgStore);

				/**
				 * @brief Refresh the configuration lines store in memory with a external data
				 * @param externCfgStore External configuration line store.
				 * @return 0 in successful operation.
				 * @return 1 if the file stream is not open.
				 * @return 2 if the Vector Memory Store is disabled.
				 * @return 3 fail to save into the memory the file lines.
				 * @return 4 if the file stream is configured to use wide strings.
				 * @return 5 in case the readonly mode is active.
				 */
				int refreshCfgStore(std::vector<std::wstring>* externCfgStore);

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

				//
				// General Object Controls:
				//

				/**
				 * @brief Check if the configuration file stream accept changes.
				 * @note If the file was created during the object creation and readonly was defined, the property will be disabled to allow write access to file stream. 
				 */
				bool isReadonlyMode();

				/**
				 * @brief Verify if the configuration file stream object is ok.
				 */
				bool isConfigStreamOk();

				/**
				 * @brief Define the readonly mode to protect the object to accept modifications on file stream.
				 * @param readonly True define enable the readonly mode.
				 */
				void setReadonly(bool readonly);

				/**
				 * @brief Save the Vector Memory into the file
				 * @param saveType Determinate the method to save the Vector Memory Store into the file. Check the notes for more details.
				 * @return 
				 * @note The save types available are: 0 - override the file lines (default operation). 1 - Put the vector's data on begin of the file. 2 - Put the vector's data on the end of the file.
				 */
				int saveStoreOnFile(unsigned short saveType = 0);

				//
				// Error List Controls:
				//

				/**
				 * @brief Access the error list. If no error or status was created, an empty vector will return.
				 * @return Return a vector of exceptions founded.
				 */
				std::vector<std::exception> getErrorList();

				/**
				 * @brief Clean the error reports
				 */
				void cleanErrors();

				/**
				 * @brief Set the error reports that will be saved in memory. Using zero, will disabled the error report.
				 * @param maxErrorReports Define the maximum number of reports in memory.
				 */
				void setErrorReport (unsigned short maxErrorReports);
		};
	}
}

#endif //! SETTINGS_LIB_CONFIG_FILE_STREAM_HPP