#pragma once

#ifndef VERSION_LIB_TOKEN_CLASSIFIER_HPP
#define VERSION_LIB_TOKEN_CLASSIFIER_HPP

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

#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY)

#include <string>
#include <vector>

#include "VersionToken.hpp"

#define VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS

/** Generic Version Library Token components
 * --------------------------------------------------------
 * About token generation:
 * 
 * The token generator separate the version components in two parts:
 * CORE_COMPONENTS and OPTIONAL_COMPONENTS
 * 
 * 
*/

namespace VersionLib
{
	/**
	 * @brief Base Token Classifier class
	 * @details This class contains the main components to create inherent classes that can provide complete support for each version string format. Also, offers support to flag the classifier status and if the override methods should be used or a custom implementation in inherent class.
	 * @note TokenClassifier is only for inherent. Any object created with this class, will have empty vectors and UNDEFINED_TOKEN identification. Also, the class is marked to no be ready for use.
	 */
	class VERSION_LIB_API TokenClassifier
	{
		protected:

			//
			// Core components: 
			//

			unsigned short coreComponents;			// Number of version core components
			char coreSeparator;						// Version core separator

			//
			// Optional components:
			//

			bool hasOptionalComponents;				// If true, enable to detect and classify the optional components
			std::vector<char> optGenericSeparator;	// Generic component separator
			char releaseSeparator;					// Release separator. I.e. In semantic versioning is used dash '-'.
			std::vector<std::string> releaseValues;	// Release values acceptable. I.e. "alpha", "beta", "a", "b".
			char releaseRevSeparator;				// Release revision separator
			bool acceptMultipleReleases;			// The version format accept combined releases like "alpha.beta"
			char buildMetadataSeparator;			// The version format can contain a metadata build information and is detected after the usage of specific character
			short hasBuild;							// Determinate if the version format accept build information. See notes about valid values. Can use the values: 0 - Not used; 1 - Must use the "build" word; 2 - The "build" word is optional; 3 - No word is used;
			char buildNumberSeparator;				// Build value separator

			//
			// Control Variables:
			//

			#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS

			/** Token Classifier Flags:
			 * ==================================
			 * 
			 * About:
			 * --------------
			 * 
			 * The flags are a way to reduce memory usage by TokenClassifier
			 * it contains in the first 2 bit fields a very reduced integer storage
			 * in 3th and 4th bit fields, 
			 * 
			 * Bit fields:
			 * --------------
			 * 
			 * 0 - 3: Very reduced integer to store values in a nibble. Value range: from 0 to 3 (The rest values are reserved).
			 * 4	: allowExtractTokenMethod: Boolean value
			 * 5	: readyForUse: Boolean
			 * 
			 * *The rest fields are reserved*
			 * 
			 * Details:
			 * --------------
			 * Format: [Datatype] field = DefaultValue
			 * 
			 * [bool] readyForUse				= false	| Determinate if the classifier is ready to be used or not. This variable indicates if the classifier was configured correctly or if is using the base class. All inherent classes must change this value to 'true' to be able to work.
			 * 
			 * [short] allowClassifyMethod		= 0		| Determinate if the classifier is qualified to use 'classify' methods. 0: Not qualified. 1: Qualified to use one or both 'classify' methods. 2: Same as '1', with allowing additional custom method. 3: Use a custom 'classify' method and not the given from base class.
			 * 
			 * [bool] allowExtractTokensMethod	= false	| Determinate if the classifier is qualified to use 'extractTokens' method
			*/
			char flags = 0;
			#else
			bool readyForUse = false;				// Determinate if the classifier is ready to be used or not. This variable indicates if the classifier was configured correctly or if is using the base class. All inherent classes must change this value to 'true' to be able to work.
			short allowClassifyMethod = 0;			// Determinate if the classifier is qualified to use 'classify' methods. 0: Not qualified. 1: Qualified to use one or both 'classify' methods. 2: Same as '1', with allowing additional custom method. 3: Use a custom 'classify' method and not the given from base class.
			bool allowExtractTokensMethod = false;	// Determinate if the classifier is qualified to use 'extractTokens' method
			#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS

			//
			// Virtual protected methods:
			//

			TokenClassifier();										// Only protected. 'TokenClassifier' method must have parameters to work.

			virtual VersionLib::VersionTokenType classify();		// Only protected. 'classify' method must have parameters to work.

		public:

			//
			// Constructors:
			//

			/**
			 * @brief Create a Token Classifier to use as a dictionary to translate the version string to version tokens
			 * @param nCoreComponents Number of version core components
			 * @param coreSeparator Version core separator
			 * @param hasOptionalComponents If true, enable to detect and classify the optional components
			 * @param optGenericSeparator Generic component separator
			 * @param releaseSeparator Release separator. I.e. In semantic versioning is used dash '-'.
			 * @param releaseValues Release values acceptable. I.e. "alpha", "beta", "a", "b".
			 * @param releaseRevSeparator Release revision separator
			 * @param acceptMultipleReleases The version format accept combined releases like "alpha.beta"
			 * @param buildMetadataSeparator The version format can contain a metadata build information and is detected after the usage of specific character
			 * @param hasBuild Determinate if the version format accept build information. See notes about valid values.
			 * @param buildNumberSeparator Build value separator
			 * @note releaseValues Use given values to check calling isRelease method. By default.
			 * @note hasBuild Can use the values: 0 - Not used; 1 - Must use the "build" word; 2 - The "build" word is optional; 3 - No word is used;
			 * @note hasBuild Should treat any value that is out of valid range as zero.
			 */
			TokenClassifier(
								unsigned short nCoreComponents,
								char coreSeparator,
								bool hasOptionalComponents,
								std::vector<char> optGenericSeparator,
								char releaseSeparator,
								std::vector<std::string> releaseValues,
								char releaseRevSeparator,
								bool acceptMultipleReleases,
								char buildMetadataSeparator,
								short hasBuild,
								char buildNumberSeparator
							);
			
