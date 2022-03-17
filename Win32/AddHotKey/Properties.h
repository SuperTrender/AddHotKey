#pragma once

#include <map>

class Properties
{
public:
	const bool parseProperties(const std::wstring& propertiesFileName);
	const std::wstring getProperty(const std::wstring& key) const;
private:
	typedef std::map<std::wstring, std::wstring> PropertiesMap;
	PropertiesMap propertiesMap;
	FILE* openFile(LPCTSTR fileName, LPCTSTR mode) const;
	const bool readLine(FILE* file, std::wstring& line) const;
	void parseProperty(const std::wstring& prop);
	void parseKeyAndValue(const std::wstring& srcStr, std::wstring& key,
						  std::wstring& value) const;
};
