#pragma once

#define DllExport extern "C" __declspec(dllexport)
//#define DllExport __declspec(dllexport)

//DllExport LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProcMetaTrader(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProcQuik(int nCode, WPARAM wParam, LPARAM lParam);
