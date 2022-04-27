#include "stdafx.h"
#include "Psapi.h"
#include "shlwapi.h"
#include "Tlhelp32.h"
#include "Util.h"

using namespace std;

void printError(const wstring& msg)
{
    LPVOID lpMsgBuf;
    DWORD lastError = GetLastError();

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf, 0, NULL);

    wstring lastErrorNumber(_T("Last error number: ") LAST_ERROR_PLACE_HOLDER);
    processPlaceHolder(lastErrorNumber, LAST_ERROR_PLACE_HOLDER, longToString(lastError));

    wstring message(msg);
    message += _T("\n\n");
    message += lastErrorNumber;
    message += _T("\n\n");
    message += (LPTSTR) lpMsgBuf;
    MessageBox(NULL, message.c_str(), NULL, MB_OK | MB_ICONERROR);

    LocalFree(lpMsgBuf);
}

void processPlaceHolder(wstring& srcString, const wstring& placeHolderName, 
                        const wstring& placeHolderValue)
{
    wstring::size_type phIndex = srcString.find(placeHolderName);
    if (phIndex != wstring::npos)
    {
        srcString.replace(phIndex, placeHolderName.length(), placeHolderValue);
    }
}

const wstring longToString(long i)
{
    wstringstream wstringStream;
    wstringStream << i;
    return wstringStream.str();
}

const wstring s2ws(const char* s)
{
    int len = MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s, -1, buf, len);
    wstring ws(buf);
    delete [] buf;
    return ws;
}

const wstring s2ws(const string& s)
{
    return s2ws(s.c_str());
}

const wstring getProcessDir(LPCTSTR processName)
{
    wstring processDir;
    DWORD processID;
    if (getProcessID(processName, processID))
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
            FALSE, processID);
        if (hProcess != NULL)
        {
            TCHAR moduleFileName[MAX_PATH];
            if (GetModuleFileNameEx(hProcess, NULL, moduleFileName, MAX_PATH))
            {
                PathRemoveFileSpec(moduleFileName);
                PathAddBackslash(moduleFileName);
                processDir = moduleFileName;
            }
            else
            {
                printError(_T("Failed to get process dir"));
            }
            CloseHandle(hProcess);
        }
        else
        {
            printError(_T("Failed to open process"));
        }
    }
    else
    {
        wstring errorMessage(_T("Failed to get process id for process "));
        errorMessage += processName;
        printError(errorMessage);
    }
    return processDir;
}

const bool getProcessID(LPCTSTR processName, DWORD& processID)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        printError(_T("CreateToolhelp32Snapshot (of processes)"));
        return false;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        printError(_T("Process32First")); // Show cause of failure
        CloseHandle(hProcessSnap);        // Must clean up the snapshot object!
        return false;
    }

    bool result = false;
    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do {
        if (_tcsicmp(pe32.szExeFile, processName) != 0)
        {
            continue;
        } 
        else
        {
            processID = pe32.th32ProcessID;
            result = true;
            break;
        }
    }
    while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return result;
}

vector<wstring>& split(const wstring& s, wchar_t delim, vector<wstring>& elems)
{
    wstringstream ss(s);
    wstring item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<wstring> split(const wstring& s, wchar_t delim)
{
    vector<wstring> elems;
    split(s, delim, elems);
    return elems;
}

wstring getLastSplittedElement(const wstring& s, wchar_t delim)
{
    vector<wstring> elems = split(s, delim);
    return elems[elems.size() - 1];
}

FILE* openFile(LPCTSTR fileName, LPCTSTR mode)
{
    FILE* file = NULL;
    _tfopen_s(&file, fileName, mode);
    return file;
}

void closeFile(FILE* file)
{
    if (file != NULL)
    {
        fclose(file);
    }
}
