#include "stdafx.h"
#include "AddHotKey.h"
#include "Config.h"
#include "Logger.h"
#include "Util.h"

using namespace std;

vector<HHOOK> hHooksKeyboard;
wstring tabsClassName;

const vector<HHOOK> addHooks(void)
{
	if (!EnumWindows(addHooksProc, NULL))
	{
		wstring errorMessage(_T("Failed to enumerate windows"));
		printError(errorMessage);
	}
	return hHooksKeyboard;
}

BOOL CALLBACK addHooksProc(HWND hWnd, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	TCHAR className[MAX_CLASS_NAME];
	if (!GetClassName(hWnd, className, MAX_CLASS_NAME))
	{
		wstring errorMessage(_T("Failed to get class name"));
		printError(errorMessage);
		return TRUE;
	}
	if (Config::getInstance().getMetaTraderClassName() == className)
	{
		hHooksKeyboard.push_back(addHook(WH_KEYBOARD, "KeyboardProcMetaTrader", GetWindowThreadProcessId(hWnd, NULL)));
	}
	else if (Config::getInstance().getQuikClassName() == className)
	{
		hHooksKeyboard.push_back(addHook(WH_KEYBOARD, "KeyboardProcQuik", GetWindowThreadProcessId(hWnd, NULL)));
	}
	return TRUE;
}

HHOOK addHook(int idHook, const string& hookProcName, DWORD dwThreadId)
{
	HHOOK hHook = NULL;
	HOOKPROC hookProc;
	static HINSTANCE hinstDLL;
	wstring fileNameDLL(_T("AddHotKeyHook.dll"));
	hinstDLL = LoadLibrary(fileNameDLL.c_str());
	if (NULL != hinstDLL)
	{
		hookProc = (HOOKPROC) GetProcAddress(hinstDLL, hookProcName.c_str());
		if (NULL != hookProc)
		{
			hHook = SetWindowsHookEx(idHook, hookProc, hinstDLL, dwThreadId);
			if (NULL == hHook)
			{
				wstring errorMessage(_T("Failed to set windows hook - "));
				errorMessage += s2ws(hookProcName);
				printError(errorMessage);
			}
		}
		else
		{
			wstring errorMessage(_T("Failed to get proc address - "));
			errorMessage += s2ws(hookProcName);
			printError(errorMessage);
		}
		FreeLibrary(hinstDLL);
	}
	else
	{
		wstring errorMessage(_T("Failed to load library - "));
		errorMessage += fileNameDLL;
		printError(errorMessage);
	}
	return hHook;
}

void removeHooks(const vector<HHOOK>& hHooks)
{
	for (int i = 0; i < static_cast<int>(hHooks.size()); i++)
	{
		const HHOOK& hHook = hHooks[i];
		if (!UnhookWindowsHookEx(hHook))
		{
//			wstring errorMessage(_T("Failed to unhook windows hook"));
//			printError(errorMessage);
		}
	}
}

const wstring findTabsClassName(HWND hwndMT)
{
	EnumChildWindows(hwndMT, findTabsClassNameProc, NULL);
	return tabsClassName;
}

BOOL CALLBACK findTabsClassNameProc(HWND hWnd, LPARAM lParam)
{
	wstring windowText = getWindowText(hWnd);
	TCHAR className[MAX_CLASS_NAME];
	GetClassName(hWnd, className, MAX_CLASS_NAME);
	tabsClassName = className;
	if (tabsClassName.find(_T("Afx:")) != wstring::npos)
	{
		return FALSE;
	}
	return TRUE;
}

void changeTimeframe(const int buttonIndex)
{
	HWND hwndTimeframes = Config::getInstance().getTimeframesHwnd();
	TimeframesButtonIdCommandMap timeframesButtonIdCommandMap = Config::getInstance().getTimeframesButtonIdCommandMap();
	if (FAILED(SendMessage(hwndTimeframes, WM_COMMAND, MAKEWPARAM(timeframesButtonIdCommandMap[buttonIndex], 0), NULL)))
	{
		wstring errorMessage(_T("Failed to send WM_COMMAND message"));
		printError(errorMessage);
		return;
	}
}

