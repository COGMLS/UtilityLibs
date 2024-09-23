#include "SettingsLibConfigFileStream.hpp"

int SettingsLib::Types::ConfigFileStream::save2Store()
{
	if (this->keepCfgStore)
	{
		if (this->isWideData)
		{
			try
			{
				// Store WFstream to Vector Memory:
				int sWFs2Vmem = SettingsLib::Tools::storeFstream2Memory(this->wCfgFileStream.get(), this->wCfgStore.get(), 0, true, true);

				if (sWFs2Vmem != 0)
				{
					this->saveErrorReport(std::exception(std::string("Fail to read into the memory the wCfgFileStream. Return " + std::to_string(sWFs2Vmem)).c_str()));
				}

				return 1;
			}
			catch(const std::exception& e)
			{
				this->saveErrorReport(e);
				return -1;
			}
		}
		else
		{
			try
			{
				// Store Fstream to Vector Memory:
				int sFs2Vmem = SettingsLib::Tools::storeFstream2Memory(this->cfgFileStream.get(), this->cfgStore.get(), 0, true, true);

				if (sFs2Vmem != 0)
				{
					this->saveErrorReport(std::exception(std::string("Fail to read into the memory the cfgFileStream. Return " + std::to_string(sFs2Vmem)).c_str()));
				}

				return 1;
			}
			catch(const std::exception& e)
			{
				this->saveErrorReport(e);
				return -1;
			}
		}
	}

	return 0;
}

int SettingsLib::Types::ConfigFileStream::makeVMemStore()
{
	if (this->keepCfgStore)
	{
		if (this->isWideData)
		{
			if (this->wCfgStore == nullptr)
			{
				this->wCfgStore.reset(new std::vector<std::wstring>);
				return 0;
			}
		}
		else
		{
			if (this->cfgStore == nullptr)
			{
				this->cfgStore.reset(new std::vector<std::string>);
				return 0;
			}
		}

		return 1;
	}

    return -1;
}

bool SettingsLib::Types::ConfigFileStream::vMemStoreExist()
{
    if (this->isWideData)
	{
		return this->wCfgStore != nullptr;
	}
	else
	{
		return this->cfgStore != nullptr;
	}
}

void SettingsLib::Types::ConfigFileStream::saveErrorReport(std::exception e)
{
	if (this->errorReportEnabled)
	{
		if (this->errorsList == nullptr)
		{
			this->errorsList.reset(new std::vector<std::exception>);
		}

		if (this->errorsList->size() == this->errorListMaxReports)
		{
			this->errorsList->erase(this->errorsList->begin());
		}

		this->errorsList->push_back(e);
	}
}

SettingsLib::Types::ConfigFileStream::ConfigFileStream()
{
}

SettingsLib::Types::ConfigFileStream::ConfigFileStream(std::filesystem::path cfgFilePath, bool useWideData, bool useReadonly, bool keepCfgStore)
{
	this->cfgFilePath = cfgFilePath;
	this->isWideData = useWideData;
	this->isReadonly = useReadonly;
	this->keepCfgStore = keepCfgStore;

	this->isNewFile = false;
	this->isCfgFileOk = true;
	
	this->setErrorReport(CONFIG_FILE_STREAM_MAXIMUM_ERRORS);

	if (!std::filesystem::exists(this->cfgFilePath))
	{
		this->isNewFile = true;
	}

	if (this->isNewFile)
	{
		this->cfgFileMode = std::ios_base::out;

		if (this->isWideData)
		{
			this->wCfgFileStream.reset(new std::wfstream);
			this->wCfgFileStream->open(this->cfgFilePath.wstring(), this->cfgFileMode);
			this->wCfgFileStream->close();
			this->wCfgFileStream.reset(nullptr);
		}
		else
		{
			this->cfgFileStream.reset(new std::fstream);
			this->cfgFileStream->open(this->cfgFilePath.string(), this->cfgFileMode);
			this->cfgFileStream->close();
			this->cfgFileStream.reset(nullptr);
		}

		if (!std::filesystem::exists(this->cfgFilePath))
		{
			this->isCfgFileOk = false;
			this->saveErrorReport(std::exception("Fail to create the configuration file!"));
		}

		this->isReadonly = false;	// Ignore the readonly mode for new files.
	}

	if (std::filesystem::is_regular_file(this->cfgFilePath))
	{
		if (this->isCfgFileOk)
		{
			if (this->isReadonly)
			{
				this->cfgFileMode = std::ios_base::in;
			}
			else
			{
				this->cfgFileMode = std::ios_base::in | std::ios_base::out;
			}

			this->openConfigStream(keepCfgStore, useReadonly);
		}
		else
		{
			this->saveErrorReport(std::exception("The configuration file was marked as FAIL"));
		}
	}
	else
	{
		this->isCfgFileOk = false;
		this->saveErrorReport(std::exception("cfgFilePath does not lead to a configuration file!"));
	}
}

