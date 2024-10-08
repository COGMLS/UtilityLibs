#include <iostream>

#include "LoggerLibVersionTools.hpp"
#include "Logger.hpp"

int main()
{
	std::cout << "Logger Library Console Test - " << LoggerLib::getVersionStr(LoggerLib::getLibVersion(), true, true) << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;

	Logger logger(std::filesystem::current_path(), "logTest");

	std::cout << "Created log " << logger.getLogFilePath().filename().string() << std::endl;

	logger.newEntry(LogEntry("Test", "This is a log test"));
	logger.newEntry(LogEntry("NewTest::", "This is a new test."));
	logger.newEntry(LogEntry("LoggerLib version: ", LoggerLib::getVersionStr(LoggerLib::getLibVersion(), true, true)));
	
	int logSavStatus = logger.saveLog();
	
	return 0;
}