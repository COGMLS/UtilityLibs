#include "SettingsIniTools.hpp"

int SettingsLib::Tools::Ini::extractIniDataLine(std::string* line, std::string* sectionName, std::string* keyName, std::string* rawValue, std::string* comment)
{
	if (line == nullptr || sectionName == nullptr || keyName == nullptr || rawValue == nullptr || comment == nullptr)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_NULLPTR_ERROR;
	}

	// Local variables to store the extracted data before send to final variables:

	#ifdef DEBUG
	std::string lLine = *line;					// Local variable to access the pointer data
	#endif // !DEBUG

	std::string lSectionName = "";
	std::string lKeyName = "";
	std::string lRawValue = "";
	std::string lComment = "";

	// Control variables:

	// Search algorithm control:

	bool foundValidChar = false;				// Any character different of space
	bool foundSectionOpenMark = false;			// Found the mark SETTINGS_INI_OPEN_SECTION
	bool foundSectionCloseMark = false;			// Found the mark SETTINGS_INI_CLOSE_SECTION
	bool foundContainerOpenMark = false;		// Found the mark SETTINGS_INI_CONTAINER_OPEN_MARK
	bool foundContainerCloseMark = false;		// Found the mark SETTINGS_INI_CONTAINER_CLOSE_MARK

	// Experimental algorithm search and control variables:

	bool trimValueInvalidSpace = false;			// Removes the starting and ending space character while is in value checking
	bool trimCommentInvalidSpace = false;		// Removes the starting and ending space character while is in comment checking

	// Search stage control:

	bool chkForSection = false;					// Determinate the section checking stage
	bool chkForKey = false;						// Determinate the key checking stage
	bool chkForValue = false;					// Determinate the value checking stage
	bool chkForContainer = false;				// Determinate the container checking stage.
	bool chkForComment = false;					// Determinate the inline comment stage, commented line is controlled by isCommentedLine

	// Configuration line status:

	bool isEmptyLine = false;					// No other char was found or only empty spaces
	bool isEmptyComment = false;				// Determinate if is an empty comment (with only SETTINGS_INI_COMMENT_MARK or SETTINGS_INI_COMMENT_MARK2). This case should ignore the comment.
	bool isCommentedLine = false;				// First char was SETTINGS_INI_COMMENT_MARK or SETTINGS_INI_COMMENT_MARK2
	bool isSection = false;						// Founded a section data, can contain comments
	bool isContainerValueType = false;			// The first and last chars for data are SETTINGS_INI_CONTAINER_OPEN_MARK and SETTINGS_INI_CONTAINER_CLOSE_MARK.
	bool lineContainsComment = false;			// The line contains comments after other possible data (section, key and/or value)
	bool hasKey = false;						// The line contain a key. False for inexistent or invalid key (without SETTINGS_INI_DATA_MARK). True for a valid key (includes the SETTINGS_INI_DATA_MARK check).
	bool hasDataSetMark = false;				// The SETTINGS_INI_DATA_MARK to define the start of the data value
	
	int valueStatus = false;					// The line contain a key-value pair, including the SETTINGS_INI_DATA_MARK to define the start of the data value. 0 - Value doesn't exist. 1 - Empty value. 2 - Exist a extractable value.

	// Algorithm saved positions:

	size_t sectionStartPos = 0;					// Section substring start position
	size_t sectionEndPos = 0;					// Section substring end position

	size_t keyStartPos = 0;						// Key substring start position
	size_t keyEndPos = 0;						// Key substring end position

	size_t dataSetPos = 0;						// Data set mark to help to identify the value start point.

	size_t valueStartPos = 0;					// Value substring start position
	size_t valueEndPos = 0;						// Value substring end position. Assume the last valid character position, except when an inline comment exist
	
	size_t commentStartPos = 0;					// Comment substring start position

	// Local variables to analyze:

	char c = '\0';								// Temporary character to analyze

	// Define the last position:
	if (line->size() > 0)
	{
		valueEndPos = line->size() - 1;
	}

	// Define if is a empty line by the size:
	if (line->empty())
	{
		isEmptyLine = true;
	}

	// Algorithm starts here:

	for (size_t i = 0; i < line->size(); i++)
	{
		// Save in local var. the current character:
		c = line->at(i);

		//
		// Comment and empty line algorithm analysis:
		//

		// Jump the spaces before found a valid char
		if (c != SETTINGS_INI_SPACE_CHAR && !foundValidChar)
		{
			foundValidChar = true;

			// Verify if the first char is a commented line
			if (c == SETTINGS_INI_COMMENT_MARK || c == SETTINGS_INI_COMMENT_MARK2)
			{
				isCommentedLine = true;
				commentStartPos = i;
				/// @todo Consider to add the support to trim the space before the comment start
				break;
			}
		}

		// Avoid multiple verifications when a non valid character was found
		if (foundValidChar)
		{
			//
			// Comment algorithm analysis:
			//

			// The first character verification needs to be the for comments
			// If a comment was found and is not the first char, consider an inline comment for section or key-pair value
			if (c == SETTINGS_INI_COMMENT_MARK || c == SETTINGS_INI_COMMENT_MARK2 && !lineContainsComment)
			{
				lineContainsComment = true;
				commentStartPos = i;

				// If found a SETTINGS_INI_OPEN_SECTION without finding the SETTINGS_INI_CLOSE_SECTION, consider the section invalid and stop the section checking
				if (foundSectionOpenMark && !foundSectionCloseMark)
				{
					isSection = false;
					chkForSection = false;
				}

				// Any key that does not have a SETTINGS_INI_DATA_MARK, will not be considered as a valid key and the chkForKey will be disabled:
				if (chkForKey)
				{
					chkForKey = false;	// Disable the key checking
				}

				// By default the value is extracted until the line ends. But, if a comment appear, consider the last known position before the comment start:
				if (chkForValue)
				{
					valueEndPos = i - 1;
					chkForValue = false;	// Disable the value checking
				}

				// Verify for empty comments. Empty comments should be ignored
				if (i + 1 > line->size())
				{
					isEmptyComment = true;
					break;	// The comment if the last possible data that can be inside the line. If the comment if empty, break the line checking to avoid the unnecessary use of computation resources.
				}
			}

			//
			// Section algorithm analysis stage:
			//
			
			// If the SETTINGS_INI_OPEN_SECTION was found, verify for section's existence conditions and if the line still has characters for the section's name:
			if (c == SETTINGS_INI_OPEN_SECTION && !chkForSection && !chkForKey && !chkForValue && !lineContainsComment)
			{
				foundSectionOpenMark = true;
				chkForSection = true;			// Enable the section checking
				
				if (i + 1 < line->size())
				{
					sectionStartPos = i + 1;
				}
				else
				{
					chkForSection = false;		// Disable the section checking, a incomplete section was found
				}
			}

			// If found SETTINGS_INI_CLOSE_SECTION, set the section position:
			if (c == SETTINGS_INI_CLOSE_SECTION && chkForSection && !chkForKey && !chkForValue && !lineContainsComment)
			{
				foundSectionCloseMark = true;
				chkForSection = false;		// Disable the section checking

				if (i - 1 > 0)
				{
					sectionEndPos = i - 1;
				}
			}

			// While is in section name check, save the possible section name into local variable to previous analysis:
			//if (foundSectionOpenMark && !foundSectionCloseMark && c != SETTINGS_INI_OPEN_SECTION && c != SETTINGS_INI_OPEN_SECTION)
			//if (chkForSection && !lineContainsComment)
			//{
			//	lSectionName += c;
			//}

			// Determinate if is a valid section:
			if (foundSectionOpenMark && foundSectionCloseMark && (sectionEndPos - sectionStartPos) > 0 && !isSection)
			{
				isSection = true;
				chkForSection = false;
			}

			//
			// Key algorithm analysis stage:
			//

			// If is not a section, value or comment checking, verify if a key exists in current line:
			if (!chkForSection && !chkForKey && !chkForValue && !isSection && !lineContainsComment)
			{
				chkForKey = true;	// Enable key checking
			}

			/// @todo Add a test for key analysis, the key should not have spaces between then.
			//if (chkForKey)
			//{
			//	lKeyName += c;
			//}

			//
			// Data set algorithm analysis:
			//

			// When found a data mark set '=' start to identify the data
			if (c == SETTINGS_INI_DATA_MARK && !isSection && chkForKey && !chkForValue && !lineContainsComment)
			{
				hasDataSetMark = true;
				dataSetPos = i;				// Define the data set mark position to help to identify if the value type

				chkForKey = false;			// Disable the key checking
				chkForValue = true;			// Enable the value checking
				
				hasKey = true;				// Define the key status

				keyEndPos = i - 1;			// Define the key ending position

				// If isn't the last character position, prepare for value extraction:
				if (i + 1 < line->size())
				{
					valueStatus = 2;		// Define the value status
					valueStartPos = i + 1;	// Prepare the next position to test as the first value substring position
				}
				else
				{
					chkForValue = false;
					valueStatus = 1;		// Empty value

					// When value start and end positions are equal to zero and the key exists, will consider a key without value
					valueStartPos = 0;
					valueEndPos = 0;
				}
			}

			//
			// Value algorithm analysis stage:
			//

			// Extract the value:
			if (chkForValue)
			{
				// Jump to next non-space character to test if is a container or not:
				if (c == SETTINGS_INI_SPACE_CHAR && !chkForContainer)
				{
					if (i + 1 < line->size())
					{
						valueStartPos++;	// The jumped position can also be used to trim spaces
					}
				}
				else
				{
					// Enter in container checking if the first non-space char was SETTINGS_INI_CONTAINER_OPEN_MARK
					if (c == SETTINGS_INI_CONTAINER_OPEN_MARK && !chkForContainer)
					{
						chkForContainer = true;		// Enable container checking
					}
				}

				//
				// Container checking:
				//

				// Identify a SETTINGS_INI_CONTAINER_OPEN_MARK:
				if (c == SETTINGS_INI_CONTAINER_OPEN_MARK  && !foundContainerOpenMark && !foundContainerCloseMark && chkForContainer && !isContainerValueType && !lineContainsComment)
				{
					foundContainerOpenMark = true;
					valueStartPos = i;
				}

				// Identify a SETTINGS_INI_CONTAINER_CLOSE_MARK:
				// NOTE: This only can be detected if the first non-space char was the SETTINGS_INI_CONTAINER_OPEN_MARK
				if (c == SETTINGS_INI_CONTAINER_CLOSE_MARK && foundContainerOpenMark && !foundContainerCloseMark && chkForContainer && !isContainerValueType && !lineContainsComment)
				{
					foundContainerCloseMark = true;
					valueEndPos = i;
					chkForValue = false;
				}

				// Define as a container type if found the both container marks, define as container type:
				if (foundContainerOpenMark && foundContainerCloseMark && !isContainerValueType && chkForContainer)
				{
					chkForContainer = false;		// Disable container checking
					isContainerValueType = true;	// Define as a container type
				}
			}
		}
	}

	// If the line only contains spaces, consider an empty line:
	if (!foundValidChar)
	{
		isEmptyLine = true;
	}
	
	// If the trim value spaces and container identify are not enabled, restore the original value substring position:
	if (!trimValueInvalidSpace && !isContainerValueType)
	{
		valueStartPos = dataSetPos + 1;
	}
	
	// If the value is an empty string, change the value status:
	if (valueEndPos - valueStartPos == 0)
	{
		if (line->at(valueStartPos) == SETTINGS_INI_SPACE_CHAR)
		{
			valueStatus = 1;
		}
	}

	//
	// Extract the values from the line:
	//

	if (isSection && sectionEndPos > 0 && (sectionEndPos - sectionStartPos) >= 1)
	{
		lSectionName = line->substr(sectionStartPos, (sectionEndPos - sectionStartPos + 1));
	}

	// Extract key value:
	if (hasKey && keyEndPos > 0 && (keyEndPos - keyStartPos) >= 1)
	{
		lKeyName = line->substr(keyStartPos, (keyEndPos - keyStartPos + 1));
	}

	// Extract value substring:
	if (valueStatus == 2 && valueEndPos > 0 && (valueEndPos - valueStartPos) >= 1)
	{
		lRawValue = line->substr(valueStartPos, valueEndPos - valueStartPos + 1);

		if (lRawValue.empty())
		{
			valueStatus = 1;
		}
	}

	// Extract comment:
	if ((isCommentedLine || lineContainsComment) && !isEmptyLine)
	{
		lComment = line->substr(commentStartPos, line->size());
	}

	// Set the local values to the pointers:

	*sectionName = lSectionName;
	*keyName = lKeyName;
	*rawValue = lRawValue;
	*comment = lComment;

	// Prepare the return value:

	// Empty line:
	if (isEmptyLine)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_EMPTY_LINE;
	}

	// Commented line:
	if (isCommentedLine)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_COMMENTED_LINE;
	}

	// Section without comment:
	if (isSection && !lineContainsComment)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_SECTION;
	}

	// Section with comment:
	if (isSection && lineContainsComment)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_SECTION_WITH_COMMENTS;
	}

	// Empty key without comment:
	if (hasKey && hasDataSetMark && valueStatus != 2 && !lineContainsComment && !isContainerValueType)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_ONLY;
	}

	// Key with common value type and without comment:
	if (hasKey && hasDataSetMark && valueStatus == 2 && !lineContainsComment && !isContainerValueType)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE;
	}

	// Empty key with comment:
	if (hasKey && hasDataSetMark && valueStatus != 2 && lineContainsComment && !isContainerValueType)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_ONLY_WITH_COMMENTS;
	}

	// Key with common value and with comment:
	if (hasKey && hasDataSetMark && valueStatus == 2 && lineContainsComment && !isContainerValueType)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE_AND_COMMENTS;
	}

	// Key with container value type and without comment:
	if (hasKey && hasDataSetMark && valueStatus == 2 && !lineContainsComment && isContainerValueType)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE;
	}

	// Key with container value type and with comments:
	if (hasKey && hasDataSetMark && valueStatus == 2 && lineContainsComment && isContainerValueType)
	{
		return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE_AND_COMMENTS;
	}

	// Any return that didn't match with the valid situations should return FAIL TO DETERMINATE status:
    return SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_FAIL_TO_DETERMINATE;
}

