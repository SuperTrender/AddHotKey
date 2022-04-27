#include "stdafx.h"
#include "Config.h"
#include "Logger.h"
#include "Util.h"

using namespace std;

Config::Config()
{
	initProperties();
	initTimeframes();
	initTimeframesQuik();
	initTimeframesMap();
	initTemplates();
	initTemplatesFX();
	init();
	initAutoScrollButtonIdCommand();
}

Config::~Config()
{
}

Config& Config::getInstance()
{
	static Config instance;
	return instance;
}

void Config::initProperties(void)
{
	const wstring propertiesFullFileName = getProcessDir(PROCESS_NAME) + PROPERTIES_FILE_NAME;
	if (!properties.parseProperties(propertiesFullFileName))
	{
		wstring errorMessage(_T("Failed to read configuration file "));
		errorMessage += propertiesFullFileName;
		MessageBox(NULL, errorMessage.c_str(), NULL, MB_OK | MB_ICONERROR);
		return;
	}
}

void Config::initTimeframes(void)
{
	timeframes.push_back(H1);
	timeframes.push_back(H4);
	timeframes.push_back(D1);
	timeframes.push_back(W1);
	timeframes.push_back(MN);
}

void Config::initTimeframesQuik(void)
{
	timeframesQuik.push_back(Hourly);
	timeframesQuik.push_back(Daily);
	timeframesQuik.push_back(Weekly);
	timeframesQuik.push_back(Monthly);
}

void Config::initTimeframesMap(void)
{
	timeframesMap[_T("H1")] = H1;
	timeframesMap[_T("H4")] = H4;
	timeframesMap[_T("Daily")] = D1;
	timeframesMap[_T("Weekly")] = W1;
	timeframesMap[_T("Monthly")] = MN;
}
	
void Config::initTemplates(void)
{
	templates = split(getTemplatesLeft(), SPACE);
}

void Config::initTemplatesFX(void)
{
	templatesFX = split(getTemplatesRight(), SPACE);
}

void Config::init(void)
{
	if (getWithMetaTrader() == _T("yes"))
	{
		mtHwnd = getHwndMT(getMetaTraderClassName());
		standardHwnd = getHwndStandard(mtHwnd, getStandardMetaTrader());
		chartsHwnd = getHwndCharts(standardHwnd, getChartsMetaTrader());
		timeframesHwnd = getHwndTimeframes(standardHwnd, getTimeframesMetaTrader());
		//tabsHwnd = getHwndTabs(mtHwnd, getTabsClassName());
		tabsHwnd = getHwndTabs(mtHwnd, findTabsClassName(mtHwnd));
	}
	if (getWithQuik() == _T("yes"))
	{
		quikHwnd = getHwndQuik(getQuikClassName());
		intervalHmenu = getHmenuInterval(quikHwnd);
	}
}

void Config::initAutoScrollButtonIdCommand(void)
{
	autoScrollButtonIdCommand = getButtonIdCommand(chartsHwnd, AUTO_SCROLL_BUTTON_INDEX);
}

const HWND Config::getHwndMain(const wstring& className)
{
	HWND hwndMain = FindWindow(className.c_str(), NULL);
	if (NULL == hwndMain)
	{
		wstring errorMessage(_T("Failed to find main window with class name "));
		errorMessage += className;
		printError(errorMessage);
		return NULL;
	}
	return hwndMain;
}

const HWND Config::getHwndMT(const wstring& className)
{
	HWND hwndMT = getHwndMain(className);
	if (NULL == hwndMT)
	{
		wstring errorMessage(_T("Failed to find hwndMT window"));
		printError(errorMessage);
		return NULL;
	}
	return hwndMT;
}

const HWND Config::getHwndStandard(HWND hwndMT, const wstring& standardMetaTrader)
{
	HWND hwndStandard = FindWindowEx(hwndMT, NULL, NULL, standardMetaTrader.c_str());
	if (NULL == hwndStandard)
	{
		wstring errorMessage(_T("Failed to find hwndStandard window"));
		printError(errorMessage);
		return NULL;
	}
	return hwndStandard;
}

const HWND Config::getHwndCharts(HWND hwndStandard, const wstring& chartsMetaTrader)
{
	HWND hwndCharts = FindWindowEx(hwndStandard, NULL, NULL, chartsMetaTrader.c_str());
	if (NULL == hwndCharts)
	{
		wstring errorMessage(_T("Failed to find hwndCharts window"));
		printError(errorMessage);
		return NULL;
	}
	return hwndCharts;
}

const HWND Config::getHwndTimeframes(HWND hwndStandard, const wstring& timeframesMetaTrader)
{
	HWND hwndTimeframes = FindWindowEx(hwndStandard, NULL, NULL, timeframesMetaTrader.c_str());
	if (NULL == hwndTimeframes)
	{
		wstring errorMessage(_T("Failed to find hwndTimeframes window"));
		printError(errorMessage);
		return NULL;
	}
	return hwndTimeframes;
}

const HWND Config::getHwndTabs(HWND hwndMT, const wstring& tabsClassName)
{
	HWND hwndTabs = FindWindowEx(hwndMT, NULL, tabsClassName.c_str(), NULL);
	if (NULL == hwndTabs)
	{
		wstring errorMessage(_T("Failed to find hwndTabs window"));
		printError(errorMessage);
		return NULL;
	}
	return hwndTabs;
}

const HWND Config::getHwndQuik(const wstring& className)
{
	HWND hwndQuik = getHwndMain(className);
	if (NULL == hwndQuik)
	{
		wstring errorMessage(_T("Failed to find hwndQuik window"));
		printError(errorMessage);
		return NULL;
	}
	return hwndQuik;
}

const HMENU Config::getHmenuInterval(HWND hwndQuik)
{
	HMENU hmenuBar = GetMenu(hwndQuik);
	if (NULL == hmenuBar)
	{
		wstring errorMessage(_T("Failed to find hmenuBar"));
		printError(errorMessage);
		return NULL;
	}
	HMENU hmenuDataExport = GetSubMenu(hmenuBar, DATA_EXPORT_MENU_POSITION_QUIK);
	if (NULL == hmenuDataExport)
	{
		wstring errorMessage(_T("Failed to find hmenuDataExport"));
		printError(errorMessage);
		return NULL;
	}
	HMENU hmenuCharts = GetSubMenu(hmenuDataExport, CHARTS_MENU_POSITION_QUIK);
	if (NULL == hmenuCharts)
	{
		wstring errorMessage(_T("Failed to find hmenuCharts"));
		printError(errorMessage);
		return NULL;
	}
	HMENU hmenuInterval = GetSubMenu(hmenuCharts, INTERVAL_MENU_POSITION_QUIK);
	if (NULL == hmenuInterval)
	{
		wstring errorMessage(_T("Failed to find hmenuInterval"));
		printError(errorMessage);
		return NULL;
	}
	return hmenuInterval;
}
