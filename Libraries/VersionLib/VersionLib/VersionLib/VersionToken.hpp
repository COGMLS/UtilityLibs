#pragma once

#ifndef VERSION_LIB_TOKEN_HPP
#define VERSION_LIB_TOKEN_HPP

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

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM

#include <string>
#include <vector>
#include <array>
#include <map>
#include <memory>
#include <list>

/** Generic Version Library Token components
 * --------------------------------------------------------
 * About token generation:
 * 
 * The token generation use rules and ids to identify the
 * version components, permitting developers to use easily
 * define custom versioning formats.
 * 
 * The token system consists in a generic class, VersionToken,
 * that can hold the data information about which part of the
 * version string component it's storing. This allows to use
 * version string reconstruction using a simple vector storing
 * the sequence of tokens and use the internal data to get the
 * numeric values to version classes.
 * 
 * Token Generation Rules:
 * 
 * The token generator look for strict two types of string
 * components: Token Marks (tm) and Token Separator (ts)
 * 
 * The Token Mars, can be used using three possible containers:
 * Braces {} : Block of components, can contain mandatory and
 * optional components combinations.
 * 
 * Brackets [] : Strict component that MUST be inside the version
 * string data
 * 
 * Parentheses () : Optional component the may be part of the
 * version string data
 * 
 * Additional Support:
 * 
 * Symbols support:
 * 
 * Symbol OR : |
 * Symbol AND : &
 * Symbol NOT : ! Must be on front of the component
 * 
 * --------------------------------------------------------
 * Example of Token Usage:
 * 
 * SemVer support:
 * 
 * [Major].[Minor].[Patch](-[[alpha|a]|[beta|b]|[release candidate|release_candidate|rc]](.[Revision]))
 * 
 * 
*/

namespace VersionLib
{
	/**
	 * @brief Version Token Type identifier
	 */
	enum VersionTokenType : unsigned short
	{
		UNDEFINED_TOKEN,			// Token that was not identified. This value can appear when an empty token is used
		UNKNOWN_TOKEN,				// Unknown token id
		NUMERIC_TOKEN,				// Any type of numeric value inside the version, like major, minor, patch or revision
		LONG_NUMBER_TOKEN,			// Long numeric values hold by the token, this is focus for build compilation values that can be very high values
		STRING_TOKEN,				// String elements or entire strings used to identify. To identify numeric values use NUMERIC_TOKEN or LONG_NUMERIC_TOKEN
		VERSION_MARK_TOKEN			// Any type of string mark that separates the version components
	};

	/**
	 * @brief Version Token Data Type identifier
	 */
	enum VersionTokenDataType : short
	{
		UNKNOWN_DATA_TYPE = -1,
		NULL_TYPE,
		UNSIGNED_INT_TYPE,
		UNSIGNED_LONG_LONG_TYPE,
		STRING_TYPE
	};

	/**
	 * @brief Version Token Data Store
	 */
	class VERSION_LIB_API VersionTokenData
	{
		private:

			union VersionTokenNumData
			{
				unsigned int int_data;
				unsigned long long long_data;
			};

			VersionLib::VersionTokenDataType type;			// Type of the data
			std::unique_ptr<std::string> strData;			// String data
			std::unique_ptr<VersionTokenNumData> numData;	// Numeric union data

		public:

			//
			// Constructors:
			//

			VersionTokenData();

			VersionTokenData (std::string data);

			VersionTokenData (unsigned int data);

			VersionTokenData (unsigned long long data);

			VersionTokenData (const VersionLib::VersionTokenData& other);

			VersionTokenData (VersionLib::VersionTokenData&& other) noexcept;

			//
			// Destructor:
			//

			~VersionTokenData();

			//
			// Operators:
			//

			VersionLib::VersionTokenData& operator= (const VersionLib::VersionTokenData& other);
			VersionLib::VersionTokenData& operator= (VersionLib::VersionTokenData&& other) noexcept;

			VersionLib::VersionTokenData& operator= (std::string data);
			VersionLib::VersionTokenData& operator= (unsigned int data);
			VersionLib::VersionTokenData& operator= (unsigned long long data);

			bool operator== (const VersionLib::VersionTokenData& other);
			bool operator== (VersionLib::VersionTokenDataType type);

			explicit operator bool() const;

			//
			// Checkers:
			//

			VersionLib::VersionTokenDataType getDataType();

			bool isNumVal();

			bool isLongVal();

			bool isStringVal();

			//
			// Getters:
			//

			std::string getStr();
			
			unsigned int getInt();
			
			unsigned long long getLong();
	};

	class VERSION_LIB_API VersionTokenSet
	{
		private:

			std::vector<std::string> set;

		public:

			VersionTokenSet (std::vector<std::string> set);

			~VersionTokenSet();
	};

	/**
	 * @brief Version Library Token class. Holds the token pattern and the data that was detected from version string. It also holds the type of token and if is a mandatory component
	 */
	class VERSION_LIB_API VersionToken
	{
		private:

			bool mandatory;												// Indicate if the component must be part of the version to be validated
			VersionLib::VersionTokenType type;							// Indicate the type of token
			std::vector<std::string> pattern_data;						// String values to be used to identify the type of token
			std::unique_ptr<std::string> str_data;						// String data store
			std::unique_ptr<VersionLib::VersionTokenData> num_data;		// Numerical values hold by a union

		public:

			//
			// Constructors:
			//

			VersionToken();

			VersionToken (std::string tokenPattern);

			VersionToken (std::string tokenPattern, bool mandatory);

			VersionToken (VersionLib::VersionTokenType type, std::string tokenPattern);

			VersionToken (VersionLib::VersionTokenType type, std::string tokenPattern, bool mandatory);

			VersionToken (const VersionLib::VersionToken& other);

			VersionToken (VersionLib::VersionToken&& other) noexcept;

			//
			// Destructor:
			//

			~VersionToken();

			//
			// Operators:
			//

			VersionLib::VersionToken& operator= (const VersionLib::VersionToken& other);
			VersionLib::VersionToken& operator= (VersionLib::VersionToken& other) noexcept;

			VersionLib::VersionToken& operator= (std::string& val);
			VersionLib::VersionToken& operator= (unsigned int& val);
			VersionLib::VersionToken& operator= (unsigned long long val);

			bool operator== (VersionLib::VersionTokenType type);

			explicit operator bool() const;

			//
			// Check methods:
			//

			bool isNumVal();

			bool isLongVal();
			
			VersionLib::VersionTokenType getType();

			//
			// Getters:
			//
			
			std::string getStrVal();

			unsigned int getIntVal();

			unsigned long long getLongVal();
	};

	/**
	 * @brief Version Library Token Map. It contains the entire token list and holds the token positions, used to recreate the string version from token elements.
	 */
	class VERSION_LIB_API VersionTokenMap
	{
		private:

			std::vector<VersionLib::VersionToken> tokens;

		public:

			VersionTokenMap(std::string version, std::vector<VersionLib::VersionToken> tokenList);

			~VersionTokenMap();
	};

	int setTokens (std::string version, std::vector<VersionLib::VersionToken>& token);

	std::map<std::string, VersionLib::VersionToken> genTokenMap (std::string version, std::string codedVersion);
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM

#endif // !VERSION_LIB_TOKEN_HPP