int SettingsLib::Tools::Ini::identifyValueType (std::string* rawValue)
{
	if (rawValue == nullptr)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR;
	}

	bool isEmpty = true;
	bool isNegativeNumber = false;
	bool isInteger = true;
	bool isFpNumber = false;
	bool isString = false;
	bool isContainer = false;

	int boolValStatus = 0;

	bool foundNonSpaceChar = false;
	bool foundInvalidChar4Number = false;
	bool foundNumber = false;
	bool chkForBoolean = true;

	bool chkForContainer = false;
	bool foundContainerOpenMark = false;
	bool foundContainerCloseMark = false;

	size_t lastNonSpaceChar = 0;
	size_t containerOpenMark = 0;
	size_t containerCloseMark = 0;

	std::string lBoolTest = "";
	char c = '\0';

	if (rawValue->empty())
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY;
	}

	for (size_t i = 0; i < rawValue->size(); i++)
	{
		c = rawValue->at(i);

		if (c != SETTINGS_INI_SPACE_CHAR)
		{
			lastNonSpaceChar = i;
		}

		if (c != SETTINGS_INI_SPACE_CHAR && !foundNonSpaceChar)
		{
			isEmpty = false;
			foundNonSpaceChar = true;
			
			// Identify the first non-space character. If is negative signal, consider a negative value:
			if (c == SETTINGS_INI_DATA_TYPE_NEGATIVE_SIGNAL)
			{
				isNegativeNumber = true;
			}

			if (c == SETTINGS_INI_CONTAINER_OPEN_MARK)
			{
				chkForContainer = true;
				foundContainerOpenMark = true;
			}
		}

		// Test for container marks:

		if (c == SETTINGS_INI_CONTAINER_OPEN_MARK)
		{
			containerOpenMark++;
		}

		if (c == SETTINGS_INI_CONTAINER_CLOSE_MARK)
		{
			containerCloseMark++;
		}

		// Identify a boolean value:
		if (foundNonSpaceChar && chkForBoolean)
		{
			if (c != SETTINGS_INI_SPACE_CHAR)
			{
				lBoolTest += c;

				std::string tmp = lBoolTest;

				// Convert into lowercase:
				std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](unsigned char lCh){return std::tolower(lCh);});

				if (std::strcmp(lBoolTest.c_str(), SETTINGS_INI_DATA_TYPE_BOOL_FALSE) == 0)
				{
					boolValStatus = 1;
					chkForBoolean = false;
				}

				if (std::strcmp(lBoolTest.c_str(), SETTINGS_INI_DATA_TYPE_BOOL_TRUE) == 0)
				{
					boolValStatus = 2;
					chkForBoolean = false;
				}
			}
		}

		// Detect any invalid char:
		if (!foundInvalidChar4Number)
		{
			// Detect if is a decimal type:
			if (c == SETTINGS_INI_DATA_TYPE_DECIMAL || c == SETTINGS_INI_DATA_TYPE_EXPONENT_LOWER || c == SETTINGS_INI_DATA_TYPE_EXPONENT_UPPER)
			{
				isFpNumber = true;
				isInteger = false;
			}

			switch (c)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					foundNumber = true;
					break;
				}
				case SETTINGS_INI_DATA_TYPE_NEGATIVE_SIGNAL:
				case SETTINGS_INI_DATA_TYPE_POSITIVE_SIGNAL:
				case SETTINGS_INI_DATA_TYPE_DECIMAL:
				case SETTINGS_INI_DATA_TYPE_EXPONENT_LOWER:
				case SETTINGS_INI_DATA_TYPE_EXPONENT_UPPER:
				case SETTINGS_INI_SPACE_CHAR:
				{
					break;
				}
				default:
				{
					foundInvalidChar4Number = true;
					break;
				}
			}
		}

		if (foundInvalidChar4Number)
		{
			isInteger = false;
			isFpNumber = false;
		}

		// Disable any impossible verification:
		if (c == SETTINGS_INI_DATA_TYPE_STRING)
		{
			isInteger = false;
			isFpNumber = false;
			boolValStatus = 0;
			chkForBoolean = false;
		}

		// Check for container:
		if (chkForContainer)
		{
			if (c == SETTINGS_INI_CONTAINER_CLOSE_MARK && foundContainerOpenMark && !foundContainerCloseMark)
			{
				foundContainerCloseMark = true;
			}

			if (containerOpenMark > 1)
			{
				chkForContainer = false;
			}

			if (containerCloseMark > 1)
			{
				chkForContainer = false;
			}
		}
	}

	// Gather the search results:

	// Is possible a number:
	if (!foundInvalidChar4Number && !foundNumber)
	{
		isInteger = false;
		isFpNumber = false;
	}
	
	// Is possible a container:
	if (foundContainerOpenMark && foundContainerCloseMark && rawValue->at(lastNonSpaceChar) == SETTINGS_INI_SPACE_CHAR && containerOpenMark == 1 && containerCloseMark == 1)
	{
		isContainer = true;
	}

	// Is possible be a string:
	if (!isEmpty && !isInteger && !isFpNumber && boolValStatus == 0 && !isContainer && foundNonSpaceChar)
	{
		isString = true;
	}

	if (isNegativeNumber && isInteger && !isFpNumber)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_INTEGER;
	}

	if (!isNegativeNumber && isInteger && !isFpNumber)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_UNSIGNED_INTEGER;
	}

	if (!isInteger && isFpNumber)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FLOAT;
	}

	if (isContainer)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_CONTAINER_TYPE;
	}

	if (boolValStatus == 1 || boolValStatus == 2)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_BOOLEAN;
	}

	if (isString)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_STRING;
	}

	return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
}

