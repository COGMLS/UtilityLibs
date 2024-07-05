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
	
	#ifdef USE_INIDATA_POINTERS
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
	#else
	this->data = other.data;
	this->vdata = other.vdata;
	this->section = other.section;
	this->comment = other.comment;
	#endif // !USE_INIDATA_POINTERS
}

SettingsLib::Types::ConfigIniData::ConfigIniData(ConfigIniData &&other) noexcept
{
	this->objWasConfig = std::move(other.objWasConfig);
	this->usingWideData = std::move(other.usingWideData);
	this->dataStoreType = std::move(other.dataStoreType);

	this->key = std::move(other.key);

	#ifdef USE_INIDATA_POINTERS
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
	#else
	this->data = std::move(other.data);
	this->vdata = std::move(other.vdata);
	this->section = std::move(other.section);
	this->comment = std::move(other.comment);
	#endif // !USE_INIDATA_POINTERS
}

SettingsLib::Types::ConfigIniData::~ConfigIniData()
{
	#ifdef USE_INIDATA_POINTERS

	#endif // !USE_INIDATA_POINTERS
}

SettingsLib::Types::ConfigIniData &SettingsLib::Types::ConfigIniData::operator=(const SettingsLib::Types::ConfigIniData &other)
{
	SettingsLib::ErrorCodes::ConfigIniStatus cleanDataStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanData());
	SettingsLib::ErrorCodes::ConfigIniStatus cleanCommentStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanComment());

	this->objWasConfig = other.objWasConfig;
	this->usingWideData = other.usingWideData;
	this->dataStoreType = other.dataStoreType;

	#ifdef USE_INIDATA_POINTERS
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
	#else
	this->key = other.key;
	this->data = other.data;
	this->vdata = other.vdata;
	this->section = other.section;
	this->comment = other.comment;
	#endif // !USE_INIDATA_POINTERS

	return *this;
}

SettingsLib::Types::ConfigIniData &SettingsLib::Types::ConfigIniData::operator=(SettingsLib::Types::ConfigIniData &&other) noexcept
{
	SettingsLib::ErrorCodes::ConfigIniStatus cleanDataStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanData());
	SettingsLib::ErrorCodes::ConfigIniStatus cleanCommentStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanComment());

	this->objWasConfig = std::move(other.objWasConfig);
	this->usingWideData = std::move(other.usingWideData);
	this->dataStoreType = std::move(other.dataStoreType);

	#ifdef USE_INIDATA_POINTERS
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
	#else
	this->key = std::move(other.key);
	this->data = std::move(other.data);
	this->vdata = std::move(other.vdata);
	this->section = std::move(other.section);
	this->comment = std::move(other.comment);
	#endif // !USE_INIDATA_POINTERS

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
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->hasData())
	{
		if (this->isContainer())
		{
			try
			{
				#ifdef USE_INIDATA_POINTERS
				this->vdata.reset(nullptr);
				#else
				this->vdata.clear();
				#endif // !USE_INIDATA_POINTERS
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
				#ifdef USE_INIDATA_POINTERS
				this->data.reset(nullptr);
				#else
				this->data.cleanData();
				#endif // !USE_INIDATA_POINTERS
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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->hasData())
	{
		if (this->isContainer())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO;
		}

		#ifdef USE_INIDATA_POINTERS
		*type = this->data->getDataType();
		#else
		*type = this->data.getDataType();
		#endif // !USE_INIDATA_POINTERS

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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->hasData())
	{
		if (this->isContainer())
		{
			#ifdef USE_INIDATA_POINTERS
			if (pos >= this->vdata->size())
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE;
			}
			#else
			if (pos >= this->vdata.size())
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE;
			}
			#endif // !USE_INIDATA_POINTERS

			try
			{
				#ifdef USE_INIDATA_POINTERS
				SettingsLib::Types::ConfigDataType lType = this->vdata->at(pos).getDataType();
				#else
				SettingsLib::Types::ConfigDataType lType = this->vdata.at(pos).getDataType();
				#endif // !USE_INIDATA_POINTERS
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
	#ifdef USE_INIDATA_POINTERS
    return this->section.get() != nullptr;
	#else
	std::string buff;
	this->section.getData(&buff);
	return !buff.empty();
	#endif // !USE_INIDATA_POINTERS
}

int SettingsLib::Types::ConfigIniData::removeSection()
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->hasSection())
	{
		#ifdef USE_INIDATA_POINTERS
		try
		{
			this->section.reset(nullptr);
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR;
		}
		#else
		if (!this->section.cleanData())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR;
		}
		#endif // !USE_INIDATA_POINTERS

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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->hasSection())
	{
		if (this->isWideData())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_STRING_DATA;
		}

		#ifdef USE_INIDATA_POINTERS
		*section = this->section->getStr();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		#else
		*section = this->section.getStr();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		#endif // !USE_INIDATA_POINTERS
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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->hasSection())
	{
		if (!this->isWideData())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA;
		}

		#ifdef USE_INIDATA_POINTERS
		*section = this->section->getStrW();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		#else
		*section = this->section.getStrW();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		#endif // !USE_INIDATA_POINTERS
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::setSection(std::string section)
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_STRING_DATA;
	}

	#ifdef USE_INIDATA_POINTERS
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
	#endif // !USE_INIDATA_POINTERS

	if (this->hasSection())
	{
		#ifdef USE_INIDATA_POINTERS
		if (this->section->setStr(section))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		#else
		if (this->section.setStr(section))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		#endif // !USE_INIDATA_POINTERS

		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_TO_SET;
}

