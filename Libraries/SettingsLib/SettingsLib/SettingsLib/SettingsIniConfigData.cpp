#include "SettingsIniConfigData.hpp"

SettingsLib::Types::ConfigIniData::ConfigIniData()
{
	this->objWasConfig = false;
}

SettingsLib::Types::ConfigIniData::ConfigIniData (std::string key)
{
	this->objWasConfig = true;
	this->usingWideData = false;
	this->key = key;
}

SettingsLib::Types::ConfigIniData::ConfigIniData(std::wstring key)
{
	this->objWasConfig = true;
	this->usingWideData = true;
	this->key = key;
}

SettingsLib::Types::ConfigIniData::ConfigIniData(const ConfigIniData &other)
{
	this->objWasConfig = other.objWasConfig;
	this->usingWideData = other.usingWideData;

	this->key = other.key;
	
	if (this->section != nullptr)
	{
		delete this->section;
	}

	if (other.section != nullptr)
	{
		*this->section = *other.section;
	}

	if (this->data != nullptr)
	{
		delete this->data;
		this->data = nullptr;
	}

	if (this->vdata != nullptr)
	{
		delete this->vdata;
		this->vdata = nullptr;
	}

	if (other.data != nullptr)
	{
		if (this->data == nullptr)
		{
			this->data = new SettingsLib::Types::ConfigDataStore;
		}

		bool successSetData = false;
		SettingsLib::Types::ConfigDataType type = other.data->getDataType();

		if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER)
		{
			unsigned long long buff = 0;
			if (other.data->getData(&buff) == 1)
			{
				if (this->data->setData(buff) == 0)
				{
					successSetData = true;
				}
			}
		}
		else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER)
		{
			long long buff = 0;
			if (other.data->getData(&buff) == 1)
			{
				if (this->data->setData(buff) == 0)
				{
					successSetData = true;
				}
			}
		}
		else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT)
		{
			double buff = 0.0;
			if (other.data->getData(&buff) == 1)
			{
				if (this->data->setData(buff) == 0)
				{
					successSetData = true;
				}
			}
		}
		else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			std::string buff;
			if (other.data->getData(&buff) == 1)
			{
				if (this->data->setData(buff) == 0)
				{
					successSetData = true;
				}
			}
		}
		else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN)
		{
			bool buff = false;
			if (other.data->getData(&buff) == 1)
			{
				if (this->data->setData(buff) == 0)
				{
					successSetData = true;
				}
			}
		}
		else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			std::wstring buff;
			if (other.data->getData(&buff) == 1)
			{
				if (this->data->setData(buff) == 0)
				{
					successSetData = true;
				}
			}
		}
		else
		{
			*this->data = *other.data;
			successSetData = true;
		}
	}

	if (other.vdata != nullptr)
	{
		if (this->vdata == nullptr)
		{
			this->vdata = new std::vector<SettingsLib::Types::ConfigDataStore>;
		}

		for (size_t i = 0; i < other.vdata->size(); i++)
		{
			this->vdata->push_back(other.vdata->at(i));
		}
	}

	if (this->comment != nullptr)
	{
		delete this->comment;
		this->comment = nullptr;
	}

	if (other.comment != nullptr)
	{
		if (this->comment == nullptr)
		{
			this->comment = new SettingsLib::Types::ConfigDataStore;
		}

		bool successSetComment = false;
		SettingsLib::Types::ConfigDataType type = other.comment->getDataType();

		if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			std::string buff;
			if (other.data->getData(&buff) == 1)
			{
				if (this->data->setData(buff) == 0)
				{
					successSetComment = true;
				}
			}
		}
		else if (type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			std::wstring buff;
			if (other.data->getData(&buff) == 1)
			{
				if (this->data->setData(buff) == 0)
				{
					successSetComment = true;
				}
			}
		}
		else
		{
			*this->comment = *other.comment;
			successSetComment = true;
		}
	}
}

