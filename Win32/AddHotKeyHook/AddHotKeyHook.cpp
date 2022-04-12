// AddHotKeyHook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "..\AddHotKey\AddHotKey.h"
#include "AddHotKeyHook.h"
#include "Cycler.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

#define VK_A 0x41
#define VK_M 0x4D

using namespace std;

// Создаём глобальную переменную для объявления глобального хука.
HHOOK hHookKeyboard = NULL;
Cycler<int> timeframesCycler(initTimeframes());
Cycler<wstring> templateCycler(initTemplates());
Cycler<wstring> templateCyclerFX(initTemplatesFX());
Cycler<int> timeframesCyclerQuik(initTimeframesQuik());

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(ul_reason_for_call);
	UNREFERENCED_PARAMETER(lpReserved);
	return TRUE;
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
LRESULT CALLBACK KeyboardProcMetaTrader(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(hHookKeyboard, nCode, wParam, lParam);
	}
//	if ((lParam & (1<<30)) && (HC_ACTION == nCode)) // Если кнопка была нажата. (Другими словами событие: 'WM_KEYUP')
	if (isBitSet(lParam, KF_ALTDOWN) && !isBitSet(lParam, KF_REPEAT)
		&& (HC_ACTION == nCode)) // Если кнопка была нажата. (Другими словами событие: 'WM_KEYUP')
	{
		if (wParam == VK_F1)
		{
			changeTimeframe(H1);
		}
		if (wParam == VK_F2)
		{
			changeTimeframe(H4);
		}
		else if (wParam == VK_F3)
		{
			changeTimeframe(D1);
		}
		else if (wParam == VK_F5)
		{
			changeTimeframe(W1);
		}
		else if (wParam == VK_F6)
		{
			changeTimeframe(MN);
		}
		else if (wParam == VK_UP)
		{
			timeframesCycler.setCurrentIndex(getButtonIndex(true));
			changeTimeframe(timeframesCycler.forward());
		}
		else if (wParam == VK_DOWN)
		{
			timeframesCycler.setCurrentIndex(getButtonIndex(false));
			changeTimeframe(timeframesCycler.backward());
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
			changeChart(true);
		}
		else if (wParam == VK_NEXT)
		{
			changeChart(false);
		}
		else if (wParam == VK_HOME)
		{
			scrollTabs(true);
		}
		else if (wParam == VK_END)
		{
			scrollTabs(false);
		}
		else if (wParam == VK_INSERT)
		{
			scrollTabs(true);
			changeChart(true);
		}
		else if (wParam == VK_DELETE)
		{
			scrollTabs(false);
			changeChart(false);
		}
		else if (wParam == VK_A)
		{
			toggleAutoScroll();
		}
    }
	LRESULT retVal = CallNextHookEx(hHookKeyboard, nCode, wParam, lParam); // Вызываем слудующее системное сообщение из очереди для обработки.
	return retVal; // Возвращаем результат.
}

LRESULT CALLBACK KeyboardProcQuik(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(hHookKeyboard, nCode, wParam, lParam);
	}
	if (isBitSet(lParam, KF_ALTDOWN) && !isBitSet(lParam, KF_REPEAT)
		&& (HC_ACTION == nCode))
	{
		if (wParam == VK_F2)
		{
			changeTimeframeQuik(Daily);
		}
		else if (wParam == VK_F3)
		{
			changeTimeframeQuik(Weekly);
		}
		else if (wParam == VK_F5)
		{
			changeTimeframeQuik(Monthly);
		}
		else if (wParam == VK_UP)
		{
			timeframesCyclerQuik.setCurrentIndex(getMenuItemIndex(true));
			changeTimeframeQuik(timeframesCyclerQuik.forward());
		}
		else if (wParam == VK_DOWN)
		{
			timeframesCyclerQuik.setCurrentIndex(getMenuItemIndex(false));
			changeTimeframeQuik(timeframesCyclerQuik.backward());
		}
		else if (wParam == VK_M)
		{
			minimizeActiveChildWindowQuik();
		}
	}
	return CallNextHookEx(hHookKeyboard, nCode, wParam, lParam);
}

#ifdef _MANAGED
#pragma managed(pop)
#endif
