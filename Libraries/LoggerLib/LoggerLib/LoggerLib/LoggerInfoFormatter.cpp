#include "LoggerInfoFormatter.hpp"

#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER

LogFormatToken::LogFormatToken()
{
	this->id = LogFormatId::Unknown;
	this->data = "";
}

LogFormatToken::LogFormatToken(std::string token)
{
	this->id = LogFormatId::Unknown;

	for (size_t i = 0; i < LogFormatIdStr.size(); i++)
	{
		if (token == LogFormatIdStr[i])
		{
			this->id = static_cast<LogFormatId>(i);
			break;
		}
	}

	this->data = token;
}

LogFormatToken::LogFormatToken(LogFormatId id, std::string data)
{
	this->id = id;
	this->data = data;
}

LogFormatToken::LogFormatToken(const LogFormatToken &other)
{
	this->id = other.id;
	this->data = other.data;
}

LogFormatToken::LogFormatToken(LogFormatToken &&other) noexcept
{
	this->id = std::move(other.id);
	this->data = std::move(other.data);
}

LogFormatToken::~LogFormatToken()
{
}

LogFormatToken &LogFormatToken::operator=(const LogFormatToken &other)
{
    this->id = other.id;
	this->data = other.data;
	return *this;
}

LogFormatToken &LogFormatToken::operator=(LogFormatToken &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	this->id = std::move(other.id);
	this->data = std::move(other.data);

	return *this;
}

std::string LogFormatToken::operator+(const LogFormatToken &other)
{
    return other.data + this->data;
}

std::string LogFormatToken::operator+(const std::string &str)
{
    return str + this->data;
}

LogFormatId LogFormatToken::getId()
{
    return this->id;
}

std::string LogFormatToken::getData()
{
    return this->data;
}

void LogFormatToken::setData (std::string data)
{
	this->data = data;
}

LogFormat::LogFormat()
{
	this->emptyReplacer = "";
	this->formatTokens = createFormatTokens("{title}::{message} {data}");
}

LogFormat::LogFormat(std::string format, std::string emptyDataReplacer)
{
	this->emptyReplacer = emptyDataReplacer;
	this->formatTokens = createFormatTokens(format);
}

LogFormat::LogFormat(const LogFormat &other)
{
	this->formatTokens = other.formatTokens;
	this->emptyReplacer = other.emptyReplacer;
}

LogFormat::LogFormat(LogFormat &&other) noexcept
{
	this->formatTokens = std::move(other.formatTokens);
	this->emptyReplacer = std::move(other.emptyReplacer);
}

LogFormat::~LogFormat()
{
}

LogFormat &LogFormat::operator=(const LogFormat &other)
{
	if (this == &other)
	{
		return *this;
	}

	this->formatTokens = other.formatTokens;
	this->emptyReplacer = other.emptyReplacer;

	return *this;
}

LogFormat &LogFormat::operator=(LogFormat &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	this->formatTokens = std::move(other.formatTokens);
	this->emptyReplacer = std::move(other.emptyReplacer);

	return *this;
}

std::string LogFormat::formatInfo(std::vector<std::string> data)
{
	std::string formattedInfo = "";

	size_t i = 0;
	size_t j = 0;

	bool replaceToken = false;
	bool formatTokensProcessed = false;
	bool dataComponentsProcessed = false;

	while (!formatTokensProcessed && !dataComponentsProcessed)
	{
		replaceToken = false;
		if (i < this->formatTokens.size())
		{
			if (this->formatTokens[i].getId() != LogFormatId::Unknown)
			{
				replaceToken = true;
			}

			// If is not marked to replace the token data, use it in the final formatted string
			if (!replaceToken)
			{
				if (this->formatTokens[i].getData().empty())
				{
					formattedInfo += this->emptyReplacer;
				}
				else
				{
					formattedInfo += this->formatTokens[i].getData();
				}
			}

			i++;
		}
		else
		{
			if (!formatTokensProcessed)
			{
				formatTokensProcessed = true;	// All components on format tokens was analyzed
			}
		}

		if (j < data.size())
		{
			if (replaceToken)
			{
				formattedInfo += data[j];
				j++;
			}
			else
			{
				// If there are more items to add, include then in the final of formatted string
				if (i >= this->formatTokens.size())
				{
					formattedInfo += data[j];
					j++;
				}
			}
		}
		else
		{
			if (!dataComponentsProcessed)
			{
				dataComponentsProcessed = true;	// All string components was analyzed
			}
		}
	}

    return formattedInfo;
}

