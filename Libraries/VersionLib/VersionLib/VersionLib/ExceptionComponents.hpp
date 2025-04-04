#pragma once

#ifndef VERSION_LIB_EXCEPTION_COMPONENTS_HPP
#define VERSION_LIB_EXCEPTION_COMPONENTS_HPP

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

#include <exception>
#include <cstring>
#include <string>
#include <array>

namespace VersionLib
{
	/**
	 * @brief Version Library Exception Codes
	 */
	enum VersionExceptionCode : int
	{
		VersionErrorCode_Std_Exception = -2,				// STL Exception
		VersionErrorCode_Unknown_Exception = -1,			// Unknown exception was found
		VersionErrorCode_Success,							// No exception was found. This code is only for status reporting.
		VersionErrorCode_Incorrect_Parameter,				// Incorrect parameter exception
		VersionErrorCode_Parameter_Value_Less_Than_Zero,	// Parameter exception with numeric value less than zero
		VersionErrorCode_Invalid_Nullptr_Data_Passed		// A nullptr was passed as argument in a unacceptable condition
	};

	/// @brief Get the error message from VersionExceptionCode
	inline const char* getErrorMessage (VersionLib::VersionExceptionCode code)
	{
		int codeInt = static_cast<int>(code);
		
		// Standard Version Library exception messages:
		const std::array<const char*, 4> VersionCodeExceptionMessages = 
		{
			"Success",
			"Incorrect parameter exception",
			"Parameter value less than zero",
			"A nullptr was passed as argument in a unacceptable condition"
		};

		if (codeInt >= 0 && codeInt < VersionCodeExceptionMessages.size())
		{
			return VersionCodeExceptionMessages[codeInt];
		}
		else
		{
			if (codeInt == -1)
			{
				return "Unknown exception";
			}

			if (codeInt == -2)
			{
				return "STL Exception";
			}

			return "";
		}
	}

	/**
	 * @brief Version Library Exception Component
	 */
	class VERSION_LIB_API VersionException : std::exception
	{
		protected:

			std::string msg_val;			// Exception message
			int code_val = 0;				// Exception code

		public:

			/**
			 * @brief Create an empty Version Library Exception
			 */
			VersionException ()
			{
				this->code_val = static_cast<int>(VersionLib::VersionExceptionCode::VersionErrorCode_Success);
				this->msg_val = "Success";
			}

			/**
			 * @brief Create a Version Library Exception based on std::exception information
			 * @param e STL Exception information
			 * @note The code exception is -2.
			 */
			VersionException (const std::exception& e)
			{
				this->code_val = static_cast<int>(VersionLib::VersionExceptionCode::VersionErrorCode_Std_Exception);
				this->msg_val = e.what();
			}

			/**
			 * @brief Create a Version Library Exception based on VersionExceptionCode and the exception message
			 * @param type Version Library Exception code type
			 * @param msg Exception message information
			 */
			VersionException (VersionLib::VersionExceptionCode type, const char* msg)
			{
				this->code_val = static_cast<int>(type);
				this->msg_val = msg;
			}

			/**
			 * @brief Create a Version Library Exception based on VersionExceptionCode
			 * @param type Version Library Exception code type
			 */
			VersionException (VersionLib::VersionExceptionCode type)
			{
				this->code_val = static_cast<int>(type);
				this->msg_val = VersionLib::getErrorMessage(type);
			}

			~VersionException()
			{
				
			}

			/**
			 * @brief Get the exception information about what happen
			 */
			const char* what() const noexcept
			{
				char* tmp_msg = nullptr;
				size_t msgSize = this->msg_val.size() + 1;
				tmp_msg = new char[msgSize];
				std::strcpy(tmp_msg, this->msg_val.c_str());
				return static_cast<const char*>(tmp_msg);
			}

			/**
			 * @brief Get the exception information and error code
			 */
			const char* msg()
			{
				std::string strMsg = "";
				strMsg = this->msg_val;
				strMsg += " | Code: " + std::to_string(this->code_val);
				size_t c_msg_size = strMsg.size() + 1;
				char* c_msg = new char[c_msg_size];
				std::strcpy(c_msg, strMsg.c_str());
				return static_cast<const char*>(c_msg);
			}

			/**
			 * @brief Get the exception code
			 */
			int code()
			{
				return this->code_val;
			}

			VersionLib::VersionException& operator= (const VersionLib::VersionException& other)
			{
				if (this == &other)
				{
					return *this;
				}

				this->code_val = other.code_val;
				this->msg_val = other.msg_val;
				
				return *this;
			}
	};
}

#endif // !VERSION_LIB_EXCEPTION_COMPONENTS_HPP