int SettingsLib::Types::ConfigIniData::setSection(std::wstring section)
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (!this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA;
	}

	#ifdef USE_INIDATA_POINTERS
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
	#endif // !USE_INIDATA_POINTERS

	if (this->hasSection())
	{
		#ifdef USE_INIDATA_POINTERS
		if (this->section->setStr(section))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		#else
		if (this->section.setStr(section))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		#endif // !USE_INIDATA_POINTERS

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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
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
	#ifdef USE_INIDATA_POINTERS
	return this->data.get() != nullptr || this->vdata.get() != nullptr;
	#else
	if (this->dataStoreType == 0)
	{
		return false;
	}
	
	return true;
	#endif // !USE_INIDATA_POINTERS
}

int SettingsLib::Types::ConfigIniData::getData(SettingsLib::Types::ConfigDataStore *data)
{
    if (data == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
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

			#ifdef USE_INIDATA_POINTERS
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
			#else
			if (this->data.getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
			{
				std::string buff;
				if (this->data.getData(&buff) == 1)
				{
					success = data->setData(buff) == 0;
				}
			}
			else if (this->data.getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
			{
				std::wstring buff;
				if (this->data.getData(&buff) == 1)
				{
					success = data->setData(buff) == 0;
				}
			}
			else
			{
				*data = this->data;
				success = true;
			}
			#endif // !USE_INIDATA_POINTERS

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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	#ifdef USE_INIDATA_POINTERS
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
	#endif // !USE_INIDATA_POINTERS

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
					#ifdef USE_INIDATA_POINTERS
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#else
					if (this->data.setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#endif // !USE_INIDATA_POINTERS
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER)
			{
				long long buff = 0;
				if (data.getData(&buff) == 1)
				{
					#ifdef USE_INIDATA_POINTERS
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#else
					if (this->data.setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#endif // !USE_INIDATA_POINTERS
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT)
			{
				double buff = 0.0;
				if (data.getData(&buff) == 1)
				{
					#ifdef USE_INIDATA_POINTERS
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#else
					if (this->data.setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#endif // !USE_INIDATA_POINTERS
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
			{
				std::string buff;
				if (data.getData(&buff) == 1)
				{
					#ifdef USE_INIDATA_POINTERS
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#else
					if (this->data.setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#endif // !USE_INIDATA_POINTERS
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN)
			{
				bool buff = false;
				if (data.getData(&buff) == 1)
				{
					#ifdef USE_INIDATA_POINTERS
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#else
					if (this->data.setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#endif // !USE_INIDATA_POINTERS
				}
			}
			else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
			{
				std::wstring buff;
				if (data.getData(&buff) == 1)
				{
					#ifdef USE_INIDATA_POINTERS
					if (this->data->setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#else
					if (this->data.setData(buff) == 0)
					{
						return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
					}
					#endif // !USE_INIDATA_POINTERS
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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	#ifdef USE_INIDATA_POINTERS
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
	#endif // !USE_INIDATA_POINTERS

	if (this->hasData())
	{
		if (this->isContainer())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO;
		}

		try
		{
			#ifdef USE_INIDATA_POINTERS
			*this->data = *data;
			#else
			this->data = *data;
			#endif // !USE_INIDATA_POINTERS
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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->hasData())
	{
		if (!this->isContainer())
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE;
		}

		try
		{
			#ifdef USE_INIDATA_POINTERS
			if (this->vdata->size() > pos)
			{
				SettingsLib::Types::ConfigDataStore tmpData = this->vdata->at(pos);
				*data = tmpData;
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
			}
			#else
			if (this->vdata.size() > pos)
			{
				SettingsLib::Types::ConfigDataStore tmpData = this->vdata.at(pos);
				*data = tmpData;
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
			}
			#endif // !USE_INIDATA_POINTERS

			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE;
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
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	#ifdef USE_INIDATA_POINTERS
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
	#endif // !USE_INIDATA_POINTERS

	if (!this->hasData())
	{
		this->dataStoreType = 2;
	}

	if (this->isContainer())
	{
		try
		{
			if (this->getConainerSize() > pos)
			{
				if (overwrite)
				{
					#ifdef USE_INIDATA_POINTERS
					SettingsLib::Types::ConfigDataStore* tmpData = &this->vdata->at(pos);
					#else
					SettingsLib::Types::ConfigDataStore* tmpData = &this->vdata.at(pos);
					#endif // !USE_INIDATA_POINTERS
					*tmpData = data;
				}
				else
				{
					#ifdef USE_INIDATA_POINTERS
					auto posRef = this->vdata->begin();
					this->vdata->insert(posRef, pos, data);
					#else
					auto posRef = this->vdata.begin();
					this->vdata.insert(posRef, pos, *data);
					#endif // !USE_INIDATA_POINTERS
				}
			}
			else
			{
				#ifdef USE_INIDATA_POINTERS
				this->vdata->push_back(data);
				#else
				this->vdata.push_back(*data);
				#endif // !USE_INIDATA_POINTERS
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
		#ifdef USE_INIDATA_POINTERS
    	return this->vdata.get() != nullptr;
		#else
		if (this->dataStoreType == 2)
		{
			return true;
		}
		#endif // !USE_INIDATA_POINTERS
	}

	return false;
}

size_t SettingsLib::Types::ConfigIniData::getConainerSize()
{
	if (this->isContainer())
	{
		#ifdef USE_INIDATA_POINTERS
		return this->vdata->size();
		#else
		return this->vdata.size();
		#endif // !USE_INIDATA_POINTERS
	}

	return 0;
}

bool SettingsLib::Types::ConfigIniData::hasComment()
{
	#ifdef USE_INIDATA_POINTERS
    return this->comment.get() != nullptr;
	#else
	if (this->comment.getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		std::string buff;
		if (this->comment.getData(&buff) == 1)
		{
			return !buff.empty();
		}
	}
	
	if (this->comment.getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		std::wstring buff;
		if (this->comment.getData(&buff) == 1)
		{
			return !buff.empty();
		}
	}

	return false;
	#endif // !USE_INIDATA_POINTERS
}

int SettingsLib::Types::ConfigIniData::cleanComment()
{
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->hasComment())
	{
		try
		{
			#ifdef USE_INIDATA_POINTERS
			this->comment.reset(nullptr);
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
			#else
			if (this->comment.cleanData())
			{
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
			}
			#endif // !USE_INIDATA_POINTERS
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
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
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
		#ifdef USE_INIDATA_POINTERS
		*comment = this->comment->getStr();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		#else
		*comment = this->comment.getStr();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		#endif // !USE_INIDATA_POINTERS
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
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
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
		#ifdef USE_INIDATA_POINTERS
		*comment = this->comment->getStrW();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		#else
		*comment = this->comment.getStrW();
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		#endif // !USE_INIDATA_POINTERS
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
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_STRING_DATA;
	}

	#ifdef USE_INIDATA_POINTERS
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
	#endif // !USE_INIDATA_POINTERS

	try
	{
		bool hasCommemntMark = comment.starts_with(SETTINGS_INI_COMMENT_MARK) || comment.starts_with(SETTINGS_INI_COMMENT_MARK2);

		if (!hasCommemntMark)
		{
			comment = SETTINGS_INI_COMMENT_MARK2 + comment;
		}

		#ifdef USE_INIDATA_POINTERS
		if (this->comment->setStr(comment))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		#else
		if (this->comment.setStr(comment))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		#endif // !USE_INIDATA_POINTERS

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
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (!this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA;
	}

	#ifdef USE_INIDATA_POINTERS
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
	#endif // !USE_INIDATA_POINTERS

	try
	{
		bool hasCommemntMark = comment.starts_with(SETTINGS_INI_COMMENT_MARK) || comment.starts_with(SETTINGS_INI_COMMENT_MARK2);
		std::wstring tmpComment;

		if (!hasCommemntMark)
		{
			tmpComment += SETTINGS_INI_COMMENT_MARK2_W;
		}

		tmpComment += comment;

		#ifdef USE_INIDATA_POINTERS
		if (this->comment->setStr(tmpComment))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		#else
		if (this->comment.setStr(tmpComment))
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		#endif // !USE_INIDATA_POINTERS

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}
	catch(const std::exception&)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData()
{
	this->isSectionConfigurated = false;
	this->useWideData = false;
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(std::string section)
{
	this->isSectionConfigurated = true;
	this->useWideData = false;
	this->sectionName.setData(section);
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(std::wstring section)
{
	this->isSectionConfigurated = true;
	this->useWideData = true;
	this->sectionName.setData(section);
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(const ConfigIniSectionData &other)
{
	this->isSectionConfigurated = other.isSectionConfigurated;
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

	this->comment = other.comment;
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(ConfigIniSectionData &&other) noexcept
{
	this->isSectionConfigurated = other.isSectionConfigurated;
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
    this->isSectionConfigurated = other.isSectionConfigurated;
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

	this->comment = other.comment;

	return *this;
}

SettingsLib::Types::ConfigIniSectionData &SettingsLib::Types::ConfigIniSectionData::operator=(SettingsLib::Types::ConfigIniSectionData &&other) noexcept
{
    this->isSectionConfigurated = other.isSectionConfigurated;
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

std::string SettingsLib::Types::ConfigIniSectionData::getSectionName()
{
	std::string name;
	this->sectionName.getData(&name);
	return name;
}

std::wstring SettingsLib::Types::ConfigIniSectionData::getSectionNameW()
{
    std::wstring nameW;
	this->sectionName.getData(&nameW);
	return nameW;
}

int SettingsLib::Types::ConfigIniSectionData::getIniData(std::string key, SettingsLib::Types::ConfigIniData *iniData)
{
	if (iniData == nullptr)
	{
		return -3;
	}

    if (this->isSectionConfigurated)
	{
		if (this->useWideData)
		{
			return -2;
		}

		if (this->keyMap.contains(key))
		{
			#ifdef USE_SECTION_POINTERS
			SettingsLib::Types::ConfigIniData* data = this->keyMap.at(key);
			#else
			SettingsLib::Types::ConfigIniData* data = &this->keyMap.at(key);
			#endif // !USE_SECTION_POINTERS
			*iniData = *data;
			return 1;
		}

		return 0;
	}

	return -1;
}

bool SettingsLib::Types::ConfigIniSectionData::isWideData()
{
    return this->useWideData;
}

int SettingsLib::Types::ConfigIniSectionData::addData(SettingsLib::Types::ConfigIniData &data)
{
	if (this->isSectionConfigurated)
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
						#ifdef USE_SECTION_POINTERS
						this->wKeyMap.insert({key, data});
						#else
						this->wKeyMap.insert({key, data});
						#endif // !USE_SECTION_POINTERS
						return 1;
					}
					else
					{
						auto p = &this->wKeyMap.at(key);
						#ifdef USE_SECTION_POINTERS
						**p = *data;
						#else
						*p = data;
						#endif // !USE_SECTION_POINTERS
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
						#ifdef USE_SECTION_POINTERS
						this->keyMap.insert({key, data});
						#else
						this->keyMap.insert({key, data});
						#endif // !USE_SECTION_POINTERS
						return 1;
					}
					else
					{
						auto p = &this->keyMap.at(key);
						#ifdef USE_SECTION_POINTERS
						**p = *data;
						#else
						*p = data;
						#endif // !USE_SECTION_POINTERS
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

	return -1;
}

int SettingsLib::Types::ConfigIniSectionData::remData(std::string key)
{
    return 0;
}

int SettingsLib::Types::ConfigIniSectionData::remData(std::wstring key)
{
    return 0;
}
