#pragma once

#define DllExport extern "C" __declspec(dllexport)
//#define DllExport __declspec(dllexport)

//DllExport LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProcMetaTrader(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProcQuik(int nCode, WPARAM wParam, LPARAM lParam);

/** /
int timeframes[] = {H1, D1, W1, MN};
const int getTimeframeIndex(const int timeframe);
int currentTimeframeIndex = getTimeframeIndex(H1);
//	currentTimeframeIndex = getTimeframeIndex(H1);
//	currentTimeframeIndex = timeframesCycler.getIndex(H1);
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
