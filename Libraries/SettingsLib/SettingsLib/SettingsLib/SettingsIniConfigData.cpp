#include "SettingsIniConfigData.hpp"

SettingsLib::Types::ConfigIniData::ConfigIniData()
{
	this->objWasConfig = false;
}

SettingsLib::Types::ConfigIniData::ConfigIniData (std::string key)
{
	this->objWasConfig = true;
	this->usingWideData = false;
}

SettingsLib::Types::ConfigIniData::ConfigIniData(std::wstring key)
{
	this->objWasConfig = true;
	this->usingWideData = true;
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

		if (this->section->getData(section) == 0)
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

		if (this->section->getData(section) == 0)
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

	if (this->key.getData(key) == 0)
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

	if (this->key.getData(key) == 0)
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
			data = this->data;
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION;
		}
		catch(const std::exception&)
		{
			return SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_GET_DATA_FAIL;
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
			this->data = data;
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
				data->setData(&tmpData);
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
		if (this->comment->getData(comment) == 0)
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
		if (this->comment->getData(comment) == 0)
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
    return this->setComment(&comment);
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
		bool hasCommemntMark = comment->starts_with(SETTINGS_INI_COMMENT_MARK) || comment->starts_with(SETTINGS_INI_COMMENT_MARK2);
		std::string tmpComment;

		if (!hasCommemntMark)
		{
			tmpComment += SETTINGS_INI_COMMENT_MARK2;
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
