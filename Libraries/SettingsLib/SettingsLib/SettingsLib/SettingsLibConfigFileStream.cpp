#include "SettingsLibConfigFileStream.hpp"

SettingsLib::ConfigFileStream::ConfigFileStream()
{
}

SettingsLib::ConfigFileStream::ConfigFileStream(std::filesystem::path cfgFilePath, bool useWideData, bool useReadonly, bool keepCfgStore)
{
	this->cfgFilePath = cfgFilePath;
	this->isWideData = useWideData;
	this->isReadonly = useReadonly;
	this->keepCfgStore = keepCfgStore;

	this->isNewFile = false;
	this->errorsList = new std::vector<std::exception>;

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

		if (this->isWideData)
		{
			// Not ready the wide stream
		}
		else
		{
			this->cfgFileStream = new std::fstream;

			try
			{
				this->cfgFileStream->open(this->cfgFilePath.string(), this->cfgFileMode);

				if (this->cfgFileStream->is_open())
				{
					if (this->keepCfgStore)
					{
						// Store Fstream to Vector Memmory:
						int sFs2Vmem = SettingsLib::Tools::storeFstream2Memory(this->cfgFileStream, this->cfgStore, 0, true, true);

						if (sFs2Vmem == 0)
						{
							// Use the vector to analyze the lines:
							// Call function to analyze the line
						}
						else
						{
							this->errorsList->push_back(std::exception(std::string("Fail to read into the memory the cfgFileStream. Return " + std::to_string(sFs2Vmem)).c_str()));
						}
					}
					else
					{
						
					}
				}
				else
				{
					this->errorsList->push_back(std::exception("Fail to open the configuration file!"));
				}
			}
			catch(const std::exception& e)
			{
				this->errorsList->push_back(e);
			}
		}
	}
	else
	{
		this->isCfgFileOk = false;
		this->errorsList->push_back(std::exception("cfgFilePath does not lead to a configuration file!"));
	}
}
