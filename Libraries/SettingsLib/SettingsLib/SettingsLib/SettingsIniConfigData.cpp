#include "SettingsIniConfigData.hpp"

SettingsLib::Types::ConfigIniData::ConfigIniData()
{

}

SettingsLib::Types::ConfigIniData::ConfigIniData (std::string key)
{
	this->usingWideData = false;

	this->key = new SettingsLib::Types::ConfigDataStore(key);
}

SettingsLib::Types::ConfigIniData::ConfigIniData(std::wstring key)
{
	this->usingWideData = true;

	this->key = new SettingsLib::Types::ConfigDataStore(key);
}

SettingsLib::Types::ConfigIniData::~ConfigIniData()
{
	if (this->section != nullptr)
	{
		this->section->~ConfigDataStore();
	}

	this->key.~ConfigDataStore();

	if (this->data != nullptr)
	{
		this->data->~ConfigDataStore();
	}

	if (this->vdata != nullptr)
	{
		this->vdata->~vector();
	}

	if (this->comment != nullptr)
	{
		this->comment->~ConfigDataStore();
	}
}

bool SettingsLib::Types::ConfigIniData::isWideData()
{
	return this->usingWideData;
}

int SettingsLib::Types::ConfigIniData::cleanData()
{
	if (this->hasData())
	{
		if (this->isContainer())
		{
			try
			{
				delete this->vdata;
				this->vdata = nullptr;
			}
			catch(const std::exception&)
			{
				return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR;
			}
		}
		else
		{
			try
			{
				delete this->data;
				this->data = nullptr;
			}
			catch(const std::exception&)
			{
				return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR;
			}
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}

	return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_CLEAN_DATA_ALREADY_EMPTY;
}

int SettingsLib::Types::ConfigIniData::getType(ConfigDataType *type)
{
	if (type == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	if (this->hasData())
	{
		if (this->isContainer())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO;
		}

		*type = this->data->getDataType();

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::getType(ConfigDataType *type, size_t pos)
{
    if (type == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	if (this->hasData())
	{
		if (this->isContainer())
		{
			if (pos >= this->vdata->size())
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE;
			}

			try
			{
				SettingsLib::Types::ConfigDataType lType = this->vdata->at(pos).getDataType();
				*type = lType;
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
			}
			catch(const std::exception&)
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR;
			}
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

bool SettingsLib::Types::ConfigIniData::hasSection()
{
    return this->section != nullptr;
}

int SettingsLib::Types::ConfigIniData::removeSection()
{
	if (this->hasSection())
	{
		try
		{
			delete this->section;
			this->section = nullptr;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR;
		}
		
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

bool SettingsLib::Types::ConfigIniData::hasData()
{
	return this->data != nullptr || this->vdata != nullptr;
}

bool SettingsLib::Types::ConfigIniData::isContainer()
{
    return this->vdata != nullptr;
}
