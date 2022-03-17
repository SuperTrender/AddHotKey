// AddHotKeyHook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "..\AddHotKey\AddHotKey.h"
#include "AddHotKeyHook.h"
#include "Cycler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

// Создаём глобальную переменную для объявления глобального хука.
HHOOK hHookKeyboard = NULL;
Cycler<int> periodCycler(initPeriods());
Cycler<wstring> templateCycler(initTemplates());
Cycler<wstring> templateCyclerFX(initTemplatesFX());
bool textractInited = false;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
	UNREFERENCED_PARAMETER(envp);

	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
	}

	return nRetCode;
}

WORD isBitSet(LPARAM lParam, WORD bit)
{
	return (HIWORD(lParam) & bit);
}

bool isBitSet_(LPARAM lParam, int bit)
{
	return (lParam & (1 << bit)) ? true : false;
}

// Функция обработки всех событий от клавиатуры.
//DllExport LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(hHookKeyboard, nCode, wParam, lParam);
	}

	//	if ((lParam & (1<<30)) && (HC_ACTION == nCode)) // Если кнопка была нажата. (Другими словами событие: 'WM_KEYUP')
	if (isBitSet(lParam, KF_ALTDOWN) && !isBitSet(lParam, KF_REPEAT)
		&& (HC_ACTION == nCode)) // Если кнопка была нажата. (Другими словами событие: 'WM_KEYUP')
	{
		if (!textractInited)
		{
			initTextract();
			textractInited = true;
		} 
		if (wParam == VK_F1)
		{
			changePeriod(H1);
		}
		else if (wParam == VK_F2)
		{
			changePeriod(D1);
		}
		else if (wParam == VK_F3)
		{
			changePeriod(W1);
		}
		else if (wParam == VK_F5)
		{
			changePeriod(MN);
		}
		else if (wParam == VK_UP)
		{
			periodCycler.setCurrentIndex(getButtonIndex(true));
			changePeriod(periodCycler.forward());
		}
		else if (wParam == VK_DOWN)
		{
			periodCycler.setCurrentIndex(getButtonIndex(false));
			changePeriod(periodCycler.backward());
		}
		else if (wParam == VK_LEFT)
		{
			changeTemplate(templateCycler.forward());
		}
		else if (wParam == VK_RIGHT)
		{
			changeTemplate(templateCyclerFX.backward());
		}
		else if (wParam == VK_PRIOR)
		{
			changeGraphic(true);
		}
		else if (wParam == VK_NEXT)
		{
			changeGraphic(false);
		}
		else if (wParam == VK_HOME)
		{
			scrollTabs(true);
		}
		else if (wParam == VK_END)
		{
			scrollTabs(false);
		}
	}
	LRESULT retVal = CallNextHookEx(hHookKeyboard, nCode, wParam, lParam); // Вызываем слудующее системное сообщение из очереди для обработки.
	return retVal; // Возвращаем результат.
}
