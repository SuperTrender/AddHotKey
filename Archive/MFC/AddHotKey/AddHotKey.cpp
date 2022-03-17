#include "stdafx.h"
#include "AddHotKey.h"
#include "C:\Program Files\OCRSDK\OCRSDK.h"

using namespace std;

const wstring META_TRADER_CLASS_NAME(_T("MetaQuotes::MetaTrader::4.00"));
const int GRAPHICS_MENU_POSITION = 4;
const int TEMPLATE_MENU_POSITION = 9;
const int UNKNOWN_BUTTON_INDEX = -1;
const int UNKNOWN_MENU_ID_COMMAND = -1;
const int GRAPHICS_TAB_COUNT = 9;
vector<int> periods;

HHOOK addHook(int idHook, const string& hookProcName)
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
			hHook = SetWindowsHookEx(idHook, hookProc, hinstDLL, 0);
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

void removeHook(HHOOK hHook)
{
	// Удаление глобального хука.
	UnhookWindowsHookEx(hHook);
}

vector<int> initPeriods(void)
{
	periods.push_back(H1);
	periods.push_back(D1);
	periods.push_back(W1);
	periods.push_back(MN);
	return periods;
}

vector<wstring> initTemplates(void)
{
	vector<wstring> templates;
	templates.push_back(_T("All-periods"));
	templates.push_back(_T("All-periods-ta"));
	return templates;
}

vector<wstring> initTemplatesFX(void)
{
	vector<wstring> templates;
	templates.push_back(_T("All-periods-fx"));
	templates.push_back(_T("All-periods-fx-ta"));
	return templates;
}

const HWND getHwndPeriod(void)
{
	HWND hwndMT = FindWindow(META_TRADER_CLASS_NAME.c_str(), NULL);
	if (NULL == hwndMT)
	{
		wstring errorMessage(_T("Failed to find hwndMT window"));
		printError(errorMessage);
		return NULL;
	}
	HWND hwndStandard = FindWindowEx(hwndMT, NULL, NULL, _T("Стандартная"));
	if (NULL == hwndStandard)
	{
		wstring errorMessage(_T("Failed to find hwndStandard window"));
		printError(errorMessage);
		return NULL;
	}
	HWND hwndPeriod = FindWindowEx(hwndStandard, NULL, NULL, _T("Период"));
	if (NULL == hwndPeriod)
	{
		wstring errorMessage(_T("Failed to find hwndPeriod window"));
		printError(errorMessage);
		return NULL;
	}
	return hwndPeriod;
}

void changePeriod(const int buttonIndex)
{
	HWND hwndPeriod = getHwndPeriod();
	if (NULL == hwndPeriod)
	{
		wstring errorMessage(_T("Failed to getHwndPeriod"));
		printError(errorMessage);
		return;
	}
	if (FAILED(SendMessage(hwndPeriod, WM_COMMAND,
		MAKEWPARAM(getButtonIdCommand(hwndPeriod, buttonIndex), 0), NULL)))
	{
		wstring errorMessage(_T("Failed to send WM_COMMAND message"));
		printError(errorMessage);
		return;
	}
}

void changeTemplate(const wstring& templateName)
{
	HWND hwndMT = FindWindow(META_TRADER_CLASS_NAME.c_str(), NULL);
	if (NULL == hwndMT)
	{
		wstring errorMessage(_T("Failed to find hwndMT window"));
		printError(errorMessage);
		return;
	}
	HMENU hmenuBar = GetMenu(hwndMT);
	if (NULL == hmenuBar)
	{
		wstring errorMessage(_T("Failed to find hmenuBar"));
		printError(errorMessage);
		return;
	}
//	getMenuItemIdCommand(hmenuBar, _T(""));
	HMENU hmenuGraphics = GetSubMenu(hmenuBar, GRAPHICS_MENU_POSITION);
	if (NULL == hmenuGraphics)
	{
		wstring errorMessage(_T("Failed to find hmenuGraphics"));
		printError(errorMessage);
		return;
	}
	HMENU hmenuTemplate = GetSubMenu(hmenuGraphics, TEMPLATE_MENU_POSITION);
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

int currentGraphicIndex = 0;

void changeGraphic(const bool forward)
{
	HWND hwndMT = FindWindow(META_TRADER_CLASS_NAME.c_str(), NULL);
	if (NULL == hwndMT)
	{
		wstring errorMessage(_T("Failed to find hwndMT window"));
		printError(errorMessage);
		return;
	}
	HWND hwndGraphics = FindWindowEx(hwndMT, NULL, _T("Afx:400000:b:10011:0:0"), NULL);
	if (NULL == hwndGraphics)
	{
		wstring errorMessage(_T("Failed to find hwndGraphics window"));
		printError(errorMessage);
		return;
	}

	TAB activeTab = getActiveTab(hwndGraphics);

	WINDOWINFO windowInfo;
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwndGraphics, &windowInfo);
//	const int graphicsTabCount = getGraphicsTabCount(hwndGraphics);
	const int graphicsTabCount = 1;
	int tabWidth = (windowInfo.rcClient.right - windowInfo.rcClient.left) / graphicsTabCount;
//	tabWidth -= 10;
	int deltaX = 10;
	int x = 0;
	int y = 18;
	if (forward)
	{
		currentGraphicIndex++;
		if (currentGraphicIndex > GRAPHICS_TAB_COUNT)
		{
			currentGraphicIndex = GRAPHICS_TAB_COUNT;
		}
		x = activeTab.right + deltaX;
/** /
		if (755 == activeTab.right)
		{
			POINT pt;
			pt.x = windowInfo.rcClient.right - 10;
			pt.y = (windowInfo.rcClient.bottom - windowInfo.rcClient.top) / 2;
// 			ClientToScreen(hwndGraphics, &pt);
// 			SetCursorPos(pt.x, pt.y);
			LPARAM lParam = MAKELPARAM(pt.x, pt.y);
			SendMessage(hwndGraphics, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
			SendMessage(hwndGraphics, WM_LBUTTONUP, MK_LBUTTON, lParam);
		}
/**/
	}
	else
	{
		currentGraphicIndex--;
		if (currentGraphicIndex < 0)
		{
			currentGraphicIndex = 0;
		}
		x = activeTab.left - deltaX;
	}
	if ((-1 == activeTab.right) || (-1 == activeTab.left))
	{
		x = 10;
	}
//	int x = (tabWidth / 2 ) + tabWidth * currentGraphicIndex;
//	int y = (windowInfo.rcClient.bottom - windowInfo.rcClient.top) / 2;
	SendMessage(hwndGraphics, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x, y));
	SendMessage(hwndGraphics, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(x, y));
}

