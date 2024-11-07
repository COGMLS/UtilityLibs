#include "SettingsIniConfigData.hpp"

SettingsLib::Types::ConfigIniData::ConfigIniData()
{
	this->objWasConfig = false;
	this->dataStoreType = 0;
}

SettingsLib::Types::ConfigIniData::ConfigIniData (std::string key)
{
	this->objWasConfig = true;
	this->usingWideData = false;
	this->dataStoreType = 0;
	this->key = key;
}

SettingsLib::Types::ConfigIniData::ConfigIniData(std::wstring key)
{
	this->objWasConfig = true;
	this->usingWideData = true;
	this->dataStoreType = 0;
	this->key = key;
}

SettingsLib::Types::ConfigIniData::ConfigIniData(const ConfigIniData &other)
{
	this->objWasConfig = other.objWasConfig;
	this->usingWideData = other.usingWideData;
	this->dataStoreType = other.dataStoreType;

	this->key = other.key;
	
	if (other.section != nullptr)
	{
		this->section.reset(new SettingsLib::Types::ConfigStrData(*other.section));
	}

	if (other.data != nullptr)
	{
		this->data.reset(new SettingsLib::Types::ConfigDataStore(*other.data));
	}

	if (other.vdata != nullptr)
	{
		this->vdata.reset(new std::vector<SettingsLib::Types::ConfigDataStore>(*other.vdata));
	}

	if (other.comment != nullptr)
	{
		this->comment.reset(new SettingsLib::Types::ConfigStrData(*other.comment));
	}
}

SettingsLib::Types::ConfigIniData::ConfigIniData(ConfigIniData &&other) noexcept
{
	this->objWasConfig = std::move(other.objWasConfig);
	this->usingWideData = std::move(other.usingWideData);
	this->dataStoreType = std::move(other.dataStoreType);

	this->key = std::move(other.key);

	if (other.section != nullptr)
	{
		this->section = std::move(other.section);
	}

	if (other.data != nullptr)
	{
		this->data = std::move(other.data);
	}

	if (other.vdata != nullptr)
	{
		this->vdata = std::move(other.vdata);
	}

	if (other.comment != nullptr)
	{
		this->comment = std::move(other.comment);
	}
}

SettingsLib::Types::ConfigIniData::~ConfigIniData()
{

}

SettingsLib::Types::ConfigIniData &SettingsLib::Types::ConfigIniData::operator=(const SettingsLib::Types::ConfigIniData &other)
{
	SettingsLib::ErrorCodes::ConfigIniStatus cleanDataStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanData());
	SettingsLib::ErrorCodes::ConfigIniStatus cleanCommentStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanComment());

	this->objWasConfig = other.objWasConfig;
	this->usingWideData = other.usingWideData;
	this->dataStoreType = other.dataStoreType;

	if (this->data.get() != nullptr)
	{
		this->data.reset(new SettingsLib::Types::ConfigDataStore(*other.data));
	}

	if (this->vdata.get() != nullptr)
	{
		this->vdata.reset(new std::vector<SettingsLib::Types::ConfigDataStore>(*other.vdata));
	}

	if (this->section.get() != nullptr)
	{
		this->section.reset(new SettingsLib::Types::ConfigStrData(*other.section));
	}

	if (this->comment.get() != nullptr)
	{
		this->comment.reset(new SettingsLib::Types::ConfigStrData(*other.comment));
	}

	return *this;
}

SettingsLib::Types::ConfigIniData &SettingsLib::Types::ConfigIniData::operator=(SettingsLib::Types::ConfigIniData &&other) noexcept
{
	SettingsLib::ErrorCodes::ConfigIniStatus cleanDataStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanData());
	SettingsLib::ErrorCodes::ConfigIniStatus cleanCommentStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanComment());

	this->objWasConfig = std::move(other.objWasConfig);
	this->usingWideData = std::move(other.usingWideData);
	this->dataStoreType = std::move(other.dataStoreType);

	if (other.section != nullptr)
	{
		this->section = std::move(other.section);
	}

	if (other.data != nullptr)
	{
		this->data = std::move(other.data);
	}

	if (other.vdata != nullptr)
	{
		this->vdata = std::move(other.vdata);
	}

	if (other.comment != nullptr)
	{
		this->comment = std::move(other.comment);
	}

	return *this;
}