std::vector<LogFormatToken> createFormatTokens (std::string format)
{
	std::vector<std::string> tokens;
	std::vector<size_t> tokenMarks;
	
	size_t formatSize = format.size();

	char t = '\0';
	char l = '\0';

	size_t i = 0;
	size_t j = 0;
	size_t start = 0;
	size_t end = 0;

	bool foundOpenIdStr = false;
	bool foundCloseIdStr = false;
	bool analyzeFieldStr = false;
	bool isValidToken = false;

	for (i = 0; i < formatSize; i++)
	{
		// Update the actual char to analyze:
		t = format[i];

		// Check for the opening mark field:
		if (t != '{' && l == '{')
		{
			foundOpenIdStr = true;
			start = i - 1;
		}

		// Check for the closing mark field:
		if (t == '}' && l != '}')
		{
			foundCloseIdStr = true;
			end = i;

			// Add to analyze the field if found the opening and closing marks.
			// Otherwise, reset the flags and variables
			if (foundOpenIdStr)
			{
				analyzeFieldStr = true;
			}
			else
			{
				start = 0;
				end = 0;
				foundOpenIdStr = false;
				foundCloseIdStr = false;
				analyzeFieldStr = false;
			}
		}

		// Analyze the field:
		if (analyzeFieldStr)
		{
			#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
			std::cout << "Positions: start:[" << start << "]::" << format[start] << " | end:[" << end << "]::" << format[end] << " => " << format.substr(start, end - start + 1) << std::endl;
			#endif // !DEBUG and IOSTREAM
			
			// Check each possible token:
			for (j = 0; j < LogFormatIdStr.size(); j++)
			{
				isValidToken = false;

				// Test the token value:
				if (format.substr(start, end - start + 1) == LogFormatIdStr[j])
				{
					isValidToken = true;
				}

				// If is valid token, generate the object and separate from the last string portion:
				if (isValidToken)
				{
					tokenMarks.push_back(start);
					tokenMarks.push_back(end);
					break;
				}
			}

			// Reset all flags and control variables:
			start = 0;
			end = 0;
			foundOpenIdStr = false;
			foundCloseIdStr = false;
			analyzeFieldStr = false;
			isValidToken = false;
		}

		// Update the last char analyzed:
		l = t;
	}

	// Algorithm to make the substrings and inserting into 'tokens' vector
	for (i = 0; i < tokenMarks.size() - 1; i++)
	{
		if (i % 2 == 0)
		{
			// On pairs, create the identified tokens for ids:
			tokens.push_back(format.substr(tokenMarks[i], tokenMarks[i + 1] - tokenMarks[i] + 1));
		}
		else
		{
			// Identify the tokens that are support to additional format:
			tokens.push_back(format.substr(tokenMarks[i] + 1, tokenMarks[i + 1] - tokenMarks[i] - 1));
		}
	}

	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Analyze status:" << std::endl;
	std::cout << "---------------" << std::endl;
	std::cout << "String: " << format << std::endl;
	std::cout << "Marks: ";
	for (j = 0; j < tokenMarks.size(); j++)
	{
		std::cout << tokenMarks[j] << " ";
	}
	std::cout << std::endl;
	std::cout << "Tokens: " << std::endl;
	for (j = 0; j < tokens.size(); j++)
	{
		std::cout << "[" << j << "] " << tokens[j] << std::endl;
	}
	std::cout << std::endl;
	#endif // !DEBUG and IOSTREAM

	// Create the log tokens:
	std::vector<LogFormatToken> LogTokens;
	for (i = 0; i < tokens.size(); i++)
	{
		LogTokens.push_back(LogFormatToken(tokens[i]));
	}

	return LogTokens;
}

#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER