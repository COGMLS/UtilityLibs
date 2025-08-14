#pragma once

#ifndef VERSION_LIB_TOKEN_MAPPER_HPP
#define VERSION_LIB_TOKEN_MAPPER_HPP

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

#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER)

#include <string>
#include <vector>
#include <array>
#include <map>
#include <memory>
#include <list>

#include "BuildTypesExt.hpp"
#include "BuildMetadata.hpp"
#include "VersionToken.hpp"
#include "TokenClassifier.hpp"

/** Version Library Token classifier and mapper system
 * --------------------------------------------------------
 * About:
 * 
 * The Version Token system contains a generic approach for common
 * datatypes and a specific approach for special tokens, like
 * version core separators. The process to separate the components
 * and make sure all of them are correctly set with right id,
 * depends on a classifiers.
*/

namespace VersionLib
{
	/**
	 * @brief Version Token Dictionary Mapper system. Map all extracted tokens from a dictionary, obeying the version format components position.
	 */
	class VERSION_LIB_API TokenMapper
	{
		protected:

			std::unique_ptr<VersionLib::TokenClassifier> classifier;

			std::vector<unsigned short> core;			// Version Core components
			VersionLib::VersionBuildType release;		// Version Release components
			VersionLib::BuildMetadata metadata;			// Version Metadata
			bool useBuild = false;						// Flag to determinate if build is used
			unsigned long build;						// Version build compilation

			TokenMapper();

		public:
			
			//
			// Constructors:
			//

			TokenMapper (VersionLib::TokenClassifier classifier);

			TokenMapper (VersionLib::TokenClassifier* classifierRef);

			TokenMapper (const VersionLib::TokenMapper& other);

			TokenMapper (VersionLib::TokenMapper&& other) noexcept;

			//
			// Destructor:
			//

			~TokenMapper();

			//
			// Operators:
			//

			VersionLib::TokenMapper& operator= (const VersionLib::TokenMapper& other);
			VersionLib::TokenMapper& operator= (VersionLib::TokenMapper&& other) noexcept;

			//
			// Classifier Direct Access:
			//

			VersionLib::TokenClassifier* access();
			
			//
			// Process Tokens:
			//

			//VersionLib::VersionToken getToken (size_t pos);

			/**
			 * @brief Process the tokens with internal TokenClassifier
			 * @return This function should return ALWAYS false if is not implemented or if the internal classifier was not used.
			 */
			virtual bool processTokens (std::string version_str);

			/**
			 * @brief Process the tokens using the formats to version components
			 * @param tokens Version tokens
			 * @return This function should return ALWAYS false if is not implemented.
			 */
			virtual bool processTokens (std::vector<VersionLib::VersionToken>& tokens);
			
			/**
			 * @brief Process the version string to version tokens and classify them with the TokenClassifier
			 * @param classifier TokenClassifier used when the mapper does not implement the internal component
			 * @param version_str Version string that will be converted into tokens
			 * @return This function should return ALWAYS false if is not implemented.
			 */
			virtual bool processTokens (VersionLib::TokenClassifier* classifier, std::string version_str);

			//
			// Checkers:
			//

			bool hasCoreSeq();

			bool hasVersionBuildType();

			bool hasMetadata();

			bool hasBuildCompilation();

			//
			// Getters for classified version tokens:
			//

			std::vector<unsigned short> getCoreNumSeq();

			VersionLib::VersionBuildType getBuildTypeComponents();

			VersionLib::BuildMetadata getBuildMetadata();

			unsigned long getBuildCompilation();

			//
			// Auxiliary methods:
			//

			void clean();
	};
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY && !VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER

#endif // !VERSION_LIB_TOKEN_MAPPER_HPP