void scrollTabs(const bool forward)
{
	HWND hwndMT = FindWindow(META_TRADER_CLASS_NAME.c_str(), NULL);
	if (NULL == hwndMT)
	{
		wstring errorMessage(_T("Failed to find hwndMT window"));
		printError(errorMessage);
		return;
	}
	HWND hwndGraphics = FindWindowEx(hwndMT, NULL, _T("Afx:400000:b:10011:0:0"), NULL);
	if (NULL == hwndGraphics)
	{
		wstring errorMessage(_T("Failed to find hwndGraphics window"));
		printError(errorMessage);
		return;
	}
	WINDOWINFO windowInfo;
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwndGraphics, &windowInfo);
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
// 	ClientToScreen(hwndGraphics, &pt);
// 	SetCursorPos(pt.x, pt.y);
	LPARAM lParam = MAKELPARAM(pt.x, pt.y);
	SendMessage(hwndGraphics, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
	SendMessage(hwndGraphics, WM_LBUTTONUP, MK_LBUTTON, lParam);
}

TAB getActiveTab(HWND hWnd)
{
	WINDOWINFO windowInfo;
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hWnd, &windowInfo);

	HDC hDc = GetDC(NULL);

	const COLORREF ACTIVE_TAB_COLORREF = 16777215;

	TAB tab;
	tab.left = -1;
	tab.right = -1;

	for (int x = windowInfo.rcClient.left; x <= windowInfo.rcClient.right; x++)
	{
		POINT pt;
		pt.x = x;
		pt.y = 17;
		ClientToScreen(hWnd, &pt);
		COLORREF colorRef = GetPixel(hDc, pt.x, pt.y);
		if ((ACTIVE_TAB_COLORREF == colorRef) && (-1 == tab.left))
		{
//			SetCursorPos(pt.x, pt.y);
			tab.left = x;
		}
		if ((ACTIVE_TAB_COLORREF != colorRef) && (-1 != tab.left))
		{
//			SetCursorPos(pt.x, pt.y);
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

const int getGraphicsTabCount(HWND hWnd)
{
	return getTokenCount(getWindowTextOCR(hWnd), _T("| :"));
}

static CString errorMessage;

const TCHAR* formatE(const TCHAR* m, const char* fn)
{
	errorMessage.Format(m, fn);
	return errorMessage;
}

bool AErrorIf(TextractSuccess code)
{
	if (code < 0)
	{
		const TCHAR* message = _T("<unknown>");
		switch(code)
		{
			case tsReject: 
				message = _T("User rejected the operation");
				break;
			case tsBadArgs: 
				message = _T("Incorrect argument");
				break;
			case tsBadBitmap: 
				message = _T("Incorrect BMP file\n") 
					  _T("Only 1, 4, 8, 16, 24, 32 bpp Windows BMP files are supported");
				break;
			case tsOutOfWindow: 
				message = _T("Rectangle is out of window");
				break;
			case tsIniNotFound: 
				message = formatE(_T("File %s not found"), TextractIniFileName());
				break;
			case tsBaseNotFound: 
				message = formatE(_T("Font pattern base file %s not found\n\n")
					  _T("Click \"Build font pattern database...\" button for building it"), 
					  TextractBaseFileName());
				break;
			case tsBitmapNotFound: 
				message = formatE(_T("Bitmap file %s not found"), 
					  TextractBitmapFileName());
				break;
			case tsFakeResNotFound: 
				message = formatE(_T("File %s not found"), TextractFakeResFileName());
				break;
			case tsInitFailed: 
				message = _T("Initialization failed");
				break;
			case tsTermFailed: 
				message = _T("Termination failed");
				break;
			case tsCrash: 
				message = _T("Internal error");
				break;
// 			case keFormat: message = formatE("Bad file format\nFile %s", fileName); break;
// 			case keNoAccess: message = formatE("Access  denied.\nFile %s", fileName); break;
		}
		wstring errorMessage(_T("OCR SDK error "));
		errorMessage += longToString(code);
		errorMessage += _T(":\n\n");
		errorMessage += message;
		AfxMessageBox(errorMessage.c_str(), MB_OK | MB_ICONSTOP);
		return false;
	}
	else
	{
		return true;
	}
}

void initTextract(void)
{
	AErrorIf(TextractInit());
}

void termTextract(void)
{
	AErrorIf(TextractTerm());
}

const CString getWindowTextOCR(HWND hWnd)
{
	CString windowText;
	TextractDestFormat format;
	format = dfText;
	TextractSource src;
	src.Wnd(hWnd);
	TextractDest dest;
	if (AErrorIf(Textract(src, dest, format)))
	{
		CString s((LPCSTR) dest.Area, dest.AreaSize);
		windowText = s;
	}
	AErrorIf(TextractDestFree(dest));
	return windowText;
}

const wstring getWindowText(HWND hWnd)
{
	int cTxtLen = GetWindowTextLength(hWnd);
	LPTSTR pszMem = (LPTSTR) VirtualAlloc((LPVOID) NULL, (DWORD) (cTxtLen + 1),
		MEM_COMMIT, PAGE_READWRITE);
	GetWindowText(hWnd, pszMem, cTxtLen + 1);
	wstring ws(pszMem);
	VirtualFree(pszMem, 0, MEM_RELEASE);
	return ws;
}

const int getButtonIndex(const bool forForward)
{
	int buttonIndex = UNKNOWN_BUTTON_INDEX;
	HWND hwndPeriod = getHwndPeriod();
	if (NULL == hwndPeriod)
	{
		wstring errorMessage(_T("Failed to getHwndPeriod"));
		printError(errorMessage);
		return buttonIndex;
	}
	int checkedButtonIndex = UNKNOWN_BUTTON_INDEX;
	LRESULT buttonCount = SendMessage(hwndPeriod, TB_BUTTONCOUNT, 0, 0);
	for (int i = 0; i < buttonCount; i++)
	{
		if (SendMessage(hwndPeriod, TB_ISBUTTONCHECKED,
						getButtonIdCommand(hwndPeriod, i), 0))
		{
			checkedButtonIndex = i;
		}
	}
	for (int i = 0; i < static_cast<int>(periods.size()); i++)
	{
		int& value = periods[i];
		if (value == checkedButtonIndex)
		{
			return checkedButtonIndex;
		}
	}
	if (forForward)
	{
		for (int i = 0; i < static_cast<int>(periods.size()); i++)
		{
			int& value = periods[i];
			if (value < checkedButtonIndex)
			{
				buttonIndex = value;
			}
		}
	}
	else
	{
		for (int i = static_cast<int>(periods.size()) - 1; i >= 0; i--)
		{
			int& value = periods[i];
			if (value > checkedButtonIndex)
			{
				buttonIndex = value;
			}
		}
	}
	return buttonIndex;
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
	lpRemoteBuffer = VirtualAllocEx(hTaskProc, NULL, sizeof(TBBUTTON),
		MEM_COMMIT, PAGE_READWRITE);
	if (!SendMessage(hWnd, TB_GETBUTTON, buttonIndex, (LPARAM) lpRemoteBuffer))
	{
		wstring errorMessage(_T("Failed to TB_GETBUTTON"));
		printError(errorMessage);
		return -1;
	}
	if (!ReadProcessMemory(hTaskProc, lpRemoteBuffer, &Button, sizeof(TBBUTTON),
		&lpNumberOfBytesRead))
	{
		wstring errorMessage(_T("Failed to ReadProcessMemory"));
		printError(errorMessage);
		return -1;
	}
	VirtualFree(lpRemoteBuffer, 0, MEM_RELEASE);
	CloseHandle(hTaskProc);
	return Button.idCommand;
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

const int getTokenCount(const CString& srcString, const CString& tokens)
{
	int tokenCount = 0;
	int iStart = 0;
	CString resToken;
	do 
	{
		resToken = srcString.Tokenize(tokens, iStart);
		if (-1 != iStart)
		{
			tokenCount++;
		}
	} while (resToken != "");
	return tokenCount - 1;
}
