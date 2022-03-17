#include "stdafx.h"
//#include "atlstr.h"
#include "Properties.h"

#define FILE_MODE _T("rt, ccs=UTF-8")

using namespace std;

const wstring Properties::getProperty(const wstring& key) const
{
	PropertiesMap::const_iterator iter = propertiesMap.find(key);
	if (iter != propertiesMap.end())
	{
		return iter->second;
	}
	else
	{
		return _T("");
	}
}

FILE* Properties::openFile(LPCTSTR fileName, LPCTSTR mode) const
{
	FILE* file = NULL;
	_tfopen_s(&file, fileName, mode);
	return file;
}

const bool Properties::parseProperties(const wstring& propertiesFileName)
{
	FILE* propertiesFile = openFile(propertiesFileName.c_str(), FILE_MODE);
	if (propertiesFile == NULL)
	{
		return false;
	}
	while(!feof(propertiesFile))
	{
		wstring line;
		if (!readLine(propertiesFile, line))
		{
			return false;
		}
		parseProperty(line);
	}
	if (propertiesFile != NULL)
	{
		fclose(propertiesFile);
	}
	return true;
}

const bool Properties::readLine(FILE* file, wstring& line) const
{
	while(!feof(file))
	{
		TCHAR ch = _fgettc(file);
		if (ferror(file))
		{
			return false;
		}
		if ((ch == _T('\n')) || (ch == _TEOF))
		{
			return true;
		}
		line += ch;
	}
	return true;
}

// Multiline properties not supported.
void Properties::parseProperty(const wstring&  prop)
{
	const wstring str(prop);
	wstring key;
	wstring value;
	parseKeyAndValue(str, key, value);
	propertiesMap[key] = value;
}

void Properties::parseKeyAndValue(const wstring& srcStr, wstring& key, wstring& value) const
{
	wstring str(srcStr);
	string::size_type commentIndex = str.find(_T("#"));
	if (commentIndex != string::npos)
	{
		str = str.substr(0, commentIndex);
	}
	string::size_type eqIndex = str.find(_T("="));
	if (eqIndex != string::npos)
	{
		key = str.substr(0, eqIndex);
		value = str.substr(eqIndex + 1);

		/*
		// trimming key and value
		// TODO create function to remove spaces (trimming) from (w)string
		// using only std::(w)string 
		// for ex., see http://forums.devx.com/archive/index.php/t-93386.html
		CString csKey(key.c_str());
		CString csValue(value.c_str());
		csKey = csKey.Trim();
		csValue = csValue.Trim();
		key = csKey.GetBuffer();
		value = csValue.GetBuffer();
		*/
	}
}