SettingsLib::Types::ConfigFileStream::~ConfigFileStream()
{
	this->closeConfigStream();
	this->freeCfgStore();

	if (this->cfgFileStream != nullptr)
	{
		this->cfgFileStream.reset(nullptr);
	}

	if (this->wCfgFileStream != nullptr)
	{
		this->wCfgFileStream.reset(nullptr);
	}

	if (this->errorsList != nullptr)
	{
		this->errorsList.reset(nullptr);
	}
}

void SettingsLib::Types::ConfigFileStream::closeConfigStream()
{
	if (this->isWideData)
	{
		this->wCfgFileStream->close();
	}
	else
	{
		this->cfgFileStream->close();
	}
}

bool SettingsLib::Types::ConfigFileStream::openConfigStream(bool refreshCfgStore, bool useReadonly)
{
	bool successfullyOpened = false;

	if (this->isReadonly)
	{
		this->cfgFileMode = std::ios_base::in;
	}
	else
	{
		this->cfgFileMode = std::ios_base::in | std::ios_base::out;
	}

	// To refresh the store, set to false to free automatically the memory:
	if (this->keepCfgStore && refreshCfgStore)
	{
		this->setKeepCfgStore(false);
	}

	this->setKeepCfgStore(refreshCfgStore);

	if (this->isWideData)
	{
		if (wCfgFileStream == nullptr)
		{
			this->wCfgFileStream.reset(new std::wfstream);
		}

		try
		{
			this->wCfgFileStream->open(this->cfgFilePath.wstring(), this->cfgFileMode);
			successfullyOpened = this->wCfgFileStream->is_open();

			if (successfullyOpened)
			{
				this->save2Store();
			}
		}
		catch(const std::exception& e)
		{
			this->saveErrorReport(e);
		}
	}
	else
	{
		if (this->cfgFileStream == nullptr)
		{
			this->cfgFileStream.reset(new std::fstream);
		}

		try
		{
			this->cfgFileStream->open(this->cfgFilePath.string(), this->cfgFileMode);
			successfullyOpened = this->cfgFileStream->is_open();

			if (successfullyOpened)
			{
				this->save2Store();
			}
		}
		catch(const std::exception& e)
		{
			this->saveErrorReport(e);
		}
	}

	// Report is the opening file fail:
	if (!successfullyOpened)
	{
		this->saveErrorReport(std::exception("Fail to open the configuration file!"));
	}

    return successfullyOpened;
}

bool SettingsLib::Types::ConfigFileStream::isConfigStreamOpen()
{
	if (this->isWideData)
	{
		return this->wCfgFileStream->is_open();
	}
	else
	{
		return this->cfgFileStream->is_open();
	}
}

void SettingsLib::Types::ConfigFileStream::getConfigStream(std::fstream *cfgFileStream)
{
	cfgFileStream = this->cfgFileStream.get();
}

void SettingsLib::Types::ConfigFileStream::getConfigStream(std::wfstream *wCfgFileStream)
{
	wCfgFileStream = this->wCfgFileStream.get();
}

int SettingsLib::Types::ConfigFileStream::getConfigLines(std::vector<std::string> *vMemStore)
{
	if (this->keepCfgStore)
	{
		if (this->isWideData)
		{
			return -1;
		}
		else
		{
			if (this->vMemStoreExist())
			{
				try
				{
					*vMemStore = *this->cfgStore.get();
					return 1;
				}
				catch(const std::exception& e)
				{
					this->saveErrorReport(e);
					return -3;
				}
			}
			
			return -2;
		}
	}

    return 0;
}

