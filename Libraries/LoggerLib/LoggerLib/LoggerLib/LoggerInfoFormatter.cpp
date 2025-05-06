#include "LoggerInfoFormatter.hpp"

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