int SettingsLib::Tools::Ini::convertNumber (std::string* rawValue, SettingsLib::Types::ConfigDataStore* valueStore)
{
	// Test the rawValue and type pointers, they can't be nullptr
	if (rawValue == nullptr)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR;
	}

	// To avoid the possibility to send a used union data:
	if (valueStore == nullptr)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR;
	}

	// Verify if the data holds a error type:
	if (valueStore->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_INIT_DATA_ERROR;
	}

	// Is the rawValue is empty, return a VALUE_EMPTY:
	if (rawValue->empty())
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY;
	}

	bool isNegativeValue = false;		// Possible negative value
	bool isFpNumber = false;			// Float point value
	bool isInteger = true;				// Assume true unless a decimal or exponent was found. NOTE: The Standard C++ string conversion functions does not convert correctly the integers with exponents.
	bool hasInvalidChar4Num = false;	// Any character different than numbers, dot and exponent and negative or positive. Spaces are ignored.

	bool foundNonSpaceChar = false;

	SettingsLib::ErrorCodes::IniRawValueConversionStatus returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY;

	if (!valueStore->cleanData())
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
	}

	char c = '\0';

	for (size_t i = 0; i < rawValue->size(); i++)
	{
		c = rawValue->at(i);

		// Identify the first non-space character. If is negative signal, consider a negative value:
		if (c != SETTINGS_INI_SPACE_CHAR && !foundNonSpaceChar)
		{
			foundNonSpaceChar = true;

			if (c == SETTINGS_INI_DATA_TYPE_NEGATIVE_SIGNAL)
			{
				isNegativeValue = true;
			}
		}

		// Detect if is a decimal type:
		if (c == SETTINGS_INI_DATA_TYPE_DECIMAL || c == SETTINGS_INI_DATA_TYPE_EXPONENT_LOWER || c == SETTINGS_INI_DATA_TYPE_EXPONENT_UPPER)
		{
			isFpNumber = true;
			isInteger = false;
		}

		// Stop the analysis:
		if (hasInvalidChar4Num)
		{
			break;
		}

		// Detect any invalid char:
		switch (c)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case SETTINGS_INI_DATA_TYPE_NEGATIVE_SIGNAL:
			case SETTINGS_INI_DATA_TYPE_POSITIVE_SIGNAL:
			case SETTINGS_INI_DATA_TYPE_DECIMAL:
			case SETTINGS_INI_DATA_TYPE_EXPONENT_LOWER:
			case SETTINGS_INI_DATA_TYPE_EXPONENT_UPPER:
			case SETTINGS_INI_SPACE_CHAR:
			{
				break;
			}
			default:
			{
				hasInvalidChar4Num = true;
				break;
			}
		}
	}

	// Consider a string when a invalid character was found:
	if (hasInvalidChar4Num)
	{
		returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_STRING;
	}

	// Try to convert the integer number:
	if (isInteger && !hasInvalidChar4Num)
	{
		bool isLL = false;
		bool isULL = false;
		long long cValue = 0ll;
		unsigned long long cValue2 = 0ull;

		// Test if the number is really a negative number:
		try
		{
			cValue = std::stoll(*rawValue);

			isLL = true;

			if (cValue < 0 && !isNegativeValue)
			{
				isNegativeValue = true;
			}
		}
		catch(const std::exception&)
		{
			// Do nothing.
		}

		// Test if the number is really a negative number:
		try
		{
			cValue2 = std::stoull(*rawValue);
			isULL = true;
		}
		catch(const std::exception&)
		{
			// Do nothing.
		}

		// The long long range is valid or a negative value was found:
		if (isLL && isULL || isNegativeValue)
		{
			if (valueStore->setData(cValue) == 0)
			{
				returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_INTEGER;
			}
			else
			{
				returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
			}
		}
		else if (isULL && !isLL && !isNegativeValue)	// The long long range is not valid and a negative value wasn't found
		{
			if (valueStore->setData(cValue2) == 0)
			{
				returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_UNSIGNED_INTEGER;
			}
			else
			{
				returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
			}
		}
		else	// Fail to apply the value, treat as a string:
		{
			returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_STRING;
		}
	}

	// Try convert the decimal number:
	if (isFpNumber && !hasInvalidChar4Num)
	{
		try
		{
			// Converted value:
			double cValue = 0.0;

			cValue = std::stod(*rawValue);

			if (valueStore->setData(cValue) == 0)
			{
				returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FLOAT;
			}
			else
			{
				returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
			}
		}
		catch(const std::exception&)
		{
			returnCode = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_UNKNOWN_ERROR;
		}
	}

	return returnCode;
}

int SettingsLib::Tools::Ini::convertValue(std::string* rawValue, SettingsLib::Types::ConfigDataStore* valueStore, bool trimSpaces)
{
	if (rawValue == nullptr)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR;
	}

	if (valueStore == nullptr)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR;
	}

	// Verify if the data holds a error type:
	if (valueStore->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_INIT_DATA_ERROR;
	}

	// If the rawValue is empty, return a VALUE_EMPTY:
	if (rawValue->empty())
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY;
	}

	//
	// Main conversion value controls:
	//

	bool isEmpty = false;					// Empty line
	bool isString = false;					// Determinate if is a string type. A literal string is determined when the first non-space character is a quote. Otherwise, will consider all data as string when foundLiteralStrOpenMark is false.
	bool isBoolean = false;					// Determinate if is a boolean type
	bool isNumber = true;					// Determinate if is a number (integer / decimal)

	int setDataStatus = -10;				// Hold the status code from setData from ConfigDataStore

	// Test conversion result:
	SettingsLib::ErrorCodes::IniRawValueConversionStatus conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY;

	bool foundNonSpaceChar = false;			// Help to identify when the current character is not part of string or only non-useful spaces
	bool isCurrentCharSpace = false;		// Determinate if the current char is space
	bool foundLiteralStrOpenMark = false;	// Determinate if the open quotes for literal string was found. If the close marks was found the open and close positions will be used to determinate the literal string (with quotes).

	size_t firstNonSpaceCharPos = 0;		// Determinate the first non space char position to help in trim the spaces before the data and identify the type
	size_t lastNonSpaceCharPos = 0;			// Determinate the last non space char position to help in trim the spaces
	size_t literalOpenQuotePos = 0;			// Help to determinate if is a literal string
	size_t literalCloseQuotePos = 0;		// Help to determinate if is a literal string
	size_t lastDataPos = 0;					// Last position to convert/extract the data

	if (rawValue->size() > 0)
	{
		lastDataPos = rawValue->size() - 1;	// Assume the data ends always when reach the last rawValue position
	}

	char c = '\0';							// Temporary character

	//
	// Number test controls:
	//

	bool isNegativeValue = false;		// Possible negative value
	bool isFpNumber = false;			// Float point value
	bool isInteger = true;				// Assume true unless a decimal or exponent was found. NOTE: The Standard C++ string conversion functions does not convert correctly the integers with exponents.
	bool hasInvalidChar4Num = false;	// Any character different than numbers, dot and exponent and negative or positive. Spaces are ignored.

	//
	// Boolean test controls:
	//

	int boolStatus = 0;					// Boolean status control. 0 - Not found a value. 1 - False value. 2 - True value.
	bool boolSearchFail = false;		// Stop the boolean search
	bool boolFalseSearchFail = false;
	bool boolTrueSearchFail = false;
	std::string falseStr = SETTINGS_INI_DATA_TYPE_BOOL_FALSE;
	std::string trueStr = SETTINGS_INI_DATA_TYPE_BOOL_TRUE;

	if (!valueStore->cleanData())
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
	}

	// Raw string value data analysis:
	for (size_t i = 0; i < rawValue->size(); i++)
	{
		c = rawValue->at(i);

		isCurrentCharSpace = false;

		// Jump the empty space that is not part of a possible data.
		// When a non space character is identified, the firstNonSpaceCharPos is marked with current position
		if (c == SETTINGS_INI_SPACE_CHAR)
		{
			isCurrentCharSpace = true;
		}
		else
		{
			if (!foundNonSpaceChar)
			{
				foundNonSpaceChar = true;
				firstNonSpaceCharPos = i;
			}

			lastNonSpaceCharPos = i;		// Save the last non-space char position
		}

		// Test only for numbers when a invalid char wasn't found:
		if (!hasInvalidChar4Num)
		{
			// Identify the first non-space character. If is negative signal, consider a possible negative value:
			if (c != SETTINGS_INI_SPACE_CHAR && !foundNonSpaceChar)
			{
				//foundNonSpaceChar = true;

				if (c == SETTINGS_INI_DATA_TYPE_NEGATIVE_SIGNAL)
				{
					isNegativeValue = true;
				}
			}

			// Detect if is a decimal type:
			if (c == SETTINGS_INI_DATA_TYPE_DECIMAL || c == SETTINGS_INI_DATA_TYPE_EXPONENT_LOWER || c == SETTINGS_INI_DATA_TYPE_EXPONENT_UPPER)
			{
				isFpNumber = true;
				isInteger = false;
			}

			// Detect any invalid char for number detection:
			switch (c)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case SETTINGS_INI_DATA_TYPE_NEGATIVE_SIGNAL:
				case SETTINGS_INI_DATA_TYPE_POSITIVE_SIGNAL:
				case SETTINGS_INI_DATA_TYPE_DECIMAL:
				case SETTINGS_INI_DATA_TYPE_EXPONENT_LOWER:
				case SETTINGS_INI_DATA_TYPE_EXPONENT_UPPER:
				case SETTINGS_INI_SPACE_CHAR:
				{
					break;
				}
				default:
				{
					hasInvalidChar4Num = true;
					break;
				}
			}

			// Stop the numeric analysis:
			if (hasInvalidChar4Num)
			{
				isNumber = false;
				isString = true;		// Assume it is a string, util confirm a boolean value
			}
		}

		// Test for boolean value:
		if (!boolSearchFail && !isBoolean)
		{
			// Test if is not a empty space after the possible string value start:
			if (foundNonSpaceChar)
			{
				char tmpC = std::tolower(c);

				// Test the false string value. For each char that obey the falseStr sequence, remove the first char position. If the sequence is broken, is not possible be a false value:
				if (!falseStr.empty() && !boolFalseSearchFail)
				{
					if (tmpC == falseStr[0])
					{
						falseStr.erase(falseStr.begin());

						if (falseStr.empty())
						{
							isBoolean = true;
							boolStatus = 1;
						}
					}
					else
					{
						boolFalseSearchFail = true;
					}
				}

				// Test the true string value. Use the same logic in falseStr test sequence to verify the true value:
				if (!trueStr.empty() && !boolTrueSearchFail)
				{
					if (tmpC == trueStr[0])
					{
						trueStr.erase(trueStr.begin());

						if (trueStr.empty())
						{
							isBoolean = true;
							boolStatus = 2;
						}
					}
					else
					{
						boolTrueSearchFail = true;
					}
				}
			}

			if (boolFalseSearchFail && boolTrueSearchFail)
			{
				boolSearchFail = true;
				isBoolean = false;
			}
		}

		// Start the analysis:
		if (foundNonSpaceChar)
		{
			// If the first non space char is a string mark, assume a possible literal string:
			if (c == SETTINGS_INI_DATA_TYPE_STRING && i == firstNonSpaceCharPos && !foundLiteralStrOpenMark)
			{
				literalOpenQuotePos = i;
				foundLiteralStrOpenMark = true;
				isString = true;
				isBoolean = false;
				boolSearchFail = true;
			}

			// If the first literal string mark was found, verify the possibility to find the close literal mark:
			// If a odd quantity of quotes was defined in rawValue, the last one will be used as final quote
			if (c = SETTINGS_INI_DATA_TYPE_STRING && i != firstNonSpaceCharPos && foundLiteralStrOpenMark)
			{
				literalCloseQuotePos = i;
				isString = true;
				isBoolean = false;
				boolSearchFail = true;
			}
		}
	}
	
	// Determinate if is a literal string or a normal string:
	if (foundLiteralStrOpenMark && isString && !isBoolean)
	{
		// Apply the value for literal string if pass the test otherwise, treat as a normal string:
		if (literalCloseQuotePos > literalOpenQuotePos)
		{
			if (trimSpaces)
			{
				if (firstNonSpaceCharPos < literalOpenQuotePos)
				{
					literalOpenQuotePos = firstNonSpaceCharPos;
				}

				if (lastNonSpaceCharPos > literalCloseQuotePos)
				{
					literalCloseQuotePos = lastNonSpaceCharPos;
				}
			}

			setDataStatus = valueStore->setData(rawValue->substr(literalOpenQuotePos, (literalCloseQuotePos - literalOpenQuotePos + 1)));

			if (setDataStatus == 0)
			{
				conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_STRING;
			}
			else
			{
				conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
			}
		}
		else
		{
			foundLiteralStrOpenMark = false;	// Make it ready to be treated as a normal string
		}
	}

	// If any specific test failed but, a non-space char was found, treat as a string:
	if (!foundLiteralStrOpenMark && isString && !isBoolean && !isNumber && foundNonSpaceChar)
	{
		//isString = true;

		if (trimSpaces)
		{
			if (lastDataPos > lastNonSpaceCharPos)
			{
				lastDataPos = lastNonSpaceCharPos;
				std::string buff = rawValue->substr(firstNonSpaceCharPos, (lastNonSpaceCharPos - firstNonSpaceCharPos + 1));
				setDataStatus = valueStore->setData(buff);
			}
			else
			{
				std::string buff = rawValue->substr(firstNonSpaceCharPos, rawValue->size());
				setDataStatus = valueStore->setData(buff);
			}
		}
		else
		{
			std::string buff = *rawValue;
			setDataStatus = valueStore->setData(buff);
		}

		if (setDataStatus == 0)
		{
			conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_STRING;
		}
		else
		{
			conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
		}
	}

	// If any specific test failed:
	if (!foundLiteralStrOpenMark && !isString && !isBoolean && isNumber && !foundNonSpaceChar)
	{
		isEmpty = true;
		conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY;
	}

	// If is a boolean value:
	if (isBoolean && boolStatus > 0)
	{
		if (boolStatus == 1)
		{
			setDataStatus = valueStore->setData(false);
		}
		else
		{
			setDataStatus = valueStore->setData(true);
		}

		if (setDataStatus == 0)
		{
			conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_BOOLEAN;
		}
		else
		{
			conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
		}
	}

	// For numbers, treat correctly here:
	if (isNumber)
	{
		// Try to convert the integer number:
		if (isInteger)
		{
			bool isULL = false;
			bool isLL = false;

			long long cValue = 0ll;
			unsigned long long cValue2 = 0ull;

			// Test if the number is really a negative number:
			try
			{
				cValue = std::stoll(*rawValue);

				isLL = true;

				if (cValue < 0 && !isNegativeValue)
				{
					isNegativeValue = true;
				}
			}
			catch(const std::exception&)
			{
				// Do nothing.
			}

			// Test if the number is really a negative number:
			try
			{
				cValue2 = std::stoull(*rawValue);
				isULL = true;
			}
			catch(const std::exception&)
			{
				// Do nothing.
			}

			// The long long range is valid or a negative value was found:
			if (isLL && isULL || isNegativeValue)
			{
				setDataStatus = valueStore->setData(cValue);
				
				if (setDataStatus == 0)
				{
					conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_INTEGER;
				}
				else
				{
					conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
				}
			}
			else if (isULL && !isLL && !isNegativeValue)	// The long long range is not valid and a negative value wasn't found
			{
				setDataStatus = valueStore->setData(cValue2);

				if (setDataStatus == 0)
				{
					conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_UNSIGNED_INTEGER;
				}
				else
				{
					conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
				}
			}
			else	// Fail to apply the value, treat as a string:
			{
				conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_UNKNOWN_ERROR;
			}
		}

		// Try convert the decimal number:
		if (isFpNumber)
		{
			try
			{
				// Converted value:
				double cValue = 0.0;

				cValue = std::stod(*rawValue);

				setDataStatus = valueStore->setData(cValue);

				if (setDataStatus == 0)
				{
					conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FLOAT;
				}
				else
				{
					conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
				}

			}
			catch(const std::exception&)
			{
				conversionStatus = SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_UNKNOWN_ERROR;
			}
		}
	}

	return conversionStatus;
}

