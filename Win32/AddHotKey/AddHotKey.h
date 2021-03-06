#pragma once

typedef struct tagTAB
{
    LONG left;
    LONG right;
} TAB;

const std::vector<HHOOK> addHooks(void);
BOOL CALLBACK addHooksProc(HWND hWnd, LPARAM lParam);
HHOOK addHook(int idHook, const std::string& hookProcName, DWORD dwThreadId);
void removeHooks(const std::vector<HHOOK>& hHooks);
const std::wstring findTabsClassName(HWND hwndMT, const std::wstring& tabsClassNamePrefix);
BOOL CALLBACK findTabsClassNameProc(HWND hWnd, LPARAM lParam);
void changeTimeframe(const int buttonIndex);
void changeTemplate(const std::wstring& templateName);
void changeChart(const bool forward);
void scrollTabs(const bool forward);
void toggleAutoScroll(void);
void changeTimeframeQuik(const int menuItemIndex);
void minimizeActiveChildWindowQuik();
const TAB getActiveTab(HWND hWnd);
const int getButtonIndex(const bool forForward);
const int getMenuItemIndex(const bool forForward);
const int getMenuItemIdCommand(HMENU hMenu, const std::wstring& srcMenuItemName);
const int getIndex(const bool forForward, const std::vector<int>& timeframes, const int checkedIndex);
const int getCurrentTimeframeIndex(void);
const std::wstring getWindowText(HWND hWnd);