SettingsLib::Types::ConfigIniData::ConfigIniData(ConfigIniData &&other) noexcept
{
	this->objWasConfig = other.objWasConfig;
	this->usingWideData = other.usingWideData;

	this->key = other.key;

	if (this->section != nullptr)
	{
		delete this->section;
		this->section = nullptr;
	}

	if (other.section != nullptr)
	{
		this->section = std::move(other.section);
		other.section = nullptr;
	}

	if (this->data != nullptr)
	{
		delete this->data;
		this->data = nullptr;
	}

	if (other.data != nullptr)
	{
		this->data = std::move(other.data);
		other.data = nullptr;
	}

	if (this->vdata != nullptr)
	{
		delete this->vdata;
		this->vdata = nullptr;
	}

	if (other.vdata != nullptr)
	{
		this->vdata = std::move(other.vdata);
		other.vdata = nullptr;
	}

	if (this->comment != nullptr)
	{
		delete this->comment;
		this->comment = nullptr;
	}

	if (other.comment != nullptr)
	{
		this->comment = std::move(other.comment);
		other.comment = nullptr;
	}
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

SettingsLib::Types::ConfigIniData &SettingsLib::Types::ConfigIniData::operator=(const SettingsLib::Types::ConfigIniData &other)
{
	SettingsLib::ErrorCodes::ConfigIniStatus cleanDataStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanData());
	SettingsLib::ErrorCodes::ConfigIniStatus cleanCommentStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanComment());

	if (!(cleanDataStatus == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR || cleanDataStatus == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR))
	{
		if (cleanCommentStatus != SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR)
		{
			this->objWasConfig = other.objWasConfig;
			this->usingWideData = other.usingWideData;
			
			if (other.data != nullptr || other.vdata != nullptr)
			{
				if (other.vdata != nullptr)
				{
					for (size_t i = 0; i < other.vdata->size(); i++)
					{
						this->vdata->push_back(other.vdata->at(i));
					}
				}
				else
				{
					this->setData(other.data);
				}
			}

			if (other.comment != nullptr)
			{
				std::string lComment;
				if (other.comment->getData(&lComment) == 1)
				{
					this->setComment(lComment);
				}
			}
		}
	}

	return *this;
}