int SettingsLib::Types::ConfigFileStream::getConfigLines(std::vector<std::wstring> *vMemStore)
{
	if (this->keepCfgStore)
	{
		if (!this->isWideData)
		{
			return -1;
		}
		else
		{
			if (this->vMemStoreExist())
			{
				try
				{
					*vMemStore = *this->wCfgStore.get();
					return 1;
				}
				catch(const std::exception& e)
				{
					this->saveErrorReport(e);
					return -3;
				}
			}
			
			return -2;
		}
	}

    return 0;
}

int SettingsLib::Types::ConfigFileStream::getConfigLine(size_t nLine, std::string *line, bool useCfgStore)
{
	if (this->isConfigStreamOpen())
	{
		return 1;
	}

	if (line == nullptr)
	{
		return 2;
	}

	if (useCfgStore && !this->keepCfgStore)
	{
		return 6;
	}

	if (useCfgStore)
	{
		if (this->isWideData)
		{
			return 5;
		}
		else
		{
			if (this->vMemStoreExist())
			{
				if (this->cfgStore->size() > nLine)
				{
					return 4;
				}

				try
				{
					// Get the config store data:
					*line = this->cfgStore->at(nLine);
					return 0;
				}
				catch(const std::exception& e)
				{
					return 3;
				}
			}

			return 7;
		}
	}
	else
	{
		if (this->isWideData)
		{
			return 5;
		}
		else
		{
			// Set to the begin of the file:
			this->cfgFileStream->seekg(std::fstream::beg);
			this->cfgFileStream->seekp(std::fstream::beg);

			size_t i = 0;
			std::string lLine;
			while (std::getline(*this->cfgFileStream.get(), lLine))
			{
				if (i == nLine)
				{
					*line = lLine;
					break;
				}

				lLine.clear();
				i++;
			}

			return 0;
		}
	}
}

int SettingsLib::Types::ConfigFileStream::getConfigLine(size_t nLine, std::wstring *line, bool useCfgStore)
{
	if (this->isConfigStreamOpen())
	{
		return 1;
	}

	if (line == nullptr)
	{
		return 2;
	}

	if (useCfgStore && !this->keepCfgStore)
	{
		return 6;
	}

	if (useCfgStore)
	{
		if (this->isWideData)
		{
			if (this->vMemStoreExist())
			{
				if (this->wCfgStore->size() > nLine)
				{
					return 4;
				}

				try
				{
					// Get the config store data:
					*line = this->wCfgStore->at(nLine);
					return 0;
				}
				catch(const std::exception& e)
				{
					return 3;
				}
			}
			
			return 7;
		}
		else
		{
			return 5;
		}
	}
	else
	{
		if (this->isWideData)
		{
			// Set to the begin of the file:
			this->wCfgFileStream->seekg(std::wfstream::beg);
			this->wCfgFileStream->seekp(std::wfstream::beg);

			size_t i = 0;
			std::wstring lLine;
			while (std::getline(*this->wCfgFileStream.get(), lLine))
			{
				if (i == nLine)
				{
					*line = lLine;
					break;
				}

				lLine.clear();
				i++;
			}

			return 0;
		}
		else
		{
			return 5;
		}
	}
}

int SettingsLib::Types::ConfigFileStream::setConfigLines(std::vector<std::string> *new_vMemStore, bool overrideVector)
{
	if (this->isWideData)
	{
		return 1;
	}
	else
	{
		if (!this->vMemStoreExist())
		{
			if (this->makeVMemStore() == -1)
			{
				return 2;
			}
		}

		try
		{
			if (overrideVector)
			{
				*this->cfgStore = *new_vMemStore;
			}
			else
			{
				for (size_t i = 0; i < new_vMemStore->size(); i++)
				{
					this->cfgStore->push_back(new_vMemStore->at(i));
				}
			}
		}
		catch(const std::exception&)
		{
			return 3;
		}
	}

    return 0;
}

int SettingsLib::Types::ConfigFileStream::setConfigLines(std::vector<std::wstring> *new_vMemStore, bool overrideVector)
{
	if (!this->isWideData)
	{
		return 1;
	}
	else
	{
		if (!this->vMemStoreExist())
		{
			if (this->makeVMemStore() == -1)
			{
				return 2;
			}
		}

		try
		{
			if (overrideVector)
			{
				*this->wCfgStore = *new_vMemStore;
			}
			else
			{
				for (size_t i = 0; i < new_vMemStore->size(); i++)
				{
					this->wCfgStore->push_back(new_vMemStore->at(i));
				}
			}
		}
		catch(const std::exception&)
		{
			return 3;
		}
	}

    return 0;
}

