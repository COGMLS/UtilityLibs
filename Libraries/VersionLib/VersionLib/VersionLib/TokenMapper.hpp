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
#include <memory>

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

			std::unique_ptr<VersionLib::TokenClassifier> classifier;	// Internal classifier (optional). If no internal classifier is used, an external classifier must be used.

			std::vector<unsigned short> core;							// Version Core components
			VersionLib::VersionBuildType release;						// Version Release components
			VersionLib::BuildMetadata metadata;							// Version Metadata
			short useBuild = 0;											// Flag to determinate if build is used. 0: No used in version classifier. 1: Used by version classifier, but not set. 2: Used by classifier and set the build value.
			unsigned long build;										// Version build compilation

			/**
			 * @brief Empty constructor. Only for inherence.
			 */
			TokenMapper();

			/**
			 * @brief Set the build compilation value, following the useBuild variable rule
			 */
			void setBuildCompilation(unsigned long build);

		public:
			
			//
			// Constructors:
			//

			/**
			 * @brief Constructor to create the TokenMapper
			 * @param classifier Token classifier object
			 */
			TokenMapper (VersionLib::TokenClassifier classifier);

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

			/**
			 * @brief Access the internal token classifier. If no internal classifier exist, a nullptr is returned.
			 */
			VersionLib::TokenClassifier* access();
			
			//
			// Process Tokens:
			//

			//VersionLib::VersionToken getToken (size_t pos);

			/**
			 * @brief Process the tokens with internal TokenClassifier
			 * @return This function should return ALWAYS -1 if is not implemented or if the internal classifier was not used.
			 * @note Other return values are defined by the implementation of this function.
			 */
			virtual int processTokens (std::string version_str);

			/**
			 * @brief Process the tokens using the formats to version components
			 * @param tokens Version tokens
			 * @return This function should return ALWAYS -1 if is not implemented.
			 * @note Other return values are defined by the implementation of this function.
			 */
			virtual int processTokens (std::vector<VersionLib::VersionToken>& tokens);
			
			/**
			 * @brief Process the version string to version tokens and classify them with the TokenClassifier
			 * @param classifier TokenClassifier used when the mapper does not implement the internal component
			 * @param version_str Version string that will be converted into tokens
			 * @return This function should return ALWAYS -1 if is not implemented.
			 * @note Other return values are defined by the implementation of this function.
			 */
			virtual int processTokens (VersionLib::TokenClassifier* classifier, std::string version_str);

			//
			// Checkers:
			//

			/**
			 * @brief Check if the TokenMapper has the version core sequence components
			 */
			bool hasCoreSeq();

			/**
			 * @brief Check if the TokenMapper has version build type or release information
			 */
			bool hasVersionBuildType();

			/**
			 * @brief Check if the TokenMapper has the version metadata
			 */
			bool hasMetadata();

			/**
			 * @brief Check if the TokenMapper is set to use build compilation data and if is set the value
			 * @return 0: Not configured to use.
			 * @return 1: Configured to be used, but the compilation value is not set.
			 * @return 2: Configured to be used and the compilation value is set.
			 */
			short hasBuildCompilation();

			//
			// Getters for classified version tokens:
			//

			/**
			 * @brief Get the sequence of version core components
			 */
			std::vector<unsigned short> getCoreNumSeq();

			/**
			 * @brief Get the version build type components object. This object can contain multiple release versions if supported by the classifier.
			 */
			VersionLib::VersionBuildType getBuildTypeComponents();

			/**
			 * @brief Get the build metadata
			 */
			VersionLib::BuildMetadata getBuildMetadata();

			/**
			 * @brief Get the build compilation
			 * @return If the mapper is not configured to use the compilation, the return will be zero.
			 */
			unsigned long getBuildCompilation();

			//
			// Auxiliary methods:
			//

			/**
			 * @brief Clean all stored version components
			 */
			void clean();
	};
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY && !VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER

#endif // !VERSION_LIB_TOKEN_MAPPER_HPP