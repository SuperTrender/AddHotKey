// AddHotKeyGUI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "AddHotKey.h"
#include "Config.h"
#include "AddHotKeyGUI.h"
#include "..\AddHotKeyHook\Cycler.h"

#define MAX_LOADSTRING 100

using namespace std;

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
vector<HHOOK> hHooks;
/** /
bool runTest = true;
/**/
/**/
bool runTest = false;
/**/

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;
    HACCEL hAccelTable;

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_ADDHOTKEY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ADDHOTKEY));

    if (!runTest)
    {
        hHooks = addHooks();
    }
    else
    {
        test();
    }

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    if (!runTest)
    {
        removeHooks(hHooks);
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex{};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style            = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc      = WndProc;
    wcex.cbClsExtra       = 0;
    wcex.cbWndExtra       = 0;
    wcex.hInstance        = hInstance;
    wcex.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ADDHOTKEY));
    wcex.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName     = MAKEINTRESOURCE(IDC_ADDHOTKEY);
    wcex.lpszClassName    = szWindowClass;
    wcex.hIconSm          = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    UNREFERENCED_PARAMETER(nCmdShow);
    HWND hWnd;

    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT,
        0, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

//   ShowWindow(hWnd, nCmdShow);
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND    - process the application menu
//  WM_PAINT      - Paint the main window
//  WM_DESTROY    - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code here...
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


/** /
int timeframes[] = { H1, D1, W1, MN };
const int getTimeframeIndex(const int timeframe);
/**/

void test(void)
{
/**/
    addHooks();
/**/
/** /
    toggleAutoScroll();
/**/
/** /
    scrollTabs(true);
    scrollTabs(false);
/**/
/** /
    changeChart(true);
/**/
/** /
    Cycler<int> timeframesCycler(Config::getInstance().getTimeframes());
    timeframesCycler.setCurrentIndex(getButtonIndex(true));
    changeTimeframe(timeframesCycler.forward());
//     timeframesCycler.setCurrentIndex(getButtonIndex(false));
//     changeTimeframe(timeframesCycler.backward());
/**/
/** /
    changeTemplate(_T("ADX"));
/**/
/** /
    changeTimeframe(0);
/**/
/** /
    initTimeframes();
    int buttonIndex = getButtonIndex(true);
    buttonIndex += 0;
/**/
/** /
    changeTimeframeQuik(Daily);
    changeTimeframeQuik(Weekly);
/**/
/** /
    initTimeframesQuik();
    getMenuItemIndex(true);
/**/

/** /
int currentTimeframeIndex = getTimeframeIndex(H1);
//    currentTimeframeIndex = getTimeframeIndex(H1);
//    currentTimeframeIndex = timeframesCycler.getIndex(H1);
currentTimeframeIndex++;

if (currentTimeframeIndex >= _countof(timeframes))
{
    currentTimeframeIndex = 0;
}
changeTimeframe(timeframes[currentTimeframeIndex]);

currentTimeframeIndex--;
if (currentTimeframeIndex < 0)
{
    currentTimeframeIndex = _countof(timeframes) - 1;
}
changeTimeframe(timeframes[currentTimeframeIndex]);
/**/
}

/** /
const int getTimeframeIndex(const int timeframe)
{
    for (int i = 0; i < _countof(timeframes); i++)
    {
        if (timeframes[i] == timeframe)
        {
            return i;
        }
    }
    return -1;
}
/**/
