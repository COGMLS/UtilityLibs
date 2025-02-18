#include <iostream>

#include "LoggerLib.hpp"

int main(int argc, const char* argv[])
{
	std::cout << "Logger Library Console Test - " << LoggerLib::getVersionStr(LoggerLib::getLibVersion(), true, true) << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;

	Logger logger(std::filesystem::current_path(), "logTest");

	std::cout << "Created log " << logger.getLogFilePath().filename().string() << std::endl;

	logger.newEntry(LogEntry("Test", "This is a log test"));
	logger.newEntry(LogEntry("NewTest::", "This is a new test."));
	logger.newEntry(LogEntry("LoggerLib version: ", LoggerLib::getVersionStr(LoggerLib::getLibVersion(), true, true)));
	
	int logSavStatus = logger.saveLog();

	std::filesystem::path appRoot = std::filesystem::path(argv[0]).parent_path();

	std::vector<std::filesystem::path> logs = getLogFileList(appRoot);

	for (std::filesystem::path& l : logs)
	{
		std::cout << l.filename() << " | " << std::filesystem::last_write_time(l) << std::endl;
	}

	std::cout << std::endl << std::endl << "Sorting logs..." << std::endl << std::endl;
	sortLogFileList(logs, false);

	for (std::filesystem::path& l : logs)
	{
		std::cout << l.filename() << " | " << std::filesystem::last_write_time(l) << std::endl;
	}

	LogEntry a("Title", "Message", 1.5f);

	LogEntry b = a;

	if (a == b)
	{
		std::cout << "A eq B" << std::endl;
	}
	else
	{
		std::cout << "A not eq B" << std::endl;
	}
	
	return 0;
}