#pragma once

#ifndef VERSION_LIB_METADATA_HPP
#define VERSION_LIB_METADATA_HPP

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

#include "ExperimentalFeatures.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
#include "ExceptionComponents.hpp"
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS

#include <string>
#include <memory>
#include <vector>

namespace VersionLib
{
	class VERSION_LIB_API BuildMetadata
	{
		private:

			bool blockMetadataMod;					// Flag to block metadata modification
			std::unique_ptr<std::string> metadata;	// Metadata string

			// Reserve for future modifications
			//std::unique_ptr<std::vector<std::string>> metadata_format;	// Metadata format for data interpretation and export it as readble data.

		public:

			//
			// Constructors:
			//

			/**
			 * @brief Create an empty build metadata object
			 */
			BuildMetadata();

			/**
			 * @brief Create a build metadata object, based on given string with metadata information
			 * @param str_metadata String with build metadata
			 * @warning This constructor does not treat the string metadata. Use the library tools to extraction
			 */
			BuildMetadata (std::string str_metadata);

			BuildMetadata (const VersionLib::BuildMetadata& other);

			BuildMetadata (VersionLib::BuildMetadata&& other) noexcept;

			//
			// Destructor:
			//

			~BuildMetadata();

			//
			// Operators:
			//

			/// @brief Test if the metadata exists
			explicit operator bool();

			VersionLib::BuildMetadata& operator= (const VersionLib::BuildMetadata& other);
			VersionLib::BuildMetadata& operator= (VersionLib::BuildMetadata&& other) noexcept;

			VersionLib::BuildMetadata& operator= (std::string& str_metadata);

			bool operator== (const VersionLib::BuildMetadata& other);
			bool operator== (std::string& other);

			//
			// Methods:
			//

			/**
			 * @brief Check if the metadata object is blocked to modifications
			 */
			bool getMetadataBlocked();

			/**
			 * @brief Define if the metadata object is editable
			 * @param block True set to block against editions
			 */
			void setMetadataBlocked (bool block);

			/**
			 * @brief Get the raw string metadata stored in the object
			 * @return If the object does not hold any data, will return an empty string
			 */
			std::string getRawMetadata();

			std::vector<std::string> getInterpretedMetadata();	// Reserved for future modifications
	};
}

#endif // !VERSION_LIB_METADATA_HPP