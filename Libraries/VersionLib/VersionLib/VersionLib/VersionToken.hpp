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
		EMPTY_TOKEN,				// EMPTY token id
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
		EMPTY_DATA_TYPE = -1,
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

			// Union for numeric values, designed to reduce memory usage
			union VersionTokenNumData
			{
				unsigned int int_data;						// Unsigned Integer data
				unsigned long long long_data;				// Unsigned Long integer data
			};

			VersionLib::VersionTokenDataType type;			// Type of the data
			std::unique_ptr<std::string> strData;			// String data
			std::unique_ptr<VersionTokenNumData> numData;	// Numeric union data

		public:

			//
			// Constructors:
			//

			/**
			 * @brief Create an object marked as EMPTY data
			 */
			VersionTokenData();

			/**
			 * @brief Create an object that holds a string data
			 * @param data Data that will be stored in the object
			 */
			VersionTokenData (std::string data);

			/**
			 * @brief Create an object that holds an unsigned int data
			 * @param data Data that will be stored in the object
			 */
			VersionTokenData (unsigned int data);

			/**
			 * @brief Create an object that holds an unsigned long data
			 * @param data Data that will be stored in the object
			 */
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

			/**
			 * @brief Test if it has a data and if it holds a known data
			 */
			explicit operator bool() const;

			//
			// Checkers:
			//

			/**
			 * @brief Get the flag data type
			 */
			VersionLib::VersionTokenDataType getDataType();

			/**
			 * @brief Check if the flag type is marked as EMPTY data
			 */
			bool isEmpty();

			/**
			 * @brief Check if the flag type is marked as NULL data
			 */
			bool isNull();

			/**
			 * @brief Check if the internal data is a numeric value
			 * @note This function checks if has a numeric data, that could be a integer or long value
			 */
			bool isNumVal();

			/**
			 * @brief Check if the internal data is a unsigned long data
			 */
			bool isLongVal();

			/**
			 * @brief Check if the internal data is a string
			 */
			bool isStringVal();

			//
			// Getters:
			//

			/**
			 * @brief Get the string value, if exist
			 * @return If exist, the string value will be returned. Otherwise, it will return an empty string.
			 * @note Check the data type TokenData holds before call this function
			 */
			std::string getStr();
			
			/**
			 * @brief Get the unsigned integer value, if exist
			 * @return If exist, the unsigned integer value will be returned. Otherwise, it will return zero.
			 * @note Check the data type TokenData holds before call this function
			 */
			unsigned int getInt();
			
			/**
			 * @brief Get the long numeric value, if exist
			 * @return If exist, the unsigned long value will be returned. Otherwise, it will return zero.
			 * @note Check the data type TokenData holds before call this function
			 */
			unsigned long long getLong();

			//
			// Setters:
			//

			/**
			 * @brief Erase all internal data and reset the type flag to EMPTY data type
			 */
			void clear();

			/**
			 * @brief Set the type flag as NULL data
			 * @note If the TokenData has any type of data inside, it will call the clear method to erase all information first
			 */
			void setNull();
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