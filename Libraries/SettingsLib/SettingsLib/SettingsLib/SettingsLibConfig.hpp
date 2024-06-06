#pragma once 

#ifndef SETTINGS_LIB_CONFIG_HPP
#define SETTINGS_LIB_CONFIG_HPP

#ifdef WIN32
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

namespace SettingsLib
{
	/**
	 * @brief Class to store and define configurations keys and values
	 */
	class SETTINGS_LIB_API Config
	{
		private:
			// Configuration file object:
			std::filesystem::path cfgFilePath;

			// Configuration file stream:
			

			// Configuration variable controls:
			bool isMod;
			bool isWideData;
			bool isConfigOk;
		public:
	};
}

#endif //! SETTINGS_LIB_CONFIG_HPP