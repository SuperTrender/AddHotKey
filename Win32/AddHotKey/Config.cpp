#include "stdafx.h"
#include "Config.h"
#include "Util.h"

using namespace std;

Config::Config()
{
	initProperties();
	initTimeframesMap();
	init();
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

void Config::initTimeframesMap(void)
{
	timeframesMap[_T("H1")] = H1;
	timeframesMap[_T("H4")] = H4;
	timeframesMap[_T("Daily")] = D1;
	timeframesMap[_T("Weekly")] = W1;
	timeframesMap[_T("Monthly")] = MN;
}
	
void Config::init(void)
{
	if (getWithMetaTrader() == _T("yes"))
	{
		mtHwnd = getHwndMT(getMetaTraderClassName());
		standardHwnd = getHwndStandard(mtHwnd, getStandardMetaTrader());
		chartsHwnd = getHwndCharts(standardHwnd, getChartsMetaTrader());
		timeframesHwnd = getHwndTimeframes(standardHwnd, getTimeframesMetaTrader());
		tabsHwnd = getHwndTabs(mtHwnd, getTabsClassName());
	}
	if (getWithQuik() == _T("yes"))
	{
		quikHwnd = getHwndQuik(getQuikClassName());
		intervalHmenu = getHmenuInterval(quikHwnd);
	}
}
