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

namespace VersionLib
{
	/**
	 * @brief Version Library Exception Codes
	 */
	enum VersionCodeException : int
	{
		Version_Code_Std_Exception = -2,				// STL Exception
		Version_Code_Unknown_Exception = -1,			// Unknown exception was found
		Version_Code_Success,							// No exception was found. This code is only for status reporting.
		Version_Code_Incorrect_Parameter,				// Incorrect parameter exception
		Version_Code_Parameter_Value_Less_Than_Zero		// Parameter exception with numeric value less than zero
	};

	/**
	 * @brief Version Library Exception Component
	 */
	class VERSION_LIB_API VersionException : std::exception
	{
		private:

			void copyMsg (char* _msg)
			{
				size_t msg_val_size = std::strlen(_msg);
				
				if (this->msg_val != nullptr)
				{
					delete[] this->msg_val;
				}

				if (this->msg_val == nullptr)
				{
					this->msg_val = new char[msg_val_size];
				}

				std::strcpy(this->msg_val, _msg);
			}

			void copyMsg (const char* _msg)
			{
				size_t msg_val_size = std::strlen(_msg);
				
				if (this->msg_val != nullptr)
				{
					delete[] this->msg_val;
					this->msg_val = nullptr;
				}

				if (this->msg_val == nullptr)
				{
					this->msg_val = new char[msg_val_size];
				}

				std::strcpy(this->msg_val, _msg);
			}

		protected:

			char* msg_val = nullptr;		// Exception message
			int code_val = 0;				// Exception code

		public:

			/**
			 * @brief Create an empty Version Library Exception
			 */
			VersionException ()
			{
				this->code_val = static_cast<int>(VersionLib::VersionCodeException::Version_Code_Success);
				this->copyMsg("Success");
			}

			/**
			 * @brief Create a Version Library Exception based on std::exception information
			 * @param e STL Exception information
			 * @note The code exception is -2.
			 */
			VersionException (const std::exception& e)
			{
				this->code_val = static_cast<int>(VersionLib::VersionCodeException::Version_Code_Std_Exception);
				this->copyMsg(e.what());
			}

			/**
			 * @brief Create a Version Library Exception based on VersionCodeException and the exception message
			 * @param type Version Library Exception code type
			 * @param msg Exception message information
			 */
			VersionException (VersionLib::VersionCodeException type, const char* msg)
			{
				this->code_val = static_cast<int>(type);
				this->copyMsg(msg);
			}

			/**
			 * @brief Create a Version Library Exception based on VersionCodeException
			 * @param type Version Library Exception code type
			 */
			VersionException (VersionLib::VersionCodeException type)
			{
				this->code_val = static_cast<int>(type);
				switch (type)
				{
					case VersionCodeException::Version_Code_Success:
					{
						this->copyMsg("Success");
						break;
					}
					case VersionCodeException::Version_Code_Incorrect_Parameter:
					{
						this->copyMsg("Incorrect parameter exception");
						break;
					}
					case VersionCodeException::Version_Code_Parameter_Value_Less_Than_Zero:
					{
						this->copyMsg("Parameter value less than zero");
						break;
					}
					default:
					{
						this->copyMsg("Unknown exception");
						break;
					}
				}
			}

			~VersionException()
			{
				if (this->msg_val != nullptr)
				{
					delete[] this->msg_val;
					this->msg_val = nullptr;
				}
			}

			/**
			 * @brief Get the exception information about what happen
			 */
			const char* what()
			{
				char* tmp_msg = nullptr;
				if (this->msg_val != nullptr)
				{
					size_t msgSize = std::strlen(this->msg_val);
					tmp_msg = new char[msgSize];
					std::strcpy(tmp_msg, this->msg_val);
				}
				return static_cast<const char*>(tmp_msg);
			}

			/**
			 * @brief Get the exception information and error code
			 */
			const char* msg()
			{
				std::string strMsg = "";
				if (this->msg_val != nullptr)
				{
					strMsg = this->msg_val;
				}
				strMsg += " | Code: " + std::to_string(this->code_val);
				size_t c_msg_size = strMsg.size();
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
				if (this->msg_val != nullptr)
				{
					delete[] this->msg_val;
					this->msg_val = nullptr;
				}

				if (other.msg_val != nullptr)
				{
					size_t msgSize = strlen(other.msg_val);
					this->msg_val = new char[msgSize];
					std::strcpy(this->msg_val, other.msg_val);
				}
				return *this;
			}
	};
}

#endif // !VERSION_LIB_EXCEPTION_COMPONENTS_HPP