void changeTemplate(const wstring& templateName)
{
	HWND hwndMT = Config::getInstance().getMTHwnd();
	HMENU hmenuBar = GetMenu(hwndMT);
	if (NULL == hmenuBar)
	{
		wstring errorMessage(_T("Failed to find hmenuBar"));
		printError(errorMessage);
		return;
	}
//	getMenuItemIdCommand(hmenuBar, _T("~DEBUG~"));
	HMENU hmenuCharts = GetSubMenu(hmenuBar, CHARTS_MENU_POSITION);
	if (NULL == hmenuCharts)
	{
		wstring errorMessage(_T("Failed to find hmenuCharts"));
		printError(errorMessage);
		return;
	}
	HMENU hmenuTemplate = GetSubMenu(hmenuCharts, TEMPLATE_MENU_POSITION);
	if (NULL == hmenuTemplate)
	{
		wstring errorMessage(_T("Failed to find hmenuTemplate"));
		printError(errorMessage);
		return;
	}
	const int menuIdCommand = getMenuItemIdCommand(hmenuTemplate, templateName);
	if (UNKNOWN_MENU_ID_COMMAND == menuIdCommand)
	{
		wstring errorMessage(_T("Failed to find template: "));
		errorMessage += templateName;
		MessageBox(NULL, errorMessage.c_str(), NULL, MB_OK | MB_ICONERROR);
		return;
	}
	if (FAILED(SendMessage(hwndMT, WM_COMMAND, MAKEWPARAM(menuIdCommand, 0), NULL)))
	{
		wstring errorMessage(_T("Failed to send WM_COMMAND message"));
		printError(errorMessage);
		return;
	}
}

void changeChart(const bool forward)
{
	HWND hwndTabs = Config::getInstance().getTabsHwnd();
	TAB activeTab = getActiveTab(hwndTabs);
	int deltaX = 10;
	int x = 0;
	int y = 18;
	if (forward)
	{
		x = activeTab.right + deltaX;
	}
	else
	{
		x = activeTab.left - deltaX;
	}
	if ((-1 == activeTab.right) || (-1 == activeTab.left))
	{
		x = 10;
	}
	LPARAM lParam = MAKELPARAM(x, y);
	if (FAILED(SendMessage(hwndTabs, WM_LBUTTONDOWN, MK_LBUTTON, lParam)))
	{
		wstring errorMessage(_T("Failed to send WM_LBUTTONDOWN message"));
		printError(errorMessage);
		return;
	}
	if (FAILED(SendMessage(hwndTabs, WM_LBUTTONUP, MK_LBUTTON, lParam)))
	{
		wstring errorMessage(_T("Failed to send WM_LBUTTONUP message"));
		printError(errorMessage);
		return;
	}
}

void scrollTabs(const bool forward)
{
	HWND hwndTabs = Config::getInstance().getTabsHwnd();
	WINDOWINFO windowInfo;
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwndTabs, &windowInfo);
	POINT pt;
	if (forward)
	{
		pt.x = windowInfo.rcClient.right - 10;
	}
	else
	{
		pt.x = windowInfo.rcClient.right - 30;
	}
	pt.y = (windowInfo.rcClient.bottom - windowInfo.rcClient.top) / 2;
// 	ClientToScreen(hwndCharts, &pt);
// 	SetCursorPos(pt.x, pt.y);
	LPARAM lParam = MAKELPARAM(pt.x, pt.y);
	SendMessage(hwndTabs, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
	SendMessage(hwndTabs, WM_LBUTTONUP, MK_LBUTTON, lParam);
}

void toggleAutoScroll()
{
	HWND hwndCharts = Config::getInstance().getChartsHwnd();
	int autoScrollButtonIdCommand = Config::getInstance().getAutoScrollButtonIdCommand();
	if (FAILED(SendMessage(hwndCharts, WM_COMMAND, MAKEWPARAM(autoScrollButtonIdCommand, 0), NULL)))
	{
		wstring errorMessage(_T("Failed to send WM_COMMAND message"));
		printError(errorMessage);
		return;
	}
}

void changeTimeframeQuik(const int menuItemIndex)
{
	HWND hwndQuik = Config::getInstance().getQuikHwnd();
	HMENU hmenuInterval = Config::getInstance().getIntervalHmenu();
	//	getMenuItemIdCommand(hmenuInterval, _T("~DEBUG~"));
	const int menuIdCommand = GetMenuItemID(hmenuInterval, menuItemIndex);
	if (UNKNOWN_MENU_ID_COMMAND == menuIdCommand)
	{
		wstring errorMessage(_T("Failed to get menu item ID for menu item index "));
		errorMessage += longToString(menuItemIndex);
		MessageBox(NULL, errorMessage.c_str(), NULL, MB_OK | MB_ICONERROR);
		return;
	}
	if (FAILED(SendMessage(hwndQuik, WM_COMMAND, MAKEWPARAM(menuIdCommand, 0), NULL)))
	{
		wstring errorMessage(_T("Failed to send WM_COMMAND message"));
		printError(errorMessage);
		return;
	}
}

