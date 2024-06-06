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