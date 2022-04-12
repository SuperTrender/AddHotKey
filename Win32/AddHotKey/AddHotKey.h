#pragma once

#define MAX_CLASS_NAME 256

enum Period {H1 = 4, H4 = 5, D1 = 6, W1 = 7, MN = 8};
enum PeriodQuik {Hourly = 11, Daily = 14, Weekly = 15, Monthly = 16};

typedef struct tagTAB
{
	LONG left;
	LONG right;
} TAB;

const int CHARTS_MENU_POSITION = 4;
const int TEMPLATE_MENU_POSITION = 9;
const int AUTO_SCROLL_BUTTON_INDEX = 7;
const int UNKNOWN_INDEX = -1;
const int UNKNOWN_BUTTON_INDEX = -1;
const int UNKNOWN_MENU_ITEM_INDEX = -1;
const int UNKNOWN_MENU_ID_COMMAND = -1;
const int CHARTS_TAB_COUNT = 9;
const int DATA_EXPORT_MENU_POSITION_QUIK = 1;
const int CHARTS_MENU_POSITION_QUIK = 2;
const int INTERVAL_MENU_POSITION_QUIK = 15;

std::vector<HHOOK> addHooks(void);
BOOL CALLBACK addHooksProc(HWND hWnd, LPARAM lParam);
HHOOK addHook(int idHook, const std::string& hookProcName, DWORD dwThreadId);
void removeHooks(const std::vector<HHOOK>& hHooks);
std::vector<int> initPeriods(void);
std::vector<int> initPeriodsQuik(void);
std::vector<std::wstring> initTemplates(void);
std::vector<std::wstring> initTemplatesFX(void);
void toggleAutoScroll(void);
void changePeriod(const int buttonIndex);
void changePeriodQuik(const int menuItemIndex);
void changeTemplate(const std::wstring& templateName);
void changeGraphic(const bool forward);
void scrollTabs(const bool forward);
void minimizeActiveChildWindowQuik();
const HWND getHwndMain(const std::wstring& className);
const HWND getHwndMT(void);
const HWND getHwndQuik(void);
const HWND getHwndStandard(void);
const HWND getHwndCharts(void);
const HWND getHwndPeriod(void);
const HWND getHwndTabs(void);
const HMENU getHmenuInterval(void);
const TAB getActiveTab(HWND hWnd);
const std::wstring getWindowText(HWND hWnd);
const int getButtonIndex(const bool forForward);
const int getButtonIdCommand(HWND hWnd, const int buttonIndex);
const int getMenuItemIndex(const bool forForward);
const int getMenuItemIdCommand(HMENU hMenu, const std::wstring& srcMenuItemName);
const int getIndex(const bool forForward, const std::vector<int>& periods,
				   const int checkedIndex);
const int getCurrentPeriodIndex(void);