void minimizeActiveChildWindowQuik()
{
	HWND hwndQuik = Config::getInstance().getQuikHwnd();
	const wstring mdiClientClassName(_T("MDIClient"));
	HWND hwndMDIClient = FindWindowEx(hwndQuik, NULL, mdiClientClassName.c_str(), NULL);
	if (NULL == hwndMDIClient)
	{
		wstring errorMessage(_T("Failed to find MDI client window with class name "));
		errorMessage += mdiClientClassName;
		printError(errorMessage);
		return;
	}
	HWND hwndActiveChild = (HWND) SendMessage(hwndMDIClient, WM_MDIGETACTIVE, NULL, NULL);
	if (NULL == hwndActiveChild)
	{
		wstring errorMessage(_T("Failed to find active child window"));
		printError(errorMessage);
		return;
	}
	ShowWindow(hwndActiveChild, SW_MINIMIZE);
}

const TAB getActiveTab(HWND hWnd)
{
	WINDOWINFO windowInfo;
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hWnd, &windowInfo);

	HDC hDc = GetDC(NULL);

	TAB tab;
	tab.left = -1;
	tab.right = -1;

	int y = windowInfo.rcClient.top;
	for (int x = windowInfo.rcClient.left; x <= windowInfo.rcClient.right; x++)
	{
		COLORREF colorRef = GetPixel(hDc, x, y);
		if ((ACTIVE_TAB_COLORREF == colorRef) && (-1 == tab.left))
		{
			//SetCursorPos(x, y);
			tab.left = x;
		}
		if ((ACTIVE_TAB_COLORREF != colorRef) && (-1 != tab.left))
		{
			//SetCursorPos(x, y);
			tab.right = x - 1;
			break;
		}
	}

	ReleaseDC(hWnd, hDc);

	if (tab.left > windowInfo.rcClient.right - 10)
	{
		tab.left = -1;
	}
	if (tab.right > windowInfo.rcClient.right - 10)
	{
		tab.right = -1;
	}
	return tab;
}

const int getButtonIndex(const bool forForward)
{
	int checkedButtonIndex = getCurrentTimeframeIndex();
	int index = getIndex(forForward, Config::getInstance().getTimeframes(), checkedButtonIndex);
	return index;
}

const int getButtonIdCommand(HWND hWnd, const int buttonIndex)
{ 
	TBBUTTON Button; 
	HANDLE hTaskProc; 
	DWORD dwProcessId; 
	LPVOID lpRemoteBuffer; 
	DWORD lpNumberOfBytesRead; 

	GetWindowThreadProcessId(hWnd, &dwProcessId); 
	hTaskProc = OpenProcess(PROCESS_ALL_ACCESS, 0, dwProcessId); 
	lpRemoteBuffer = VirtualAllocEx(hTaskProc, NULL, sizeof(TBBUTTON), MEM_COMMIT, PAGE_READWRITE);
	if (!SendMessage(hWnd, TB_GETBUTTON, buttonIndex, (LPARAM) lpRemoteBuffer))
	{
		wstring errorMessage(_T("Failed to TB_GETBUTTON"));
		printError(errorMessage);
		return -1;
	}
	if (!ReadProcessMemory(hTaskProc, lpRemoteBuffer, &Button, sizeof(TBBUTTON), &lpNumberOfBytesRead))
	{
		wstring errorMessage(_T("Failed to ReadProcessMemory"));
		printError(errorMessage);
		return -1;
	}
	VirtualFree(lpRemoteBuffer, 0, MEM_RELEASE);
	CloseHandle(hTaskProc);
	return Button.idCommand;
} 

const int getMenuItemIndex(const bool forForward)
{
	HMENU hmenuInterval = Config::getInstance().getIntervalHmenu();
	if (NULL == hmenuInterval)
	{
		return UNKNOWN_MENU_ITEM_INDEX;
	}
	int menuItemCount = GetMenuItemCount(hmenuInterval);
	if (FAILED(menuItemCount))
	{
		wstring errorMessage(_T("Failed to GetMenuItemCount"));
		printError(errorMessage);
		return UNKNOWN_MENU_ITEM_INDEX;
	}
	int checkedMenuItemIndex = UNKNOWN_MENU_ITEM_INDEX;
	for (int i = 0; i < menuItemCount; i++)
	{
		MENUITEMINFO menuItemInfo;
		menuItemInfo.cbSize = sizeof(MENUITEMINFO);
		menuItemInfo.fMask = MIIM_STATE;
		if (!GetMenuItemInfo(hmenuInterval, i, TRUE, &menuItemInfo))
		{
			wstring errorMessage(_T("Failed to find the state of menu item"));
			printError(errorMessage);
			return UNKNOWN_MENU_ITEM_INDEX;
		}
		if (MFS_CHECKED == menuItemInfo.fState)
		{
			checkedMenuItemIndex = i;
		}
	}
	return getIndex(forForward, Config::getInstance().getTimeframesQuik(), checkedMenuItemIndex);
}

