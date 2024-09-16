#include <iostream>

#include "LoggerLibDef.hpp"
#include "Logger.hpp"

//#include "../LoggerLib/Logger.hpp

int main()
{
	Logger logger(std::filesystem::current_path(), "logTest");

	std::cout << "Created log " << logger.getLogFilePath().filename().string() << std::endl;

	logger.newEntry(LogEntry("Test", "This is a log test"));
	logger.newEntry(LogEntry("NewTest::", "This is a new test."));
	
	int logSavStatus = logger.saveLog();
	
	return 0;
}