long long SettingsLib::Tools::Ini::convertValue2Container(std::string *rawValue, std::vector<SettingsLib::Types::ConfigDataStore> *vData, bool trimSpaces)
{
	// Verify if the pointers are nullptr:

    if (rawValue == nullptr)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR;
	}

	if (vData == nullptr)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR;
	}

	// If the rawValue is empty, return VALUE_EMPTY:
	if (rawValue->empty())
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY;
	}

	//
	// Container controls:
	// 

	bool foundContainerStartMark = false;
	bool foundContainerEndMark = false;

	long long nEntries = 0;					// Count how many entries was generated on algorithm.
	size_t containerStartPos = 0;
	size_t containerEndPos = 0;
	
	// Hold the result from last entry check:
	SettingsLib::ErrorCodes::IniLineCheckStatus lastCheckStatus = SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_EMPTY_LINE;

	if (rawValue->size() > 0)
	{
		containerEndPos = rawValue->size() - 1;
	}

	char c = '\0';							// Temporary character

	// Detect the possible entries and literal strings:
	for (size_t i = 0, j = rawValue->size() - 1; i < rawValue->size() && j >= 0; i++, j--)
	{
		char c2 = rawValue->at(j);
		c = rawValue->at(i);

		if (c == SETTINGS_INI_CONTAINER_OPEN_MARK && !foundContainerStartMark)
		{
			foundContainerStartMark = true;
			containerStartPos = i;
		}

		if (c2 == SETTINGS_INI_CONTAINER_CLOSE_MARK && !foundContainerEndMark)
		{
			foundContainerEndMark = true;
			containerEndPos = j;
		}
	}

	// If is not a container:
	if (!foundContainerStartMark || !foundContainerEndMark)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL;
	}

	//
	// Extraction controls:
	//

	bool insertData = false;
	bool foundLiteralStrOpenMark = false;
	bool foundLiteralStrCloseMark = false;

	size_t literalStrOpenMarkPos = 0;
	size_t literalStrCloseMarkPos = 0;

	size_t startDataPos = containerStartPos + 1;
	size_t endDataPos = containerEndPos;
	
	std::string buffer;
	std::vector<std::string> rawEntries;	// Separated entries without treatment

	for (size_t i = containerStartPos + 1; i <= containerEndPos; i++)
	{
		c = rawValue->at(i);

		// Check for data insertion conditions:
		if (c == SETTINGS_INI_CONTAINER_VALUE_SEPARATOR || c == SETTINGS_INI_CONTAINER_CLOSE_MARK)
		{
			// In case a literal string was found:
			if (foundLiteralStrOpenMark && foundLiteralStrCloseMark)
			{
				insertData = true;
			}

			// In case a quote open mark was found and not closed, verify if the current position is the last inside the container:
			if (foundLiteralStrOpenMark && !foundLiteralStrCloseMark && i == containerEndPos)
			{
				insertData = true;
			}

			// In case a non literal string will be inserted:
			if (!foundLiteralStrOpenMark && !foundLiteralStrCloseMark)
			{
				insertData = true;
			}
		}

		// Insert the data:
		if (insertData)
		{
			// Take the substring data:
			if (foundLiteralStrCloseMark)
			{
				buffer = rawValue->substr(literalStrOpenMarkPos, (literalStrCloseMarkPos - literalStrOpenMarkPos) + 1);
			}
			else
			{
				buffer = rawValue->substr(startDataPos, (endDataPos - startDataPos) + 1);
			}

			// Insert the data:
			rawEntries.push_back(buffer);
			buffer.clear();
			nEntries++;
			insertData = false;

			// Reset the control variables:
			foundLiteralStrOpenMark = false;
			foundLiteralStrCloseMark = false;
			literalStrOpenMarkPos = 0;
			literalStrCloseMarkPos = 0;
		}

		if (c == SETTINGS_INI_CONTAINER_VALUE_SEPARATOR)
		{
			// Check for possible new data position:
			if (i <= containerEndPos && !foundLiteralStrOpenMark)
			{
				startDataPos = i + 1;
			}
		}
		else
		{
			if (!foundLiteralStrCloseMark)
			{
				endDataPos = i;
			}
		}

		// Check for close string marks only when an open mark was found:
		if (c == SETTINGS_INI_DATA_TYPE_STRING && foundLiteralStrOpenMark && !foundLiteralStrCloseMark)
		{
			foundLiteralStrCloseMark = true;
			literalStrCloseMarkPos = i;
		}

		// Check for open string marks:
		if (c == SETTINGS_INI_DATA_TYPE_STRING && !foundLiteralStrOpenMark && !foundLiteralStrCloseMark)
		{
			foundLiteralStrOpenMark = true;
			literalStrOpenMarkPos = i;
		}
	}

	long long nFails = 0;

	if (!rawEntries.empty())
	{
		for (size_t i = 0; i < rawEntries.size(); i++)
		{
			SettingsLib::Types::ConfigDataStore tmpStore;
			int convertStatus = SettingsLib::Tools::Ini::convertValue(&rawEntries[i], &tmpStore, trimSpaces);
			SettingsLib::ErrorCodes::IniRawValueConversionStatus convertStatusCode = static_cast<SettingsLib::ErrorCodes::IniRawValueConversionStatus>(convertStatus);

			switch (convertStatusCode)
			{
				case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY:
				case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_UNSIGNED_INTEGER:
				case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_INTEGER:
				case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FLOAT:
				case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_BOOLEAN:
				case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_STRING:
				case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_WSTRING:
				{
					vData->push_back(tmpStore);
					break;
				}
				default:
				{
					nFails++;
					break;
				}
			}
		}
	}

	if (nFails == 0)
	{
		return nEntries;
	}
	else
	{
		if (nEntries > nFails)
		{
			return -1;
		}

		return -2;
	}
}