const int getMenuItemIdCommand(HMENU hMenu, const wstring& srcMenuItemName)
{
	int menuItemCount = GetMenuItemCount(hMenu);
	if (FAILED(menuItemCount))
	{
		wstring errorMessage(_T("Failed to GetMenuItemCount"));
		printError(errorMessage);
		return UNKNOWN_MENU_ID_COMMAND;
	}
	for (int i = 0; i < menuItemCount; i++)
	{
		MENUITEMINFO menuItemInfo;
		menuItemInfo.cbSize = sizeof(MENUITEMINFO);
		menuItemInfo.fMask = MIIM_STRING;
		menuItemInfo.dwTypeData = NULL;
		if (!GetMenuItemInfo(hMenu, i, TRUE, &menuItemInfo))
		{
			wstring errorMessage(_T("Failed to find the size of menuItemName"));
			printError(errorMessage);
			return UNKNOWN_MENU_ID_COMMAND;
		}
		LPTSTR menuItemName = new TCHAR[menuItemInfo.cch + 1];
		menuItemInfo.dwTypeData = menuItemName;
		menuItemInfo.cch++;
		if (!GetMenuItemInfo(hMenu, i, TRUE, &menuItemInfo))
		{
			wstring errorMessage(_T("Failed to find menuItemName"));
			printError(errorMessage);
			delete menuItemName;
			return UNKNOWN_MENU_ID_COMMAND;
		}
		if (_tcsicmp(srcMenuItemName.c_str(), menuItemName) == 0)
		{
			delete menuItemName;
			return GetMenuItemID(hMenu, i);
		}
		delete menuItemName;
	}
	return UNKNOWN_MENU_ID_COMMAND;
}

const int getIndex(const bool forForward, const vector<int>& timeframes, const int checkedIndex)
{
	for (int i = 0; i < static_cast<int>(timeframes.size()); i++)
	{
		const int& value = timeframes[i];
		if (value == checkedIndex)
		{
			return checkedIndex;
		}
	}
	int index = UNKNOWN_INDEX;
	if (forForward)
	{
		for (int i = 0; i < static_cast<int>(timeframes.size()); i++)
		{
			const int& value = timeframes[i];
			if (value < checkedIndex)
			{
				index = value;
			}
		}
	}
	else
	{
		for (int i = static_cast<int>(timeframes.size()) - 1; i >= 0; i--)
		{
			const int& value = timeframes[i];
			if (value > checkedIndex)
			{
				index = value;
			}
		}
	}
	return index;
}

const int getCurrentTimeframeIndex(void)
{
	int currentTimeframeIndex = H1;
	wstring windowTextMT = getWindowText(Config::getInstance().getMTHwnd());

	wstring::size_type openBracketIndex = windowTextMT.find(_T("["));
	wstring::size_type closeBracketIndex = windowTextMT.find(_T("]"));
	if ((openBracketIndex != wstring::npos) && (closeBracketIndex != wstring::npos))
	{
		wstring currentTimeframe = getLastSplittedElement(
			windowTextMT.substr(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1), COMMA);
		TimeframesMap timeframesMap = Config::getInstance().getTimeframesMap();
		TimeframesMap::const_iterator timeframesIterator = timeframesMap.find(currentTimeframe);
		if (timeframesIterator != timeframesMap.end( ))
		{
			currentTimeframeIndex = timeframesMap[currentTimeframe];
		}
	}

	return currentTimeframeIndex;
}

const wstring getWindowText(HWND hWnd)
{
	int cTxtLen = GetWindowTextLength(hWnd);
	LPTSTR pszMem = (LPTSTR) VirtualAlloc((LPVOID) NULL, (DWORD) (cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);
	GetWindowText(hWnd, pszMem, cTxtLen + 1);
	wstring ws(pszMem);
	VirtualFree(pszMem, 0, MEM_RELEASE);
	return ws;
}
