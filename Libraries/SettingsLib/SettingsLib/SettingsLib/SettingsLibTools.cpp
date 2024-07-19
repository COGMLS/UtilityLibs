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
			unsigned long long nLinesRead = 0ull;

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
					if (nLinesRead == readLines)
					{
						break;
					}
				}

				vMemStore->push_back(line);
				line.clear();

				nLinesRead++;
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

int SettingsLib::Tools::storeFstream2Memory(std::wfstream *fs, std::vector<std::wstring> *vMemStore, unsigned long long readLines, bool resetPosBeforeOp, bool seekBeginPostOp)
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
			unsigned long long nLinesRead = 0ull;

			if (resetPosBeforeOp)
			{
				fs->seekg(std::wfstream::beg);
				fs->seekp(std::wfstream::beg);
			}

			std::wstring line;

			while (std::getline(*fs, line))
			{
				if (readLines != 0)
				{
					if (nLinesRead == readLines)
					{
						break;
					}
				}

				vMemStore->push_back(line);
				line.clear();

				nLinesRead++;
			}

			if (seekBeginPostOp)
			{
				fs->seekg(std::wfstream::beg);
				fs->seekp(std::wfstream::beg);
			}

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		return 4;
	}
}

int SettingsLib::Tools::storeMemory2Fstream(std::fstream *fs, std::vector<std::string> *vMemStore, bool resetPosBeforeOp, bool seekBeginPostOp)
{
    if (fs == nullptr)
	{
		return 2;
	}

	if (vMemStore == nullptr)
	{
		return 3;
	}

	try
	{
		// Check if the file is open:
		if (fs->is_open())
		{
			// Reset position before operation:
			if (resetPosBeforeOp)
			{
				fs->seekg(std::fstream::beg);
				fs->seekp(std::fstream::beg);
			}

			// Insert each line inside the vMemStore into fstream:
			for (size_t i = 0; i < vMemStore->size(); i++)
			{
				std::string l = vMemStore->at(i);
				*fs << l;
			}

			// Reset position after operation:
			if (seekBeginPostOp)
			{
				fs->seekg(std::fstream::beg);
				fs->seekp(std::fstream::beg);
			}

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		return 4;
	}
}

int SettingsLib::Tools::storeMemory2Fstream(std::wfstream *fs, std::vector<std::wstring> *vMemStore, bool resetPosBeforeOp, bool seekBeginPostOp)
{
    if (fs == nullptr)
	{
		return 2;
	}

	if (vMemStore == nullptr)
	{
		return 3;
	}

	try
	{
		// Check if the file is open:
		if (fs->is_open())
		{
			// Reset position before operation:
			if (resetPosBeforeOp)
			{
				fs->seekg(std::wfstream::beg);
				fs->seekp(std::wfstream::beg);
			}

			// Insert each line inside the vMemStore into fstream:
			for (size_t i = 0; i < vMemStore->size(); i++)
			{
				std::wstring l = vMemStore->at(i);
				*fs << l;
			}

			// Reset position after operation:
			if (seekBeginPostOp)
			{
				fs->seekg(std::wfstream::beg);
				fs->seekp(std::wfstream::beg);
			}

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		return 4;
	}
}
