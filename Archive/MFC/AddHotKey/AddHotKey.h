#pragma once

#define LAST_ERROR_PLACE_HOLDER _T("${lastError}")

enum Period {H1 = 4, D1 = 6, W1 = 7, MN = 8};

typedef struct tagTAB
{
	LONG left;
	LONG right;
} TAB;

HHOOK addHook(int idHook, const std::string& hookProcName);
void removeHook(HHOOK hHook);
std::vector<int> initPeriods(void);
std::vector<std::wstring> initTemplates(void);
std::vector<std::wstring> initTemplatesFX(void);
const HWND getHwndPeriod(void);
void changePeriod(const int buttonIndex);
void changeTemplate(const std::wstring& templateName);
void changeGraphic(const bool forward);
void scrollTabs(const bool forward);
TAB getActiveTab(HWND hWnd);
const int getGraphicsTabCount(HWND hWnd);
void initTextract(void);
void termTextract(void);
const CString getWindowTextOCR(HWND hWnd);
const std::wstring getWindowText(HWND hWnd);
const int getButtonIndex(const bool forForward);
const int getButtonIdCommand(HWND hWnd, const int buttonIndex);
const int getMenuItemIdCommand(HMENU hMenu, const std::wstring& srcMenuItemName);
void printError(const std::wstring& msg);
void processPlaceHolder(std::wstring& srcString, const std::wstring& placeHolderName,
						const std::wstring& placeHolderValue);
const std::wstring longToString(long i);
const std::wstring s2ws(const char* s);
const std::wstring s2ws(const std::string& s);
const int getTokenCount(const CString& srcString, const CString& tokens);
