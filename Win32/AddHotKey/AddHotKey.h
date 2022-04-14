#pragma once

typedef struct tagTAB
{
	LONG left;
	LONG right;
} TAB;

std::vector<HHOOK> addHooks(void);
BOOL CALLBACK addHooksProc(HWND hWnd, LPARAM lParam);
HHOOK addHook(int idHook, const std::string& hookProcName, DWORD dwThreadId);
void removeHooks(const std::vector<HHOOK>& hHooks);
void changeTimeframe(const int buttonIndex);
void changeTemplate(const std::wstring& templateName);
void changeChart(const bool forward);
void scrollTabs(const bool forward);
void toggleAutoScroll(void);
void changeTimeframeQuik(const int menuItemIndex);
void minimizeActiveChildWindowQuik();
const TAB getActiveTab(HWND hWnd);
const std::wstring getWindowText(HWND hWnd);
const int getButtonIndex(const bool forForward);
const int getButtonIdCommand(HWND hWnd, const int buttonIndex);
const int getMenuItemIndex(const bool forForward);
const int getMenuItemIdCommand(HMENU hMenu, const std::wstring& srcMenuItemName);
const int getIndex(const bool forForward, const std::vector<int>& timeframes, const int checkedIndex);
const int getCurrentTimeframeIndex(void);
