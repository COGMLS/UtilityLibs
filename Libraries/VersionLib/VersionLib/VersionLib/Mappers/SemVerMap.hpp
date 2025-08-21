#pragma once

#ifndef SEM_VER_MAPPER_HPP
#define SEM_VER_MAPPER_HPP

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

#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER)

#include "../TokenMapper.hpp"
#include "../Dictionaries/SemVerDict.hpp"

#include <vector>

namespace VersionLib
{
	namespace Mappers
	{
		/**
		 * @brief Semantic Versioning Mapper
		 */
		class VERSION_LIB_API SemVerMapper : public VersionLib::TokenMapper
		{
			public:

				SemVerMapper();

				~SemVerMapper();

				/**
				 * @brief Process a string version in Semantic Versioning format
				 * @param version_str Version data string
				 * @return Return the processToken value from token vector parameters
				 */
				int processTokens (std::string version_str);

				/**
				 * @brief Process the given tokens
				 * @param tokens 
				 * @return 
				 * @note When this method is called, all stored components are erased before start the analysis
				 */
				int processTokens (std::vector<VersionLib::VersionToken>& tokens);
		};
	}
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY && !VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER

#endif // !SEM_VER_MAPPER_HPP