bool SettingsLib::Types::ConfigIniData::isWideData()
{
	return this->usingWideData;
}

int SettingsLib::Types::ConfigIniData::resetConfigIniData()
{
	int cleanDataStatus = this->cleanData();
	int cleanCommentStatus = this->cleanComment();

	if (cleanCommentStatus > 0 || cleanDataStatus > 0)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_RESET_OBJECT_FAIL;
	}

	this->objWasConfig = false;
	this->usingWideData = false;

	return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
}

int SettingsLib::Types::ConfigIniData::cleanData()
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->hasData())
	{
		if (this->isContainer())
		{
			try
			{
				this->vdata.reset(nullptr);
				this->dataStoreType = 0;
			}
			catch(const std::exception&)
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR;
			}
		}
		else
		{
			try
			{
				this->data.reset(nullptr);
				this->dataStoreType = 0;
			}
			catch(const std::exception&)
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR;
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

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
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

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
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
    return this->section.get() != nullptr;
}

int SettingsLib::Types::ConfigIniData::removeSection()
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->hasSection())
	{
		try
		{
			this->section.reset(nullptr);
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR;
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::getSection(std::string *section)
{
	if (section == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->hasSection())
	{
		if (this->isWideData())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_STRING_DATA;
		}

		*section = this->section->getStr();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::getSection(std::wstring *section)
{
    if (section == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->hasSection())
	{
		if (!this->isWideData())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA;
		}

		*section = this->section->getStrW();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::setSection(std::string section)
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_STRING_DATA;
	}

	if (!this->hasSection())
	{
		try
		{
			this->section.reset(new SettingsLib::Types::ConfigStrData);
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	if (this->hasSection())
	{
		if (this->section->setStr(section))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}

		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_TO_SET;
}

int SettingsLib::Types::ConfigIniData::setSection(std::wstring section)
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (!this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA;
	}

	if (!this->hasSection())
	{
		try
		{
			this->section.reset(new SettingsLib::Types::ConfigStrData);
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	if (this->hasSection())
	{
		if (this->section->setStr(section))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}

		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_TO_SET;
}

int SettingsLib::Types::ConfigIniData::getKey(std::string *key)
{
	if (key == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_STRING_DATA;
	}

	*key = this->key.getStr();
	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
}

int SettingsLib::Types::ConfigIniData::getKey(std::wstring *key)
{
    if (key == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (!this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA;
	}

	*key = this->key.getStrW();
	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
}

int SettingsLib::Types::ConfigIniData::setKey(std::string key)
{
	if (key.empty())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
	}

	if (this->objWasConfig)
	{
		if (this->isWideData())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_STRING_DATA;
		}
	}

	if (this->key.setStr(key))
	{
		if (!this->objWasConfig)
		{
			this->objWasConfig = true;
			this->usingWideData = false;
		}
		
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}
	else
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}
}

int SettingsLib::Types::ConfigIniData::setKey(std::wstring key)
{
	if (key.empty())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
	}

	if (this->objWasConfig)
	{
		if (!this->isWideData())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA;
		}
	}

	if (this->key.setStr(key))
	{
		if (!this->objWasConfig)
		{
			this->objWasConfig = true;
			this->usingWideData = true;
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}
	else
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}
}

bool SettingsLib::Types::ConfigIniData::hasData()
{
	return this->data.get() != nullptr || this->vdata.get() != nullptr;
}

int SettingsLib::Types::ConfigIniData::getData(SettingsLib::Types::ConfigDataStore *data)
{
    if (data == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->hasData())
	{
		if (this->isContainer())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO;
		}

		try
		{
			bool success = false;

			if (this->data->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
			{
				std::string buff;
				if (this->data->getData(&buff) == 1)
				{
					success = data->setData(buff) == 0;
				}
			}
			else if (this->data->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
			{
				std::wstring buff;
				if (this->data->getData(&buff) == 1)
				{
					success = data->setData(buff) == 0;
				}
			}
			else
			{
				*data = this->data.get();
				success = true;
			}

			if (success)
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
			}
			else
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
			}
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
		}
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::setData(SettingsLib::Types::ConfigDataStore data)
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (!this->hasData())
	{
		try
		{
			this->data.reset(new SettingsLib::Types::ConfigDataStore);
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	if (!this->hasData())
	{
		this->dataStoreType = 1;
	}

	if (this->hasData())
	{
		if (this->isContainer())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO;
		}

		try
		{
			SettingsLib::Types::ConfigDataType type = data.getDataType();

			if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER)
			{
				unsigned long long buff = 0;
				if (data.getData(&buff) == 1)
				{
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER)
			{
				long long buff = 0;
				if (data.getData(&buff) == 1)
				{
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT)
			{
				double buff = 0.0;
				if (data.getData(&buff) == 1)
				{
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
			{
				std::string buff;
				if (data.getData(&buff) == 1)
				{
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN)
			{
				bool buff = false;
				if (data.getData(&buff) == 1)
				{
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
			{
				std::wstring buff;
				if (data.getData(&buff) == 1)
				{
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
				}
			}
			else
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
			}

			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
		}
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::setData(SettingsLib::Types::ConfigDataStore *data)
{
    if (data == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (!this->hasData())
	{
		try
		{
			this->data.reset(new SettingsLib::Types::ConfigDataStore);
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	if (this->hasData())
	{
		if (this->isContainer())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO;
		}

		try
		{
			*this->data = *data;
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
		}
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::getData(SettingsLib::Types::ConfigDataStore *data, size_t pos)
{
    if (data == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->hasData())
	{
		if (!this->isContainer())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE;
		}

		try
		{
			if (this->vdata->size() > pos)
			{
				SettingsLib::Types::ConfigDataStore tmpData = this->vdata->at(pos);
				*data = tmpData;
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
			}

			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
		}
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::getContainer(std::vector<SettingsLib::Types::ConfigDataStore> *vData)
{
	if (vData == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->hasData())
	{
		if (!this->isContainer())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE;
		}

		try
		{
			*vData = *this->vdata.get();
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
		}
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::insertData(SettingsLib::Types::ConfigDataStore data, size_t pos, bool overwrite)
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (!this->hasData())
	{
		try
		{
			this->vdata.reset(new std::vector<SettingsLib::Types::ConfigDataStore>);
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	if (!this->hasData())
	{
		this->dataStoreType = 2;
	}

	if (this->isContainer())
	{
		try
		{
			if (this->getContainerSize() > pos)
			{
				if (overwrite)
				{
					SettingsLib::Types::ConfigDataStore* tmpData = &this->vdata->at(pos);
					*tmpData = data;
				}
				else
				{
					auto posRef = this->vdata->begin();
					this->vdata->insert(posRef, pos, data);
				}
			}
			else
			{
				this->vdata->push_back(data);
			}
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE;
}

bool SettingsLib::Types::ConfigIniData::isContainer()
{
	if (this->hasData())
	{
    	return this->vdata.get() != nullptr;
	}

	return false;
}

size_t SettingsLib::Types::ConfigIniData::getContainerSize()
{
	if (this->isContainer())
	{
		return this->vdata->size();
	}

	return 0;
}

bool SettingsLib::Types::ConfigIniData::hasComment()
{
    return this->comment.get() != nullptr;
}

int SettingsLib::Types::ConfigIniData::cleanComment()
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->hasComment())
	{
		try
		{
			this->comment.reset(nullptr);
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR;
		}
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::getComment(std::string *comment)
{
	if (comment == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_STRING_DATA;
	}

	if (!this->hasComment())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
	}

	try
	{
		*comment = this->comment->getStr();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}
	catch(const std::exception&)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
	}
}

int SettingsLib::Types::ConfigIniData::getComment(std::wstring *comment)
{
    if (comment == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (!this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA;
	}

	if (!this->hasComment())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
	}

	try
	{
		*comment = this->comment->getStrW();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}
	catch(const std::exception&)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
	}
}

int SettingsLib::Types::ConfigIniData::setComment(std::string comment)
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_STRING_DATA;
	}

	if (!this->hasComment())
	{
		try
		{
			this->comment.reset(new SettingsLib::Types::ConfigStrData);
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	try
	{
		bool hasCommentMark = comment.starts_with(SETTINGS_INI_COMMENT_MARK) || comment.starts_with(SETTINGS_INI_COMMENT_MARK2);

		if (!hasCommentMark)
		{
			comment = SETTINGS_INI_COMMENT_MARK2 + comment;
		}

		if (this->comment->setStr(comment))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}
	catch(const std::exception&)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}
}

int SettingsLib::Types::ConfigIniData::setComment(std::wstring comment)
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED;
	}

	if (!this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA;
	}

	if (!this->hasComment())
	{
		try
		{
			this->comment.reset(new SettingsLib::Types::ConfigStrData);
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	try
	{
		bool hasCommentMark = comment.starts_with(SETTINGS_INI_COMMENT_MARK) || comment.starts_with(SETTINGS_INI_COMMENT_MARK2);
		std::wstring tmpComment;

		if (!hasCommentMark)
		{
			tmpComment += SETTINGS_INI_COMMENT_MARK2_W;
		}

		tmpComment += comment;

		if (this->comment->setStr(tmpComment))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}
	catch(const std::exception&)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData()
{
	this->isSectionConfigured = false;
	this->useWideData = false;
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(std::string section)
{
	this->isSectionConfigured = true;
	this->useWideData = false;
	this->sectionName.setData(section);
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(std::wstring section)
{
	this->isSectionConfigured = true;
	this->useWideData = true;
	this->sectionName.setData(section);
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(const ConfigIniSectionData &other)
{
	this->isSectionConfigured = other.isSectionConfigured;
	this->useWideData = other.useWideData;

	this->sectionName = other.sectionName;

	if (this->useWideData)
	{
		this->wKeyMap = other.wKeyMap;
	}
	else
	{
		this->keyMap = other.keyMap;
	}

	if (other.comment != nullptr)
	{
		this->comment.reset(new SettingsLib::Types::ConfigDataStore(*other.comment));
	}
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(ConfigIniSectionData &&other) noexcept
{
	this->isSectionConfigured = other.isSectionConfigured;
	this->useWideData = other.useWideData;

	this->sectionName = other.sectionName;

	if (this->useWideData)
	{
		this->wKeyMap = std::move(other.wKeyMap);
	}
	else
	{
		this->keyMap = std::move(other.keyMap);
	}

	this->comment = std::move(other.comment);
}

SettingsLib::Types::ConfigIniSectionData::~ConfigIniSectionData()
{

}

SettingsLib::Types::ConfigIniSectionData &SettingsLib::Types::ConfigIniSectionData::operator=(const SettingsLib::Types::ConfigIniSectionData &other)
{
    this->isSectionConfigured = other.isSectionConfigured;
	this->useWideData = other.useWideData;

	this->sectionName = other.sectionName;

	if (this->useWideData)
	{
		this->wKeyMap = other.wKeyMap;
	}
	else
	{
		this->keyMap = other.keyMap;
	}

	if (other.comment != nullptr)
	{
		this->comment.reset(new SettingsLib::Types::ConfigDataStore(*other.comment));
	}

	return *this;
}

SettingsLib::Types::ConfigIniSectionData &SettingsLib::Types::ConfigIniSectionData::operator=(SettingsLib::Types::ConfigIniSectionData &&other) noexcept
{
    this->isSectionConfigured = other.isSectionConfigured;
	this->useWideData = other.useWideData;

	this->sectionName = other.sectionName;

	if (this->useWideData)
	{
		this->wKeyMap = std::move(other.wKeyMap);
	}
	else
	{
		this->keyMap = std::move(other.keyMap);
	}

	this->comment = std::move(other.comment);

	return *this;
}

int SettingsLib::Types::ConfigIniSectionData::getSectionName(std::string* sectionName)
{
	if (sectionName == nullptr)
	{
		return -3;
	}

	if (this->isSectionConfigured)
	{
		if (this->useWideData)
		{
			return -2;
		}

		if (this->sectionName.getData(sectionName) == 1)
		{
			return 1;
		}

		return 0;
	}

	return -1;
}

int SettingsLib::Types::ConfigIniSectionData::getSectionName(std::wstring* sectionName)
{
	if (sectionName == nullptr)
	{
		return -3;
	}

	if (this->isSectionConfigured)
	{
		if (!this->useWideData)
		{
			return -2;
		}

		if (this->sectionName.getData(sectionName) == 1)
		{
			return 1;
		}

		return 0;
	}

	return -1;
}

int SettingsLib::Types::ConfigIniSectionData::getComment(std::string *comment)
{
    if (comment == nullptr)
	{
		return -1;
	}

	SettingsLib::Types::ConfigDataType type = static_cast<SettingsLib::Types::ConfigDataType>(this->comment->getDataType());

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING)
	{
		return -2;
	}

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -3;
	}

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 1;
	}

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		if (this->useWideData)
		{
			return -4;
		}
	}

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		int status = this->comment->getData(comment);

		if (status == 1)
		{
			return 0;
		}

		return -5;
	}

	return -6;
}

int SettingsLib::Types::ConfigIniSectionData::getComment(std::wstring *comment)
{
    if (comment == nullptr)
	{
		return -1;
	}

	SettingsLib::Types::ConfigDataType type = static_cast<SettingsLib::Types::ConfigDataType>(this->comment->getDataType());

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING)
	{
		return -2;
	}

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -3;
	}

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 1;
	}

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		if (this->useWideData)
		{
			return -4;
		}
	}

	if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		int status = this->comment->getData(comment);

		if (status == 1)
		{
			return 0;
		}

		return -5;
	}

	return -6;
}

int SettingsLib::Types::ConfigIniSectionData::setComment(std::string comment)
{
	if (this->useWideData)
	{
		return -1;
	}

	int status = this->comment->setData(comment);

	return status;
}

int SettingsLib::Types::ConfigIniSectionData::setComment(std::wstring comment)
{
	if (!this->useWideData)
	{
		return -1;
	}

	int status = this->comment->setData(comment);

	return status;
}

bool SettingsLib::Types::ConfigIniSectionData::cleanComment()
{
	return this->comment->cleanData();
}

bool SettingsLib::Types::ConfigIniSectionData::hasComment()
{
    if (this->comment == nullptr)
	{
		return false;
	}

	return true;
}

int SettingsLib::Types::ConfigIniSectionData::getIniData(std::string key, SettingsLib::Types::ConfigIniData *iniData)
{
	if (iniData == nullptr)
	{
		return -3;
	}

    if (this->isSectionConfigured)
	{
		if (this->useWideData)
		{
			return -2;
		}

		if (this->keyMap.contains(key))
		{
			SettingsLib::Types::ConfigIniData* data = &this->keyMap.at(key);
			*iniData = *data;
			return 1;
		}

		return 0;
	}

	return -1;
}

int SettingsLib::Types::ConfigIniSectionData::getIniData(std::wstring key, SettingsLib::Types::ConfigIniData *iniData)
{
	if (iniData == nullptr)
	{
		return -3;
	}

    if (this->isSectionConfigured)
	{
		if (!this->useWideData)
		{
			return -2;
		}

		if (this->wKeyMap.contains(key))
		{
			SettingsLib::Types::ConfigIniData* data = &this->wKeyMap.at(key);
			*iniData = *data;
			return 1;
		}

		return 0;
	}

	return -1;
}

SettingsLib::Types::ConfigIniData *SettingsLib::Types::ConfigIniSectionData::getIniEntryRef(std::string key)
{
	if (this->isSectionConfigured && !this->useWideData && !this->keyMap.empty())
	{
		if (this->keyMap.contains(key))
		{
			return &this->keyMap.at(key);
		}
	}

    return nullptr;
}

SettingsLib::Types::ConfigIniData *SettingsLib::Types::ConfigIniSectionData::getIniEntryRef(std::wstring key)
{
    if (this->isSectionConfigured && this->useWideData && !this->wKeyMap.empty())
	{
		if (this->wKeyMap.contains(key))
		{
			return &this->wKeyMap.at(key);
		}
	}

    return nullptr;
}

size_t SettingsLib::Types::ConfigIniSectionData::getIniDatabaseSize()
{
	if (this->isSectionConfigured)
	{
		return 0;
	}

	if (this->useWideData)
	{
		return this->wKeyMap.size();
	}
	else
	{
		return this->keyMap.size();
	}
}

bool SettingsLib::Types::ConfigIniSectionData::isConfigured()
{
    return this->isSectionConfigured;
}

bool SettingsLib::Types::ConfigIniSectionData::isWideData()
{
    return this->useWideData;
}

int SettingsLib::Types::ConfigIniSectionData::addData(SettingsLib::Types::ConfigIniData &data)
{
	if (this->isSectionConfigured)
	{
		if (data.isWideData())
		{
			if (!this->useWideData)
			{
				return -2;
			}

			std::wstring key;
			SettingsLib::ErrorCodes::ConfigIniStatus status = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(data.getKey(&key));

			if (status == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
			{
				try
				{
					bool isEmpty = this->wKeyMap.empty();
					bool foundKey = this->wKeyMap.contains(key);

					if (!foundKey || isEmpty)
					{
						this->wKeyMap.insert({key, data});
						return 1;
					}
					else
					{
						auto p = &this->wKeyMap.at(key);
						*p = data;
						return 2;
					}
				}
				catch(const std::exception&)
				{
					return -1;
				}
			}

			return 0;
		}
		else
		{
			if (this->useWideData)
			{
				return -2;
			}

			std::string key;
			int statusI = data.getKey(&key);
			SettingsLib::ErrorCodes::ConfigIniStatus status = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(statusI);

			if (status == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
			{
				try
				{
					bool isEmpty = this->keyMap.empty();
					bool foundKey = this->keyMap.contains(key);
					
					if (!foundKey || isEmpty)
					{
						this->keyMap.insert({key, data});
						return 1;
					}
					else
					{
						auto p = &this->keyMap.at(key);
						*p = data;
						return 2;
					}
				}
				catch(const std::exception&)
				{
					return -1;
				}
			}

			return 0;
		}
	}

	return -3;
}

int SettingsLib::Types::ConfigIniSectionData::contains(std::string key)
{
	if (!this->isSectionConfigured)
	{
		return -3;
	}

	if (this->useWideData)
	{
		return -2;
	}

	if (this->keyMap.empty())
	{
		return -1;
	}

	if (this->keyMap.contains(key))
	{
		return 1;
	}

    return 0;
}

int SettingsLib::Types::ConfigIniSectionData::contains(std::wstring key)
{
	if (!this->isSectionConfigured)
	{
		return -3;
	}

	if (!this->useWideData)
	{
		return -2;
	}

	if (this->wKeyMap.empty())
	{
		return -1;
	}

	if (this->wKeyMap.contains(key))
	{
		return 1;
	}

    return 0;
}

int SettingsLib::Types::ConfigIniSectionData::remData(std::string key)
{
	if (!this->isSectionConfigured)
	{
		return -3;
	}

	if (this->useWideData)
	{
		return -2;
	}

	if (this->keyMap.empty())
	{
		return 0;
	}

	if (this->keyMap.contains(key))
	{
		try
		{
			this->keyMap.erase(key);
			return 1;
		}
		catch(const std::exception&)
		{
			return -1;
		}
	}

    return 2;
}

int SettingsLib::Types::ConfigIniSectionData::remData(std::wstring key)
{
    if (!this->isSectionConfigured)
	{
		return -3;
	}

	if (!this->useWideData)
	{
		return -2;
	}

	if (this->wKeyMap.empty())
	{
		return 0;
	}

	if (this->wKeyMap.contains(key))
	{
		try
		{
			this->wKeyMap.erase(key);
			return 1;
		}
		catch(const std::exception&)
		{
			return -1;
		}
	}

    return 2;
}
