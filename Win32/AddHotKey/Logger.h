#pragma once

#define LOG_FILE_NAME _T("AddHotKey.log")
#define EOL _T("\n")

// Singleton (http://en.wikipedia.org/wiki/Singleton_pattern#C.2B.2B)
class Logger
{
public:
	static Logger& getInstance();
	// http://hashcode.ru/questions/289383/c-unicode-%D0%BF%D1%80%D0%B8-%D0%B7%D0%B0%D0%BF%D0%B8%D1%81%D0%B8-%D0%B2-%D1%84%D0%B0%D0%B9%D0%BB
	void Logger::log(long l);
	void Logger::logln(long l);
	void Logger::log(const std::wstring message);
	void Logger::logln(const std::wstring message);
	void Logger::log(const HWND hwnd);
	void Logger::logln(const HWND hwnd);
	void Logger::log(const std::vector<int> intVector);
	void Logger::logln(const std::vector<int> intVector);
	void Logger::log(const std::vector<long> longVector);
	void Logger::logln(const std::vector<long> longVector);
	void Logger::log(const std::vector<std::wstring> wstringVector);
	void Logger::logln(const std::vector<std::wstring> wstringVector);
private:
	Logger();
	~Logger();
	Logger(const Logger&);            // intentionally undefined
	Logger& operator=(const Logger&); // intentionally undefined
	std::wofstream logWofstream;
};
