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
#include <memory>

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
 * 
*/

namespace VersionLib
{
	/**
	 * @brief Version Token Type identifier
	 * @note All token types with special meaning must be set after STRING_TOKEN
	 */
	enum VersionTokenType : unsigned short
	{
		FAIL_TO_IDENTIFY_TOKEN,						// THIS FLAG IS NOT A TOKEN IDENTIFICATION, but an error flag. Use only in exceptions and errors. Otherwise, use UNDEFINED_TOKEN.
		UNDEFINED_TOKEN,							// Token that was not identified. This value can appear when an empty token is used
		EMPTY_TOKEN,								// EMPTY token id
		SHORT_NUMERIC_TOKEN,						// Any type of numeric value inside the version that fits in the short integer (16-bits) range. It can be major, minor, patch or revision
		NUMERIC_TOKEN,								// Any type of numeric value inside the version, that does not fit in reduced memory layout (SHORT_NUMERIC_TOKEN). It can be major, minor, patch or revision
		LONG_NUMBER_TOKEN,							// Long numeric values hold by the token, this is focus for build compilation values that can be very high values or special versioning formats like __cplusplus macro.
		STRING_TOKEN,								// String elements or entire strings used to identify. To identify numeric values use NUMERIC_TOKEN or LONG_NUMERIC_TOKEN
		
		//
		// Token type special meaning section:
		//
		
		VERSION_TOKEN_VERSION_CORE_SEPARATOR,		// Version core component separators or identifiers. Normally used dot separators.
		VERSION_TOKEN_RELEASE_SEPARATOR,			// Separator that is used to identify the portions of Version Core and Version Release(s). On Semantic Versioning is used dash '-'
		VERSION_TOKEN_RELEASE_COMPONENT_DEFINITION,	// Unique version release component that identify the release or pre release information segment
		VERSION_TOKEN_RELEASE_REVISION_SEPARATOR,	// Separator identifiers used by release or pre release information segment. Normally used dot to separate between release information. I.e. alpha.15
		VERSION_TOKEN_BUILD_WORD,					// A word that can appear in some version informations formats that can be used as special token identifier
		VERSION_TOKEN_BUILD_VALUE,					// A special numeric value position that can express the build compilation value in some version formats
		VERSION_TOKEN_BUILD_SEPARATOR,				// A separator used to build compilation segment
		VERSION_TOKEN_METADATA_SEPARATOR,			// Unique version component that contains the version metadata information segment
		VERSION_TOKEN_GENERIC_SEPARATOR,			// Generic token mark to identify a verion separator
		VERSION_TOKEN_GENERIC_COMPONENT_DEFINITION,	// Generic token mark to identify a component version. It can be used to identify unique marks too.
		VERSION_TOKEN_GENERIC_VALUE					// Generic token value. Used to mark a content that could not be identified. I.e. Numerical values that are out of range.
	};

	/**
	 * @brief Version Token Data Type identifier
	 */
	enum VersionTokenDataType : short
	{
		EMPTY_DATA_TYPE = -1,		// Mark the Token Data as EMPTY data
		NULL_TYPE,					// Mark the Token Data as NULL data
		UNSIGNED_SHORT_TYPE,		// Flag to data type unsigend short
		UNSIGNED_INT_TYPE,			// Flag to data type unsigned int
		UNSIGNED_LONG_TYPE,			// Flag to data type unsigned long
		STRING_TYPE					// Flag to data type string
	};

	/**
	 * @brief Version Token Data Store. It holds any datatype that is identifiable from version information. It's possible to store strings and integers.
	 */
	class VERSION_LIB_API VersionTokenData
	{
		private:

			// Union for numeric values, designed to reduce memory usage
			union VersionTokenNumData
			{
				unsigned short short_data;					// Unsigned Short Integer data
				unsigned int int_data;						// Unsigned Integer data
				unsigned long long_data;					// Unsigned Long integer data
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
			 * @brief Create an object that holds an unsigned short data
			 * @param data Data that will be stored in the object
			 */
			VersionTokenData (unsigned short data);

			/**
			 * @brief Create an object that holds an unsigned int data
			 * @param data Data that will be stored in the object
			 */
			VersionTokenData (unsigned int data);

			/**
			 * @brief Create an object that holds an unsigned long data
			 * @param data Data that will be stored in the object
			 */
			VersionTokenData (unsigned long data);

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

			VersionLib::VersionTokenData& operator= (std::string& data);
			VersionLib::VersionTokenData& operator= (unsigned short& data);
			VersionLib::VersionTokenData& operator= (unsigned int& data);
			VersionLib::VersionTokenData& operator= (unsigned long& data);

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
			 * @brief Make a fast check with specific data type
			 * @param type Token data type
			 */
			bool isType (VersionLib::VersionTokenDataType type);

			/**
			 * @brief Check if the flag type is marked as EMPTY data
			 */
			bool isEmpty();

			/**
			 * @brief Check if the flag type is marked as NULL data
			 */
			bool isNull();