int SettingsLib::Types::ConfigFileStream::setConfigLine(size_t lineN, std::string line, bool overwrite)
{
    if (this->isWideData)
	{
		return 1;
	}
	else
	{
		if (!this->vMemStoreExist())
		{
			if (this->makeVMemStore() == -1)
			{
				return 2;
			}
		}

		try
		{
			if (lineN >= this->cfgStore->size())
			{
				this->cfgStore->push_back(line);
			}
			else
			{
				if (overwrite)
				{
					std::string* vLine = &this->cfgStore->at(lineN);
					*vLine = line;
				}
				else
				{
					this->cfgStore->insert(this->cfgStore->begin() + lineN, line);
				}
			}
		}
		catch(const std::exception&)
		{
			return 3;
		}
	}

    return 0;
}

int SettingsLib::Types::ConfigFileStream::setConfigLine(size_t lineN, std::wstring line, bool overwrite)
{
    if (!this->isWideData)
	{
		return 1;
	}
	else
	{
		if (!this->vMemStoreExist())
		{
			if (this->makeVMemStore() == -1)
			{
				return 2;
			}
		}

		try
		{
			if (lineN >= this->wCfgStore->size())
			{
				this->wCfgStore->push_back(line);
			}
			else
			{
				if (overwrite)
				{
					std::wstring* vLine = &this->wCfgStore->at(lineN);
					*vLine = line;
				}
				else
				{
					this->wCfgStore->insert(this->wCfgStore->begin() + lineN, line);
				}
			}
		}
		catch(const std::exception&)
		{
			return 3;
		}
	}

    return 0;
}

int SettingsLib::Types::ConfigFileStream::setConfigLine(std::string line, std::string refLine, size_t lineN, bool useRefLine)
{
	if (!this->isConfigStreamOpen())
	{
		return 4;
	}

    return 0;
}

int SettingsLib::Types::ConfigFileStream::insertConfigLine(std::string line, bool insertOnBegin, bool resetPos)
{
	if (!this->isConfigStreamOpen())
	{
		return 1;
	}

	if (this->isWideData)
	{
		return 2;
	}

	std::streampos oldP = this->cfgFileStream->tellp();
	std::streampos oldG = this->cfgFileStream->tellg();

	if (insertOnBegin)
	{
		this->cfgFileStream->seekg(std::fstream::beg);
		this->cfgFileStream->seekp(std::fstream::beg);
	}
	else
	{
		this->cfgFileStream->seekg(std::fstream::end);
		this->cfgFileStream->seekp(std::fstream::end);
	}

	std::vector<std::string> tmpVec;

	int loadStatus = SettingsLib::Tools::storeFstream2Memory(this->cfgFileStream.get(), &tmpVec, 0, true, true);
	int saveStatus = -1;

	if (loadStatus == 0)
	{
		if (insertOnBegin)
		{
			tmpVec.insert(tmpVec.begin(), line);
		}
		else
		{
			tmpVec.push_back(line);
		}

		saveStatus = SettingsLib::Tools::storeMemory2Fstream(this->cfgFileStream.get(), &tmpVec, true, true, true, false);
	}

	if (resetPos)
	{
		this->cfgFileStream->seekg(std::fstream::beg);
		this->cfgFileStream->seekp(std::fstream::beg);
	}

	if (loadStatus == 4 || saveStatus == 4)
	{
		this->cfgFileStream->seekg(oldG);
		this->cfgFileStream->seekp(oldP);

		if (loadStatus == 4)
		{
			return 3;
		}

		return 4;
	}

    return 0;
}