int SettingsLib::Tools::Ini::trimSpaces(std::string *rawValue, std::string *newStr, bool trimBegin, bool trimEnd)
{
	// Verify if the pointers are nullptr:

    if (rawValue == nullptr)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR;
	}

	if (newStr == nullptr)
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR;
	}

	// If the rawValue is empty, return VALUE_EMPTY:
	if (rawValue->empty())
	{
		return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY;
	}

	// Make sure the newStr will only holds data from rawValue:
	newStr->clear();

	//
	// Trim variable controls:
	//

	std::string buffer;

	size_t firstNonSpaceChar = 0;
	size_t lastNonSpaceChar = 0;
	size_t lastDataPos = 0;

	bool isCurrentCharSpace = false;
	bool foundNonSpaceChar = false;

	if (rawValue->size() > 0)
	{
		lastDataPos = rawValue->size() - 1;
	}

	char c = '\0';

	// Start the raw string analysis:
	for (size_t i = 0; i < rawValue->size(); i++)
	{
		isCurrentCharSpace = false;

		c = rawValue->at(i);

		if (c == SETTINGS_INI_SPACE_CHAR)
		{
			isCurrentCharSpace = true;
		}
		else
		{
			if (!foundNonSpaceChar)
			{
				foundNonSpaceChar = true;
				firstNonSpaceChar = i;
			}
		}

		if (!isCurrentCharSpace)
		{
			lastNonSpaceChar = i;
		}
	}

	if (lastNonSpaceChar < lastDataPos)
	{
		lastDataPos = lastNonSpaceChar;
	}

	if (trimBegin && trimEnd)
	{
		buffer = rawValue->substr(firstNonSpaceChar, (lastDataPos - firstNonSpaceChar) + 1);
	}

	if (trimBegin && !trimEnd)
	{
		buffer = rawValue->substr(firstNonSpaceChar, (rawValue->size() - firstNonSpaceChar));
	}

	if (!trimBegin && trimEnd)
	{
		buffer = rawValue->substr(0, (lastDataPos - firstNonSpaceChar) + 1);
	}

	*newStr = buffer;

    return SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_STRING;
}

