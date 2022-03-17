#include "stdafx.h"
#include "Logger.h"

using namespace std;

/** /
	bool debug = true;
/**/
/**/
	bool debug = false;
/**/

Logger::Logger()
{
	if (debug)
	{
		logWofstream.open(LOG_FILE_NAME, ios_base::out);
	}
}

Logger::~Logger()
{
	if (debug)
	{
		logWofstream.close();
	}
}

Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}

void Logger::log(long l)
{
	if (debug)
	{
		logWofstream << l;
		logWofstream.flush();
	}
}

void Logger::logln(long l)
{
	if (debug)
	{
		logWofstream << l << EOL;
		logWofstream.flush();
	}
}

void Logger::log(const wstring message)
{
	if (debug)
	{
		logWofstream << message;
		logWofstream.flush();
	}
}

void Logger::logln(const wstring message)
{
	if (debug)
	{
		logWofstream << message << EOL;
		logWofstream.flush();
	}
}

void Logger::log(const HWND hwnd)
{
	if (debug)
	{
		logWofstream << hwnd;
		logWofstream.flush();
	}
}

void Logger::logln(const HWND hwnd)
{
	if (debug)
	{
		logWofstream << hwnd << EOL;
		logWofstream.flush();
	}
}

void Logger::log(const vector<int> intVector)
{
	if (debug)
	{
		for (int i = 0; i < static_cast<int>(intVector.size()); i++)
		{
			const int& value = intVector[i];
			logWofstream << value;
			logWofstream.flush();
		}
	}
}

void Logger::logln(const vector<int> intVector)
{
	if (debug)
	{
		for (int i = 0; i < static_cast<int>(intVector.size()); i++)
		{
			const int& value = intVector[i];
			logWofstream << value << EOL;
			logWofstream.flush();
		}
	}
}

void Logger::log(const vector<long> longVector)
{
	if (debug)
	{
		for (int i = 0; i < static_cast<int>(longVector.size()); i++)
		{
			const long& value = longVector[i];
			logWofstream << value;
			logWofstream.flush();
		}
	}
}

void Logger::logln(const vector<long> longVector)
{
	if (debug)
	{
		for (int i = 0; i < static_cast<int>(longVector.size()); i++)
		{
			const long& value = longVector[i];
			logWofstream << value << EOL;
			logWofstream.flush();
		}
	}
}

void Logger::log(const vector<wstring> wstringVector)
{
	if (debug)
	{
		for (int i = 0; i < static_cast<int>(wstringVector.size()); i++)
		{
			const wstring& value = wstringVector[i];
			logWofstream << value;
			logWofstream.flush();
		}
	}
}

void Logger::logln(const vector<wstring> wstringVector)
{
	if (debug)
	{
		for (int i = 0; i < static_cast<int>(wstringVector.size()); i++)
		{
			const wstring& value = wstringVector[i];
			logWofstream << value << EOL;
			logWofstream.flush();
		}
	}
}