SettingsLib::Types::ConfigIniData &SettingsLib::Types::ConfigIniData::operator=(SettingsLib::Types::ConfigIniData &&other) noexcept
{
	SettingsLib::ErrorCodes::ConfigIniStatus cleanDataStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanData());
	SettingsLib::ErrorCodes::ConfigIniStatus cleanCommentStatus = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(this->cleanComment());

	if (!(cleanDataStatus == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR || cleanDataStatus == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR))
	{
		if (cleanCommentStatus != SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR)
		{
			this->objWasConfig = other.objWasConfig;
			this->usingWideData = other.usingWideData;
			
			if (other.data != nullptr || other.vdata != nullptr)
			{
				if (other.vdata != nullptr)
				{
					this->vdata = std::move(other.vdata);
				}
				else
				{
					this->data = std::move(other.data);
				}
			}

			if (other.comment != nullptr)
			{
				this->comment = std::move(other.comment);
			}
		}
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
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

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
				return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR;
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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
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
	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

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

		if (this->section->getData(section) == 1)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
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

		if (this->section->getData(section) == 1)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::setSection(std::string *section)
{
	if (section == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_STRING_DATA;
	}

	if (!this->hasSection())
	{
		try
		{
			this->section = new SettingsLib::Types::ConfigDataStore;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	if (this->hasSection())
	{
		if (this->section->setData(section) == 0)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}

		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_SET_DATA_FAIL;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_TO_SET;
}

int SettingsLib::Types::ConfigIniData::setSection(std::wstring *section)
{
    if (section == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (!this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA;
	}

	if (!this->hasSection())
	{
		try
		{
			this->section = new SettingsLib::Types::ConfigDataStore;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	if (this->hasSection())
	{
		if (this->section->setData(section) == 0)
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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_GET_STRING_DATA;
	}

	if (this->key.getData(key) == 1)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}
	else
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
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

	if (this->key.getData(key) == 1)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
	}
	else
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
	}

	return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_NO_DATA_AVAILABLE;
}

int SettingsLib::Types::ConfigIniData::setKey(std::string key)
{
    return this->setKey(&key);
}

int SettingsLib::Types::ConfigIniData::setKey(std::wstring key)
{
    return this->setKey(&key);
}

int SettingsLib::Types::ConfigIniData::setKey(std::string *key)
{
    if (key == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	if (key->empty())
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

	if (this->key.setData(key) == 0)
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

int SettingsLib::Types::ConfigIniData::setKey(std::wstring *key)
{
    if (key == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	if (key->empty())
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

	if (this->key.setData(key) == 0)
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
	return this->data != nullptr || this->vdata != nullptr;
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
				*data = *this->data;
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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (!this->hasData())
	{
		try
		{
			this->data = new SettingsLib::Types::ConfigDataStore;
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
		return SettingsLib::ErrorCodes::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (!this->hasData())
	{
		try
		{
			this->data = new SettingsLib::Types::ConfigDataStore;
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

int SettingsLib::Types::ConfigIniData::insertData(SettingsLib::Types::ConfigDataStore *data, size_t pos, bool overwrite)
{
	if (data == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (!this->hasData())
	{
		try
		{
			this->vdata = new std::vector<SettingsLib::Types::ConfigDataStore>;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	if (this->isContainer())
	{
		try
		{
			if (this->getConainerSize() > pos)
			{
				if (overwrite)
				{
					SettingsLib::Types::ConfigDataStore* tmpData = &this->vdata->at(pos);
					*tmpData = *data;
				}
				else
				{
					auto posRef = this->vdata->begin();
					this->vdata->insert(posRef, pos, *data);
				}
			}
			else
			{
				this->vdata->push_back(*data);
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
    	return this->vdata != nullptr;
	}

	return false;
}

size_t SettingsLib::Types::ConfigIniData::getConainerSize()
{
	if (this->isContainer())
	{
		return this->vdata->size();
	}

	return 0;
}

bool SettingsLib::Types::ConfigIniData::hasComment()
{
    return this->comment != nullptr;
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
			delete this->comment;
			this->comment = nullptr;
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
		if (this->comment->getData(comment) == 1)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
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
		if (this->comment->getData(comment) == 1)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}

		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
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

	if (!this->hasComment())
	{
		try
		{
			this->comment = new SettingsLib::Types::ConfigDataStore;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	try
	{
		bool hasCommemntMark = comment.starts_with(SETTINGS_INI_COMMENT_MARK) || comment.starts_with(SETTINGS_INI_COMMENT_MARK2);

		if (!hasCommemntMark)
		{
			comment = SETTINGS_INI_COMMENT_MARK2 + comment;
		}

		if (this->comment->setData(comment) == 0)
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
    return this->setComment(&comment);
}

int SettingsLib::Types::ConfigIniData::setComment(std::string *comment)
{
	if (comment == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	std::string buff = *comment;

	return this->setComment(buff);
}

int SettingsLib::Types::ConfigIniData::setComment(std::wstring *comment)
{
    if (comment == nullptr)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR;
	}

	if (!this->objWasConfig)
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED;
	}

	if (!this->isWideData())
	{
		return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA;
	}

	if (!this->hasComment())
	{
		try
		{
			this->comment = new SettingsLib::Types::ConfigDataStore;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION;
		}
	}

	try
	{
		bool hasCommemntMark = comment->starts_with(SETTINGS_INI_COMMENT_MARK) || comment->starts_with(SETTINGS_INI_COMMENT_MARK2);
		std::wstring tmpComment;

		if (!hasCommemntMark)
		{
			tmpComment += SETTINGS_INI_COMMENT_MARK2_W;
		}

		tmpComment += *comment;

		if (this->comment->setData(tmpComment) == 0)
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
	this->isSectionConfigurated = false;
	this->useWideData = false;
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(std::string section)
{
	this->isSectionConfigurated = true;
	this->useWideData = false;
	this->sectionName.setData(section);
	this->keyMap = new std::map<std::string, SettingsLib::Types::ConfigIniData>;
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(std::wstring section)
{
	this->isSectionConfigurated = true;
	this->useWideData = true;
	this->sectionName.setData(section);
	this->wKeyMap = new std::map<std::wstring, SettingsLib::Types::ConfigIniData>;
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(const ConfigIniSectionData &other)
{
	this->isSectionConfigurated = other.isSectionConfigurated;
	this->useWideData = other.useWideData;

	this->sectionName = other.sectionName;

	if (this->useWideData)
	{
		this->wKeyMap = new std::map<std::wstring, SettingsLib::Types::ConfigIniData>(*other.wKeyMap);
	}
	else
	{
		this->keyMap = new std::map<std::string, SettingsLib::Types::ConfigIniData>(*other.keyMap);
	}
}

SettingsLib::Types::ConfigIniSectionData::ConfigIniSectionData(ConfigIniSectionData &&other) noexcept
{
	this->isSectionConfigurated = other.isSectionConfigurated;
	this->useWideData = other.useWideData;

	this->sectionName = other.sectionName;

	if (this->useWideData)
	{
		this->wKeyMap = new std::map<std::wstring, SettingsLib::Types::ConfigIniData>(*std::move(other.wKeyMap));
	}
	else
	{
		this->keyMap = new std::map<std::string, SettingsLib::Types::ConfigIniData>(*std::move(other.keyMap));
	}
}

SettingsLib::Types::ConfigIniSectionData::~ConfigIniSectionData()
{
	if (this->keyMap != nullptr)
	{
		delete this->keyMap;
		this->keyMap = nullptr;
	}

	if (this->wKeyMap != nullptr)
	{
		delete this->wKeyMap;
		this->wKeyMap = nullptr;
	}
}

SettingsLib::Types::ConfigIniSectionData &SettingsLib::Types::ConfigIniSectionData::operator=(const SettingsLib::Types::ConfigIniSectionData &other)
{
    this->isSectionConfigurated = other.isSectionConfigurated;
	this->useWideData = other.useWideData;

	this->sectionName = other.sectionName;

	if (this->useWideData)
	{
		this->wKeyMap = new std::map<std::wstring, SettingsLib::Types::ConfigIniData>;
		*this->wKeyMap = *other.wKeyMap;
	}
	else
	{
		this->keyMap = new std::map<std::string, SettingsLib::Types::ConfigIniData>;
		*this->keyMap = *other.keyMap;
	}

	return *this;
}

SettingsLib::Types::ConfigIniSectionData &SettingsLib::Types::ConfigIniSectionData::operator=(SettingsLib::Types::ConfigIniSectionData &&other) noexcept
{
    this->isSectionConfigurated = other.isSectionConfigurated;
	this->useWideData = other.useWideData;

	this->sectionName = other.sectionName;

	if (this->useWideData)
	{
		this->wKeyMap = new std::map<std::wstring, SettingsLib::Types::ConfigIniData>;
		this->wKeyMap = std::move(other.wKeyMap);
	}
	else
	{
		this->keyMap = new std::map<std::string, SettingsLib::Types::ConfigIniData>;
		this->keyMap = std::move(other.keyMap);
	}

	return *this;
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

		if (this->keyMap->contains(key))
		{
			SettingsLib::Types::ConfigIniData data = this->keyMap->at(key);
			*iniData = data;
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

int SettingsLib::Types::ConfigIniSectionData::addData(SettingsLib::Types::ConfigIniData& data)
{
	if (&data == nullptr)
	{
		return -3;
	}

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
				bool iswKeyMapNull = this->wKeyMap == nullptr;

				try
				{
					bool isEmpty = this->wKeyMap->empty();
					bool foundKey = this->wKeyMap->contains(key);

					if (!foundKey || isEmpty)
					{
						this->wKeyMap->insert({key, data});
						return 1;
					}
					else
					{
						auto p = &this->wKeyMap->at(key);
						p = &data;
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
			SettingsLib::ErrorCodes::ConfigIniStatus status = static_cast<SettingsLib::ErrorCodes::ConfigIniStatus>(data.getKey(&key));

			if (status == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
			{
				bool isKeyMapNull = this->keyMap == nullptr;

				try
				{
					bool isEmpty = this->keyMap->empty();
					bool foundKey = this->keyMap->contains(key);
					
					if (!foundKey || isEmpty)
					{
						this->keyMap->insert({key, data});
						return 1;
					}
					else
					{
						auto p = &this->keyMap->at(key);
						p = &data;
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