int SettingsLib::Tools::Ini::convertDataStore2Str(SettingsLib::Types::ConfigDataStore *data, std::string *strValue)
{
    if (data == nullptr)
	{
		return -1;
	}

	if (strValue == nullptr)
	{
		return -2;
	}

	SettingsLib::Types::ConfigDataType type = data->getDataType();

	switch (type)
	{
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING:
		{
			return -4;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL:
		{
			return -3;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY:
		{
			*strValue = "";
			return 0;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER:
		{
			unsigned long long ull = 0;
			if (data->getData(&ull) == 1)
			{
				*strValue = std::to_string(ull);
				return 0;
			}
			
			return 1;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER:
		{
			long long ll = 0;
			if (data->getData(&ll) == 1)
			{
				*strValue = std::to_string(ll);
				return 0;
			}
			
			return 1;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT:
		{
			double d = 0.0;
			if (data->getData(&d) == 1)
			{
				*strValue = std::to_string(d);
				return 0;
			}
			
			return 1;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING:
		{
			std::string s;
			if (data->getData(&s) == 1)
			{
				*strValue = s;
				return 0;
			}
			
			return 1;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING:
		{
			return -5;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN:
		{
			bool b = false;
			if (data->getData(&b) == 1)
			{
				if (b)
				{
					*strValue = SETTINGS_INI_DATA_TYPE_BOOL_TRUE;
				}
				else
				{
					*strValue = SETTINGS_INI_DATA_TYPE_BOOL_FALSE;
				}

				return 0;
			}

			return 1;
		}
		default:
		{
			return -6;	// Unknown value was send to test the type
		}
	}
}

int SettingsLib::Tools::Ini::convertDataStore2Str(SettingsLib::Types::ConfigDataStore *data, std::wstring *strValue)
{
    if (data == nullptr)
	{
		return -1;
	}

	if (strValue == nullptr)
	{
		return -2;
	}

	SettingsLib::Types::ConfigDataType type = data->getDataType();

	switch (type)
	{
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING:
		{
			return -4;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL:
		{
			return -3;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY:
		{
			*strValue = L"";
			return 0;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER:
		{
			unsigned long long ull = 0;
			if (data->getData(&ull) == 1)
			{
				*strValue = std::to_wstring(ull);
				return 0;
			}
			
			return 1;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER:
		{
			long long ll = 0;
			if (data->getData(&ll) == 1)
			{
				*strValue = std::to_wstring(ll);
				return 0;
			}
			
			return 1;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT:
		{
			double d = 0.0;
			if (data->getData(&d) == 1)
			{
				*strValue = std::to_wstring(d);
				return 0;
			}
			
			return 1;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING:
		{
			return -5;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING:
		{
			std::wstring w;
			if (data->getData(&w) == 1)
			{
				*strValue = w;
				return 0;
			}
			
			return 1;
		}
		case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN:
		{
			bool b = false;
			if (data->getData(&b) == 1)
			{
				if (b)
				{
					*strValue = SETTINGS_INI_DATA_TYPE_BOOL_TRUE_W;
				}
				else
				{
					*strValue = SETTINGS_INI_DATA_TYPE_BOOL_FALSE_W;
				}

				return 0;
			}

			return 1;
		}
		default:
		{
			return -6;	// Unknown value was send to test the type
		}
	}
}

int SettingsLib::Tools::Ini::convertObj2CfgLine(SettingsLib::Types::ConfigIniData *iniData, std::string *line)
{
	if (iniData == nullptr)
	{
		return -1;
	}

	if (line == nullptr)
	{
		return -2;
	}

	if (iniData->isWideData())
	{
		return 1;
	}

	std::string localLine;

	std::string key;
	std::string data;
	std::string comment;

	SettingsLib::ErrorCodes::ConfigIniStatus keyStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(iniData->getKey(&key));
	SettingsLib::ErrorCodes::ConfigIniStatus commentStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(iniData->getComment(&comment));
	std::vector<std::string> vStrData;

	if (iniData->isContainer())
	{
		size_t vDataMaxSize = iniData->getContainerSize();

		for (size_t i = 0; i < vDataMaxSize; i++)
		{
			std::string tmpValLine;
			SettingsLib::Types::ConfigDataStore data;

			if (iniData->getData(&data, i) == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
			{
				if (SettingsLib::Tools::Ini::convertDataStore2Str(&data, &tmpValLine) == 0)
				{
					vStrData.push_back(tmpValLine);
				}
			}
		}
	}
	else
	{
		SettingsLib::Types::ConfigDataStore data;
		SettingsLib::ErrorCodes::ConfigIniStatus dataStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(iniData->getData(&data));
		std::string tmpValLine;

		if (SettingsLib::Tools::Ini::convertDataStore2Str(&data, &tmpValLine) == 0)
		{
			vStrData.push_back(tmpValLine);
		}
	}

	if (iniData->isContainer())
	{
		data += SETTINGS_INI_CONTAINER_OPEN_MARK;
	}

	for (size_t i = 0; i < vStrData.size(); i++)
	{
		if (i + 1 == vStrData.size())
		{
			data += vStrData.at(i);
		}
		else
		{
			data += vStrData.at(i);
			data += SETTINGS_INI_CONTAINER_VALUE_SEPARATOR;
		}
	}

	if (iniData->isContainer())
	{
		data += SETTINGS_INI_CONTAINER_CLOSE_MARK;
	}

	if (keyStatus == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
	{
		localLine += key;
		localLine += SETTINGS_INI_DATA_MARK;
	}

	if (!vStrData.empty())
	{
		localLine += data;
	}

	if (!comment.empty())
	{
		localLine += SETTINGS_INI_SPACE_CHAR;
		localLine += SETTINGS_INI_COMMENT_MARK2;
		localLine += comment;
	}

	*line = localLine;

    return 0;
}

int SettingsLib::Tools::Ini::convertObj2CfgLine(SettingsLib::Types::ConfigIniData *iniData, std::wstring *line)
{
	if (iniData == nullptr)
	{
		return -1;
	}

	if (line == nullptr)
	{
		return -2;
	}

	if (!iniData->isWideData())
	{
		return 1;
	}

	std::wstring localLine;

	std::wstring key;
	std::wstring data;
	std::wstring comment;

	SettingsLib::ErrorCodes::ConfigIniStatus keyStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(iniData->getKey(&key));
	SettingsLib::ErrorCodes::ConfigIniStatus commentStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(iniData->getComment(&comment));
	std::vector<std::wstring> vStrData;

	if (iniData->isContainer())
	{
		size_t vDataMaxSize = iniData->getContainerSize();

		for (size_t i = 0; i < vDataMaxSize; i++)
		{
			std::wstring tmpValLine;
			SettingsLib::Types::ConfigDataStore data;

			if (iniData->getData(&data, i) == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
			{
				if (SettingsLib::Tools::Ini::convertDataStore2Str(&data, &tmpValLine) == 0)
				{
					vStrData.push_back(tmpValLine);
				}
			}
		}
	}
	else
	{
		SettingsLib::Types::ConfigDataStore data;
		SettingsLib::ErrorCodes::ConfigIniStatus dataStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(iniData->getData(&data));
		std::wstring tmpValLine;

		if (SettingsLib::Tools::Ini::convertDataStore2Str(&data, &tmpValLine) == 0)
		{
			vStrData.push_back(tmpValLine);
		}
	}

	if (iniData->isContainer())
	{
		data += SETTINGS_INI_CONTAINER_OPEN_MARK_W;
	}

	for (size_t i = 0; i < vStrData.size(); i++)
	{
		if (i + 1 == vStrData.size())
		{
			data += vStrData.at(i);
		}
		else
		{
			data += vStrData.at(i);
			data += SETTINGS_INI_CONTAINER_VALUE_SEPARATOR_W;
		}
	}

	if (iniData->isContainer())
	{
		data += SETTINGS_INI_CONTAINER_CLOSE_MARK_W;
	}

	if (keyStatus == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
	{
		localLine += key;
		localLine += SETTINGS_INI_DATA_MARK_W;
	}

	if (!vStrData.empty())
	{
		localLine += data;
	}

	if (!comment.empty())
	{
		localLine += SETTINGS_INI_SPACE_CHAR_W;
		localLine += SETTINGS_INI_COMMENT_MARK2_W;
		localLine += comment;
	}

	*line = localLine;

    return 0;
}