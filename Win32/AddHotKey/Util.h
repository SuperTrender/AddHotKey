#pragma once

#define LAST_ERROR_PLACE_HOLDER _T("${lastError}")
#define COMMA _T(',')
#define SPACE _T(' ')

void printError(const std::wstring& msg);
void processPlaceHolder(std::wstring& srcString, const std::wstring& placeHolderName,
                        const std::wstring& placeHolderValue);
const std::wstring longToString(long i);
const std::wstring s2ws(const char* s);
const std::wstring s2ws(const std::string& s);
const std::wstring getProcessDir(LPCTSTR processName);
const bool getProcessID(LPCTSTR processName, DWORD& processID);
std::vector<std::wstring>& split(const std::wstring& s, wchar_t delim, std::vector<std::wstring>& elems);
std::vector<std::wstring> split(const std::wstring& s, wchar_t delim);
std::wstring getLastSplittedElement(const std::wstring& s, wchar_t delim);
FILE* openFile(LPCTSTR fileName, LPCTSTR mode);
void closeFile(FILE* file);
