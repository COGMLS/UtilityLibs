#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

#include "LoggerLib.hpp"

int main(int argc, const char* argv[])
{
	#ifdef _WIN32
	LogEntry startApp = LogEntry("[Application Start]::", "HighPrecisionLocalTime::", getLoggerDateTime(true, false), true);
	#else
	LogEntry startApp = LogEntry("[Application Start]::", "HighPrecisionLocalTime::", getLoggerDateTime(true, true), true);
	#endif // !_WIN32

	bool testAutoSave = false;
	bool testSortLogFiles = false;
	bool testPointerLogger = false;
	bool testStreamOperator = false;
	bool testLogEntryEqOperator = false;
	bool testLogInfoFormatter = false;

	std::vector<std::string> args;
	for (size_t i = 0; i < argc; i++)
	{
		std::string arg = argv[i];

		args.push_back(arg);

		if (i != 0)
		{
			std::transform(arg.begin(), arg.end(), arg.begin(), [](unsigned char c){return std::tolower(c);});
		}

		if (arg == "--testautosave" || arg == "-a")
		{
			testAutoSave = true;
		}

		if (arg == "--testsortfiles" || arg == "-sort")
		{
			testSortLogFiles = true;
		}

		if (arg == "--testpointerlogger" || arg == "-p")
		{
			testPointerLogger = true;
		}

		if (arg == "--teststreamop" || arg == "-stream")
		{
			testStreamOperator = true;
		}

		if (arg == "--testlogentryeqop" || arg == "-eq")
		{
			testLogEntryEqOperator = true;
		}

		if (arg == "--testloginfoformatter" || arg == "-formatter")
		{
			testLogInfoFormatter = true;
		}
	}

	std::cout << "Logger Library Console Test - " << LoggerLib::getVersionStr(LoggerLib::getLibVersion(), true, true) << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;

	/* Space to test the parameters and send error messages:
	 * ---------------------------------------------------------
	 * 
	*/

	int errorStatus = 0;

	#ifndef LOGGER_INFORMATION_FORMATTER_HPP
	if (testLogInfoFormatter)
	{
		std::cout << "Invalid Argument: --testloginfoformatter | -formatter" << std::endl;
	}
	#endif // !LOGGER_INFORMATION_FORMATTER_HPP

	if (errorStatus != 0)
	{
		return errorStatus;	// Terminate the application
	}

	//
	// ---------------------------------------------------------
	//

	// Create the application logger:

	Logger logger(std::filesystem::current_path(), "logTest");
	
	std::cout << "Created log " << logger.getLogFilePath().filename().string() << std::endl;

	logger.newEntry(startApp);
	logger.newEntry(LogEntry("AppName::", "Utility Library Console Test"));
	logger.newEntry(LogEntry("AppVersion::", "1.5.1"));
	logger.newEntry(LogEntry("LoggerLib version: ", LoggerLib::getVersionStr(LoggerLib::getLibVersion(), true, true)));
	logger.newEntry(LogEntry("", ""));	// New line on log file
	logger.newEntry(LogEntry("AppCli::", "Number of arguments used: ", static_cast<long long>(argc)));

	for (size_t i = 0; i < args.size(); i++)
	{
		logger.newEntry(LogEntry("Cli Index: " + std::to_string(i), " | " + args[i]));
	}
	
	int logSavStatus = logger.saveLog();

	if (testAutoSave)
	{
		logger.setAutoSave(true, 5);
	}

	logger.newEntry(LogEntry("Test - ", "This is a log test"));
	logger.newEntry(LogEntry("NewTest::", "This is a new test."));
	
	if (testStreamOperator)
	{
		LogEntry log_entry("StreamOperatorTest::", "Test with operator<< with LogDataStore enabled");
		#if defined(LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE) && defined(LOGGER_ENABLE_EXPERIMENTAL_LOG_ENTRY_OPERATORS)
		std::cout << log_entry << std::endl;
		#else
		std::cout << "LogEntry Stream Insertion operator is disabled in this compilation" << std::endl;
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE && !LOGGER_ENABLE_EXPERIMENTAL_LOG_ENTRY_OPERATORS
	}

	if (testSortLogFiles)
	{
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
	}

	if (testLogEntryEqOperator)
	{
		LogEntry a("Title", "Message", 1.5f);
	
		LogEntry b = a;
	
		if (a == b)
		{
			logger.newEntry(LogEntry("Test of LogEntry Equality::", "LogEntry equality result: Equal", " | LogEntry test info: Title: 'Title', Message: 'Message', Data: '1.5f'"));
			std::cout << "A eq B" << std::endl;
		}
		else
		{
			logger.newEntry(LogEntry("Test of LogEntry Equality::", "LogEntry equality result: Not Equal"));
			std::cout << "A not eq B" << std::endl;
		}
	}

	if (testPointerLogger)
	{
		Logger* pLogger = new Logger(std::filesystem::current_path(), "pLogTest");
	
		pLogger->setAutoSave(true, 5);
	
		for (size_t i = 0; i < 25; i++)
		{
			pLogger->newEntry(LogEntry("Test " + std::to_string(i) + "::", "Message ", static_cast<long long>(i)));
		}
	
		pLogger->~Logger();
		pLogger = nullptr;
	}

	#ifdef LOGGER_INFORMATION_FORMATTER_HPP
	if (testLogInfoFormatter)
	{
		std::string logInfo = "{title}::{message}-{data}";
		//createFormatTest(logInfo);
		LogFormat formatter1(logInfo, "");
		LogFormat formatter2(") {title} => {message}");

		std::cout << formatter1.formatInfo({"Entry Test", "Message test"}) << std::endl;
		std::cout << formatter1.formatInfo({"Entry Test 1", "Message test 1", "Data test"}) << std::endl;
		std::cout << formatter2.formatInfo({"Entry Test 2", "Message 2", "Extra data example"}) << std::endl;
	}
	#endif // !LOGGER_INFORMATION_FORMATTER_HPP
	
	return 0;
}