			TokenClassifier (const VersionLib::TokenClassifier& other);

			TokenClassifier (VersionLib::TokenClassifier&& other) noexcept;

			//
			// Destructor:
			//

			~TokenClassifier();

			//
			// Operators:
			//

			VersionLib::TokenClassifier& operator= (const VersionLib::TokenClassifier& other);
			VersionLib::TokenClassifier& operator= (VersionLib::TokenClassifier&& other) noexcept;

			//
			// Getters:
			//
			
			/**
			 * @brief Get the number of version core components
			 */
			unsigned short getNumCoreComponents();

			/**
			 * @brief Get the version core separator
			 */
			char getCoreSeparator();

			/**
			 * @brief Check if the version format has optional components
			 */
			bool getHasOptionalComponents();

			/**
			 * @brief Get optional generic separator
			 */
			std::vector<char> getOptGenericSeparator();

			/**
			 * @brief Get the version release separator
			 */
			char getReleaseSeparator();

			/**
			 * @brief Get the release values registered
			 */
			std::vector<std::string> getReleaseValues();

			/**
			 * @brief Get the release revision separator
			 */
			char getReleaseRevSeparator();

			/**
			 * @brief Get if the version format accept multiple releases
			 */
			bool getAcceptMultipleReleases();

			/**
			 * @brief Get the build metadata separator
			 */
			char getBuildMetadataSeparator();

			/**
			 * @brief Get the build status
			 * @note hasBuild Can use the values: 0 - Not used; 1 - Must use the "build" word; 2 - The "build" word is optional; 3 - No word is used;
			 */
			short getHasBuild();

			/**
			 * @brief Get the build number separator
			 */
			char getBuildNumberSeparator();

			//
			// Classifier controls:
			//

			/**
			 * @brief Verify if the classify is correctly configured and read for use
			 */
			bool isReady();

			/**
			 * @brief Control if the classifiers will allow to use the 'classify' methods
			 * @return If false, a external function must be used to classify and use the internal classifier components to detect how to detect the token.
			 */
			short allowClassify();

			/**
			 * @brief Control if the classifier will allow to use the 'extractTokens' method
			 * @return If false, an external function must be called to use the internal classifier components or the 'classify' methods to detect the tokens.
			 */
			bool allowExtract();

			//
			// Checkers:
			//

			/**
			 * @brief Try to classify the current given data. Set the pointers as nullptr to not use the variable.
			 * @param currentChar Current character to analyze
			 * @param strAcc String accumulator
			 * @param tokenType Current token type classification
			 * @param lastTokenType Last token type classification
			 * @param useTmpToken Define if will 'tmpToken' pointer and it's data/create one
			 * @param tmpData Depending the implemented algorithm, may be easier to already provide the token data. Use the temporary token data as data transaction.
			 * @return If not identified the token, must return UNDEFINED_TOKEN.
			 * @note This method is a generic implementation, allowing use a lot of parameters types. If one or more of those parameters are not necessary, use nullptr or create a new 'classify' method and set the 'allowClassifyMethod' following the documented rules.
			 * @note 'tmpToken' pointer, must be controlled by 'useTmpToken' boolean to determinate if the pointer will be used or not.
			 */
			virtual VersionLib::VersionTokenType classify (char* currentChar, std::string* strAcc, VersionLib::VersionTokenType* tokenType, VersionLib::VersionTokenType* lastTokenType, bool useTmpToken, VersionLib::VersionToken* tmpToken);

			/**
			 * @brief Try to classify the current given data. Set the pointers as nullptr to not use the variable.
			 * @param index Current index
			 * @param versionStr Version string
			 * @param currentChar Current character to analyze
			 * @param strAcc String accumulator
			 * @param tokenType Current token type classification
			 * @param lastTokenType Last token type classification
			 * @param useTmpToken Define if will 'tmpToken' pointer and it's data/create one
			 * @param tmpData Depending the implemented algorithm, may be easier to already provide the token data. Use the temporary token data as data transaction.
			 * @return If not identified the token, must return UNDEFINED_TOKEN.
			 * @note This method is a generic implementation, allowing use a lot of parameters types. If one or more of those parameters are not necessary, use nullptr or create a new 'classify' method and set the 'allowClassifyMethod' following the documented rules.
			 * @note 'tmpToken' pointer, must be controlled by 'useTmpToken' boolean to determinate if the pointer will be used or not.
			 */
			virtual VersionLib::VersionTokenType classify (size_t* index, std::string* versionStr, char* currentChar, std::string* strAcc, VersionLib::VersionTokenType* tokenType, VersionLib::VersionTokenType* lastTokenType, bool useTmpToken, VersionLib::VersionToken* tmpToken);

			//
			// Extraction methods:
			//

			/**
			 * @brief Direct token extraction from the own classifier
			 * @details This method is a internal token extraction implementation, if implemented, allowing to avoid use external functions to get the tokens from version string 
			 * @param version Version string. The format must be compatible with the classifier's implementation
			 * @return If not implemented or not compatible, should return an empty vector. Otherwise, it will return the tokens following the internal algorithm.
			 */
			virtual std::vector<VersionLib::VersionToken> extractTokens (std::string version);
	};
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY

#endif // !VERSION_LIB_TOKEN_CLASSIFIER_HPP