int SettingsLib::Types::ConfigFileStream::insertConfigLine(std::wstring line, bool insertOnBegin, bool resetPos)
{
    if (!this->isConfigStreamOpen())
	{
		return 1;
	}

	if (!this->isWideData)
	{
		return 2;
	}
	
	std::streampos oldP = this->wCfgFileStream->tellp();
	std::streampos oldG = this->wCfgFileStream->tellg();

	if (insertOnBegin)
	{
		this->wCfgFileStream->seekg(std::wfstream::beg);
		this->wCfgFileStream->seekp(std::wfstream::beg);
	}
	else
	{
		this->wCfgFileStream->seekg(std::wfstream::end);
		this->wCfgFileStream->seekp(std::wfstream::end);
	}

	std::vector<std::wstring> tmpVec;

	int loadStatus = SettingsLib::Tools::storeFstream2Memory(this->wCfgFileStream.get(), &tmpVec, 0, true, true);
	int saveStatus = -1;

	if (loadStatus == 0)
	{
		if (insertOnBegin)
		{
			tmpVec.insert(tmpVec.begin(), line);
		}
		else
		{
			tmpVec.push_back(line);
		}

		saveStatus = SettingsLib::Tools::storeMemory2Fstream(this->wCfgFileStream.get(), &tmpVec, true, true, true, false);
	}

	if (resetPos)
	{
		this->wCfgFileStream->seekg(std::wfstream::beg);
		this->wCfgFileStream->seekp(std::wfstream::beg);
	}

	if (loadStatus == 4 || saveStatus == 4)
	{
		this->wCfgFileStream->seekg(oldG);
		this->wCfgFileStream->seekp(oldP);

		if (loadStatus == 4)
		{
			return 3;
		}

		return 4;
	}

    return 0;
}

size_t SettingsLib::Types::ConfigFileStream::getvMemStoreSize()
{
	if (this->vMemStoreExist())
	{
		if (this->isWideData)
		{
			return this->wCfgStore->size();
		}
		else
		{
			return this->cfgStore->size();
		}
	}

	return 0;
}

int SettingsLib::Types::ConfigFileStream::freeCfgStore()
{
	if (this->keepCfgStore)
	{
		if (this->isWideData)
		{
			if (this->wCfgStore != nullptr)
			{
				this->wCfgStore.reset(nullptr);
				return 1;
			}
		}
		else
		{
			if (this->cfgStore != nullptr)
			{
				this->cfgStore.reset(nullptr);
				return 1;
			}
		}

		return 0;
	}

    return -1;
}

int SettingsLib::Types::ConfigFileStream::refreshCfgStore()
{
	// Verify if the config stream is accessible and save it into store:
	if (this->isConfigStreamOpen())
	{
		if (!this->vMemStoreExist())
		{
			if (this->makeVMemStore() == -1)
			{
				return 2;
			}
		}

		if (this->save2Store() == -1)
		{
			return 3;
		}

		return 0;
	}

	return 1;
}

int SettingsLib::Types::ConfigFileStream::refreshCfgStore(std::vector<std::string> *externCfgStore)
{
	if (this->isWideData)
	{
		return 4;
	}

	if (this->isReadonly)
	{
		return 5;
	}

	if (this->isConfigStreamOpen())
	{
		if (this->freeCfgStore() == -1)
		{
			return 2;
		}

		if (this->makeVMemStore() >= 0)
		{
			*this->cfgStore = *externCfgStore;
			return 0;
		}

		return 3;
	}

	return 1;
}

int SettingsLib::Types::ConfigFileStream::refreshCfgStore(std::vector<std::wstring> *externCfgStore)
{
	if (!this->isWideData)
	{
		return 4;
	}

	if (this->isReadonly)
	{
		return 5;
	}

	if (this->isConfigStreamOpen())
	{
		if (this->freeCfgStore() == -1)
		{
			return 2;
		}

		if (this->makeVMemStore() >= 0)
		{
			*this->wCfgStore = *externCfgStore;
			return 0;
		}

		return 3;
	}

	return 1;
}

bool SettingsLib::Types::ConfigFileStream::getKeepCfgStore()
{
    return this->keepCfgStore;
}

void SettingsLib::Types::ConfigFileStream::setKeepCfgStore(bool keepCfgStore)
{
	// If the vector store is enabled, delete the data:
	if (this->keepCfgStore && !keepCfgStore)
	{
		this->freeCfgStore();
	}

	// If the vector store is disabled, create the data:
	if (!this->keepCfgStore && keepCfgStore)
	{
		this->makeVMemStore();
	}

	this->keepCfgStore = keepCfgStore;
}

bool SettingsLib::Types::ConfigFileStream::isReadonlyMode()
{
    return this->isReadonly;
}

bool SettingsLib::Types::ConfigFileStream::isConfigStreamOk()
{
    return this->isCfgFileOk;
}

void SettingsLib::Types::ConfigFileStream::setReadonly(bool readonly)
{
	this->isReadonly = readonly;
}

