#include "test.hpp"

int testToolsExtractIniData (int i, std::string* line, std::string* section, std::string* key, std::string* value, std::string* comment)
{
	int r = SettingsLib::Tools::Ini::extractIniDataLine(line, section, key, value, comment);
	std::string rs = "";

	std::cout << "--------------------------------" << std::endl;
	std::cout << "Post line analyze: " << std::endl;
	std::cout << "line (" << i << "): " << *line << std::endl;
	std::cout << "section: " << *section << std::endl;
	std::cout << "key: " << *key << std::endl;
	std::cout << "rawValue: " << *value << std::endl;
	std::cout << "comments: " << *comment << std::endl;

	SettingsLib::ErrorCodes::IniLineCheckStatus iniS = static_cast<SettingsLib::ErrorCodes::IniLineCheckStatus>(r);

	rs = translateIniLineCheckStatus(iniS);

	std::cout << "Return: " << rs << std::endl;
	std::cout << "Return Code: " << r << std::endl;

	return r;
}

int testToolsConvertValue (std::string* value, SettingsLib::Types::ConfigDataType* type, SettingsLib::Types::ConfigDataUnion* uData)
{
	SettingsLib::Types::ConfigDataUnion* auData = uData;
	int r2 = SettingsLib::Tools::Ini::convertValue(value, type, auData, false);
	std::string rs2 = "";

	SettingsLib::ErrorCodes::IniRawValueConversionStatus iniS2 = static_cast<SettingsLib::ErrorCodes::IniRawValueConversionStatus>(r2);

	rs2 = translateIniRawValueConversionStatus(iniS2);

	std::cout << "Conversion Status: " << rs2 << std::endl;
	std::cout << "Conversion Status Code: " << r2 << std::endl;

    return r2;
}
