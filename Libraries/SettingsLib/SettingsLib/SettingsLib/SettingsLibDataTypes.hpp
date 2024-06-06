#pragma once 

#ifndef SETTINGS_LIB_DATA_TYPES_HPP
#define SETTINGS_LIB_DATA_TYPES_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32

#include <array>
#include <string>
#include <vector>

namespace SettingsLib
{
	namespace Types
	{
		/// @brief Settings Library Version struct
		struct SettingsLibVersion
		{
			unsigned int major;
			unsigned int minor;
			unsigned int revision;
			char buildType[8];
			unsigned int build;
		};

		/// @brief Configuration Data for Container Type
		enum ConfigDataContainerType : int
		{
			NO_CONTAINER,
			VECTOR,
			ARRAY
		};

		/// @brief Configuration Data Type control
		enum ConfigDataType : int
		{
			SETTINGS_LIB_CONFIG_DATA_FAIL,
			SETTINGS_LIB_CONFIG_DATA_EMPTY,
			SETTINGS_LIB_UNSIGNED_INTEGER,
			SETTINGS_LIB_INTERGER,
			SETTINGS_LIB_FLOAT,
			SETTINGS_LIB_STRING,
			SETTINGS_LIB_BOOLEAN,
			SETTINGS_LIB_WSTRING,
		};

		/// @brief Configuration Data Union
		union ConfigDataUnion
		{
			unsigned long long ull;
			long long ll;
			double d;
			bool b;
			std::string* s;
			std::wstring* w;
		};

		class ConfigData
		{
			private:
				ConfigDataType* data = nullptr;
				std::vector<ConfigDataType>* vdata = nullptr;
				std::array<ConfigDataType, 0>* adata = nullptr;
			public:

		};
	}
}

#endif //! SETTINGS_LIB_DATA_TYPES_HPP