int SettingsLib::Types::ConfigFileStream::saveStoreOnFile(unsigned short saveType)
{
	if (saveType > 2)
	{
		return -1;
	}

	if (!this->vMemStoreExist())
	{
		return 1;
	}

	if (this->isReadonlyMode())
	{
		return 2;
	}

	if (!this->isConfigStreamOpen())
	{
		return 3;
	}

	int status = -1;
	
	std::ios_base::openmode oldMode = this->cfgFileMode;

	this->closeConfigStream();

	if (saveType == 0 || saveType == 2)
	{
		if (saveType == 0)
		{
			// Prepare to reopen the file stream removing all data:
			this->cfgFileMode = std::ios_base::out | std::ios_base::trunc;
			this->openConfigStream(false, false);

			if (this->isWideData)
			{
				status = SettingsLib::Tools::storeMemory2Fstream(this->wCfgFileStream.get(), this->wCfgStore.get(), true, true, true, false);
			}
			else
			{
				status = SettingsLib::Tools::storeMemory2Fstream(this->cfgFileStream.get(), this->cfgStore.get(), true, true, true, false);
			}
		}
		else
		{
			// Prepare to reopen the file stream to get positioned in the end of file:
			this->cfgFileMode = std::ios_base::out | std::ios_base::app;
			this->openConfigStream(false, false);

			if (this->isWideData)
			{
				status = SettingsLib::Tools::storeMemory2Fstream(this->wCfgFileStream.get(), this->wCfgStore.get(), false, false, true, false);
			}
			else
			{
				status = SettingsLib::Tools::storeMemory2Fstream(this->cfgFileStream.get(), this->cfgStore.get(), false, false, true, false);
			}
		}
	}

	if (saveType == 1)
	{
		// Prepare to store the current line inside the file into a local vector
		// Prepare to reopen the file stream 
		if (this->isWideData)
		{
			std::vector<std::wstring> localFileLines;

			status = SettingsLib::Tools::storeFstream2Memory(this->wCfgFileStream.get(), &localFileLines, 0, true, false);

			this->cfgFileMode = std::ios_base::out | std::ios_base::trunc;

			this->closeConfigStream();
			this->openConfigStream(false, false);

			status = SettingsLib::Tools::storeMemory2Fstream(this->wCfgFileStream.get(), this->wCfgStore.get(), true, false, true, true);
			status = SettingsLib::Tools::storeMemory2Fstream(this->wCfgFileStream.get(), &localFileLines, false, false, true, false);
		}
		else
		{
			std::vector<std::string> localFileLines;

			status = SettingsLib::Tools::storeFstream2Memory(this->cfgFileStream.get(), &localFileLines, 0, true, false);

			this->cfgFileMode = std::ios_base::out | std::ios_base::trunc;

			this->closeConfigStream();
			this->openConfigStream(false, false);

			status = SettingsLib::Tools::storeMemory2Fstream(this->cfgFileStream.get(), this->cfgStore.get(), true, false, true, true);
			status = SettingsLib::Tools::storeMemory2Fstream(this->cfgFileStream.get(), &localFileLines, false, false, true, false);
		}
	}

	// Restore the original openmode and file stream state before the operarion:

	this->closeConfigStream();
	this->cfgFileMode = oldMode;
	this->openConfigStream(false, false);

    return 0;
}

std::vector<std::exception> SettingsLib::Types::ConfigFileStream::getErrorList()
{
	if (this->errorsList != nullptr)
	{
		return *this->errorsList.get();
	}

    return std::vector<std::exception>();
}

void SettingsLib::Types::ConfigFileStream::cleanErrors()
{
	if (this->errorsList != nullptr)
	{
		this->errorsList->clear();
	}
}

void SettingsLib::Types::ConfigFileStream::setErrorReport(unsigned short maxErrorReports)
{
	if (maxErrorReports == 0)
	{
		this->errorReportEnabled = false;
		this->errorListMaxReports = 0;
		this->errorsList.reset(nullptr);
	}
	else
	{
		if (maxErrorReports >= SHRT_MAX)
		{
			maxErrorReports = CONFIG_FILE_STREAM_MAXIMUM_ERRORS;
		}

		this->errorReportEnabled = true;
		this->errorListMaxReports = maxErrorReports;
		this->errorsList.reset(new std::vector<std::exception>);
	}
}
