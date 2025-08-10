#pragma once

#ifndef SEM_VER_DICTIONARY_HPP
#define SEM_VER_DICTIONARY_HPP

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

#include "../ExperimentalFeatures.hpp"

#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY)

#include <string>
#include <vector>

#include "../TokenClassifier.hpp"
#include "../VersionToken.hpp"

#include "../BuildTypes.hpp"
#include "../CommonTools.hpp"
#include "../ReleaseTools.hpp"

/** Version Dictionaries header
 * --------------------------------------------------------
 * About:
 * 
 * This header contains all predefined TokenClassifiers that
 * can be used by the VersionData and also used by proper
 * version classes to deal with version strings
 * 
 * These classes does not allow internal data modification
 * and only works to provide an object that can process the
 * given data and reuse them in other process.
*/

namespace VersionLib
{
	namespace Dictionaries
	{
		class VERSION_LIB_API SemVerClassifier : public VersionLib::TokenClassifier
		{
			public:

				SemVerClassifier();

				~SemVerClassifier();

				std::vector<VersionLib::VersionToken> extractTokens (std::string version);
		};
	}
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY

#endif // !SEM_VER_DICTIONARY_HPP