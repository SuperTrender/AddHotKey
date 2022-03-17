#pragma once

#define DllExport extern "C" __declspec(dllexport)
//#define DllExport __declspec(dllexport)

//DllExport LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProcMetaTrader(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProcQuik(int nCode, WPARAM wParam, LPARAM lParam);

/** /
int periods[] = {H1, D1, W1, MN};
const int getPeriodIndex(const int period);
int currentPeriodIndex = getPeriodIndex(H1);
//	currentPeriodIndex = getPeriodIndex(H1);
//	currentPeriodIndex = periodCycler.getIndex(H1);
currentPeriodIndex++;

if (currentPeriodIndex >= _countof(periods))
{
currentPeriodIndex = 0;
}
changePeriod(periods[currentPeriodIndex]);

currentPeriodIndex--;
if (currentPeriodIndex < 0)
{
currentPeriodIndex = _countof(periods) - 1;
}
changePeriod(periods[currentPeriodIndex]);

const int getPeriodIndex(const int period)
{
	for (int i = 0; i < _countof(periods); i++)
	{
		if (periods[i] == period)
		{
			return i;
		}
	}
	return -1;
}
/**/
