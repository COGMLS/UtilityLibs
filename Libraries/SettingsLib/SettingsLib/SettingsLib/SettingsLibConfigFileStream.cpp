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
				//int sWFs2Vmem = SettingsLib::Tools::storeFstream2Memory(this->wCfgFileStream.get(), this->wCfgStore.get(), 0, true, true);

				//if (sWFs2Vmem != 0)
				//{
				//	this->errorsList->push_back(std::exception(std::string("Fail to read into the memory the wCfgFileStream. Return " + std::to_string(sWFs2Vmem)).c_str()));
				//}

				return 1;
			}
			catch(const std::exception& e)
			{
				this->errorsList->push_back(e);
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
					this->errorsList->push_back(std::exception(std::string("Fail to read into the memory the cfgFileStream. Return " + std::to_string(sFs2Vmem)).c_str()));
				}

				return 1;
			}
			catch(const std::exception& e)
			{
				this->errorsList->push_back(e);
				return -1;
			}
		}
	}

	return 0;
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
	this->errorsList.reset(new std::vector<std::exception>);

	if (!std::filesystem::exists(this->cfgFilePath))
	{
		this->isNewFile = true;
	}

	if (std::filesystem::is_regular_file(this->cfgFilePath) && !this->isNewFile)
	{
		if (this->isReadonly && !this->isNewFile)
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
		this->isCfgFileOk = false;
		this->errorsList->push_back(std::exception("cfgFilePath does not lead to a configuration file!"));
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

	if (this->cfgStore != nullptr)
	{
		this->cfgStore.reset(nullptr);
	}

	if (this->wCfgStore != nullptr)
	{
		this->wCfgStore.reset(nullptr);
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
			this->errorsList->push_back(e);
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
			this->errorsList->push_back(e);
		}
	}

	// Report is the opening file fail:
	if (!successfullyOpened)
	{
		this->errorsList->push_back(std::exception("Fail to open the configuration file!"));
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

int SettingsLib::Types::ConfigFileStream::getConfigLines(std::vector<std::string> *vMemStore)
{
	if (vMemStore == nullptr)
	{
		return -2;
	}
	if (this->keepCfgStore)
	{
		if (this->isWideData)
		{
			return -1;
		}
		else
		{
			try
			{
				*vMemStore = *this->cfgStore.get();
				return 1;
			}
			catch(const std::exception& e)
			{
				this->errorsList->push_back(e);
				return -3;
			}
			
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

void SettingsLib::Types::ConfigFileStream::getConfigStream(std::fstream *cfgFileStream)
{
	cfgFileStream = this->cfgFileStream.get();
}

size_t SettingsLib::Types::ConfigFileStream::getvMemStoreSize()
{
	if (this->cfgStore != nullptr || this->wCfgStore != nullptr)
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

void SettingsLib::Types::ConfigFileStream::refreshCfgStore()
{
	// Verify if the config stream is accessible and save it into store:
	if (this->isConfigStreamOpen())
	{
		this->save2Store();
	}
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
		if (this->isWideData)
		{
			this->wCfgStore.reset(new std::vector<std::wstring>);
		}
		else
		{
			this->cfgStore.reset(new std::vector<std::string>);
		}
	}

	this->keepCfgStore = keepCfgStore;
}

bool SettingsLib::Types::ConfigFileStream::isReadonlyMode()
{
    return this->isReadonly;
}

std::vector<std::exception> SettingsLib::Types::ConfigFileStream::getErrorList()
{
	if (this->errorsList != nullptr)
	{
		return *this->errorsList.get();
	}

    return std::vector<std::exception>();
}
