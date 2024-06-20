#include "SettingsLibTools.hpp"

int SettingsLib::Tools::storeFstream2Memory (std::fstream* fs, std::vector<std::string>* vMemStore, unsigned long long readLines, bool resetPosBeforeOp, bool seekBeginPostOp)
{
	try
	{
		if (fs == nullptr)
		{
			return 2;
		}

		if (vMemStore == nullptr)
		{
			return 3;
		}

		if (fs->is_open())
		{
			unsigned long long nLinesReaded = 0ull;

			if (resetPosBeforeOp)
			{
				fs->seekg(std::fstream::beg);
				fs->seekp(std::fstream::beg);
			}

			std::string line;

			while (std::getline(*fs, line))
			{
				if (readLines != 0)
				{
					if (nLinesReaded == readLines)
					{
						break;
					}
				}

				vMemStore->push_back(line);
				line.clear();

				nLinesReaded++;
			}

			if (seekBeginPostOp)
			{
				fs->seekg(std::fstream::beg);
				fs->seekp(std::fstream::beg);
			}

			return 0;
		}

		return 1;
	}
	catch(const std::exception& /*e*/)
	{
		return 4;
	}
}

int SettingsLib::Tools::initializeDataUnion (SettingsLib::Types::ConfigDataUnion* pData)
{
	if (pData == nullptr)
	{
		try
		{
			pData = new SettingsLib::Types::ConfigDataUnion;
			return 0;
		}
		catch(const std::exception&)
		{
			return -1;
		}
	}

	return 1;
}

int SettingsLib::Tools::initializeDataUnion (SettingsLib::Types::ConfigDataUnion* pData, SettingsLib::Types::ConfigDataType type)
{
	int i = initializeDataUnion(pData);

	if (i == 0)
	{
		if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
		{
			return 0;		// Created with success the union without initialyze the data (EMPTY DATA)
		}

		try
		{
			switch (type)
			{
				case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER:
				{
					pData->ull = 0;
				}
				case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTERGER:
				{
					pData->ll = 0;
				}
				case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT:
				{
					pData->d = 0.0;
				}
				case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING:
				{
					pData->s = new std::string;
				}
				case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN:
				{
					pData->b = false;
				}
				case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING:
				{
					pData->w = new std::wstring;
				}
				default:
				{
					return 4;		// Invalid configuration was send
				}
			}

			return 0;				// Created the union and initialyzed the data
		}
		catch(const std::exception&)
		{
			return 3;				// Fail to create and initialyze the data
		}
	}

	return i;						// Return 1 if a non nullptr was send or 2 if a catch condition occur in creation.
}

int SettingsLib::Tools::destroyDataUnion (SettingsLib::Types::ConfigDataUnion* pData, SettingsLib::Types::ConfigDataType type)
{
	if (pData == nullptr)
	{
		return 1;		// The pointer data is nullptr
	}

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return 3;		// Invalid type
	}

	try
	{
		if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			delete pData->s;
			pData->s = nullptr;
		}
		
		if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			delete pData->w;
			pData->w = nullptr;
		}

		delete pData;
		pData = nullptr;

		return 0;		// Successful operation
	}
	catch(const std::exception&)
	{
		return 2;		// Fail to destroy
	}
}