			/**
			 * @brief Check if the internal data is a numeric value (short, int or long)
			 * @note This function checks if has a numeric data, that could be a short, integer or long value
			 * @note To check if is using long, use method isLongVal
			 */
			bool isNumVal();

			/**
			 * @brief Check if the internal numeric data is int
			 */
			bool isIntVal();

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
			 * @brief Get the unsigned short integer value, if exist
			 * @return If exist, the unsigned short integer value will be returned. Otherwise, it will return zero.
			 * @note Check the data type TokenData holds before call this function
			 */
			unsigned short getShort();
			
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
			unsigned long getLong();

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

	/**
	 * @brief Version Library Token class. Holds the token pattern and the data that was detected from version string. It also holds the type of token and if is a mandatory component
	 */
	class VERSION_LIB_API VersionToken
	{
		private:

			int position;								// Token position. If set a negative value, it means there is no specific position
			bool mandatory;								// Indicate if the component must be part of the version to be validated
			VersionLib::VersionTokenType type;			// Indicate the type of token
			VersionLib::VersionTokenData data;			// Token data

		public:

			//
			// Constructors:
			//

			VersionToken();

			VersionToken (VersionLib::VersionTokenData data);

			VersionToken (VersionLib::VersionTokenData data, int position);
			
			VersionToken (VersionLib::VersionTokenData data, int position, bool mandatory);
			
			VersionToken (VersionLib::VersionTokenData data, VersionLib::VersionTokenType type);
			
			VersionToken (VersionLib::VersionTokenData data, VersionLib::VersionTokenType type, int position);
			
			VersionToken (VersionLib::VersionTokenData data, VersionLib::VersionTokenType type, int position, bool mandatory);
			
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
			VersionLib::VersionToken& operator= (VersionLib::VersionToken&& other) noexcept;

			VersionLib::VersionToken& operator= (std::string& val);
			VersionLib::VersionToken& operator= (unsigned short& val);
			VersionLib::VersionToken& operator= (unsigned int& val);
			VersionLib::VersionToken& operator= (unsigned long& val);

			bool operator== (VersionLib::VersionTokenType type);
			bool operator!= (VersionLib::VersionTokenType type);

			explicit operator bool() const;

			//
			// Check methods:
			//

			/**
			 * @brief Method to fast check the Token type
			 * @param type Token type
			 * @note This function differs from isType in VersionTokenData using more possible values that are more related about the 'meaning' of the token. I.e. A version core component is a string, but is treated as VERSION_TOKEN_VERSION_CORE_SEPARATOR.
			 */
			bool isType (VersionLib::VersionTokenType type);

			/**
			 * @brief Check if the token is optional on version composition
			 */
			bool isMandatory();

			/**
			 * @brief Check if the token is empty
			 */
			bool isEmpty();

			/**
			 * @brief Check if the token has a numerical value (short, int or long)
			 */
			bool isNumVal();

			/**
			 * @brief Check if the token has a short numerical value
			 */
			bool isShortVal();

			/**
			 * @brief Check if the token has a integer value
			 */
			bool isIntVal();

			/**
			 * @brief Check if the token has a long integer value
			 */
			bool isLongVal();

			/**
			 * @brief Check if the token has a string mark or the Token Data has a string
			 * @note Special token types can be strings. In this case this function will return true too.
			 */
			bool isStringVal();

			/**
			 * @brief Check if the token type has a special meaning
			 */
			bool isSpecialToken();

			//
			// Getters:
			//
			
			/**
			 * @brief Get the token position
			 * @return If the value is -1, it means the positioning is disabled for this token.
			 */
			int getPos();
			
			/**
			 * @brief Get the token data in string format.
			 * @note If the data is a numerical value, it will be converted to string
			 */
			std::string getTokenStr();
			
			/**
			 * @brief Get the token type
			 * @note This function does not related with Token Data Type
			 */
			VersionLib::VersionTokenType getType();
			
			/**
			 * @brief Get the TokenData
			 */
			VersionLib::VersionTokenData getTokenData();

			//
			// Setters:
			//

			/**
			 * @brief Define a position for the token
			 * @param position If the position is less than zero, it means the positioning is disabled
			 */
			void setPos (int position);

			/**
			 * @brief Define if the token is mandatory in version compositioning
			 * @param mandatory True enable the mandatory option
			 */
			void setMandatory (bool mandatory);

			/**
			 * @brief Set the token to a specific type
			 * @details This is useful to determinate special token identifications
			 * @param type Token type
			 * @warning Careful when applying a custom type, specially when the token type differs from the real data stored in TokenData
			 */
			void setTokenType (VersionLib::VersionTokenType type);

			/**
			 * @brief Change the internal token data to another
			 * @param data New token data
			 * @warning This method does not check or change the token type or other internal variables
			 */
			void setTokenData (VersionLib::VersionTokenData& data);
	};

	//
	// Version Token Tools:
	//

	/**
	 * @brief Convert the VersionTokenType to string
	 * @param type Token Type to be translated to string format
	 */
	std::string getTokenTypeStr (VersionLib::VersionTokenType type);
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM

#endif // !VERSION_LIB_TOKEN_HPP