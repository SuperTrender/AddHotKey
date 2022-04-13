#pragma once

#include "AddHotKey.h"
#include "Properties.h"

#define PROCESS_NAME _T("AddHotKey.exe")
#define PROPERTIES_FILE_NAME _T("AddHotKey.ini")
#define WITH_META_TRADER_PROPERTY_NAME _T("with_meta_trader")
#define META_TRADER_CLASS_NAME_PROPERTY_NAME _T("meta_trader_class_name")
#define STANDARD_META_TRADER_PROPERTY_NAME _T("standard_meta_trader")
#define CHARTS_META_TRADER_PROPERTY_NAME _T("charts_meta_trader")
#define TIMEFRAMES_META_TRADER_PROPERTY_NAME _T("timeframes_meta_trader")
#define TABS_CLASS_NAME_PROPERTY_NAME _T("tabs_class_name")
#define TEMPLATES_LEFT_PROPERTY_NAME _T("templates_left")
#define TEMPLATES_RIGHT_PROPERTY_NAME _T("templates_right")
#define WITH_QUIK_PROPERTY_NAME _T("with_quik")
#define QUIK_CLASS_NAME_PROPERTY_NAME _T("quik_class_name")

typedef std::map<std::wstring, int> TimeframesMap;

// Singleton (http://en.wikipedia.org/wiki/Singleton_pattern#C.2B.2B)
class Config
{
public:
	static Config& getInstance();
	const std::wstring Config::getWithMetaTrader(void) const
	{
		return properties.getProperty(WITH_META_TRADER_PROPERTY_NAME);
	}
	const std::wstring Config::getMetaTraderClassName(void) const
	{
		return properties.getProperty(META_TRADER_CLASS_NAME_PROPERTY_NAME);
	}
	const std::wstring Config::getStandardMetaTrader(void) const
	{
		return properties.getProperty(STANDARD_META_TRADER_PROPERTY_NAME);
	}
	const std::wstring Config::getChartsMetaTrader(void) const
	{
		return properties.getProperty(CHARTS_META_TRADER_PROPERTY_NAME);
	}
	const std::wstring Config::getTimeframesMetaTrader(void) const
	{
		return properties.getProperty(TIMEFRAMES_META_TRADER_PROPERTY_NAME);
	}
	const std::wstring Config::getTabsClassName(void) const
	{
		return properties.getProperty(TABS_CLASS_NAME_PROPERTY_NAME);
	}
	const std::wstring Config::getTemplatesLeft(void) const
	{
		return properties.getProperty(TEMPLATES_LEFT_PROPERTY_NAME);
	}
	const std::wstring Config::getTemplatesRight(void) const
	{
		return properties.getProperty(TEMPLATES_RIGHT_PROPERTY_NAME);
	}
	const std::wstring Config::getWithQuik(void) const
	{
		return properties.getProperty(WITH_QUIK_PROPERTY_NAME);
	}
	const std::wstring Config::getQuikClassName(void) const
	{
		return properties.getProperty(QUIK_CLASS_NAME_PROPERTY_NAME);
	}
	const TimeframesMap Config::getTimeframesMap(void) const
	{
		return timeframesMap;
	}
	const HWND Config::getMTHwnd(void) const
	{
		return mtHwnd;
	}
	const HWND Config::getStandardHwnd(void) const
	{
		return standardHwnd;
	}
	const HWND Config::getChartsHwnd(void) const
	{
		return chartsHwnd;
	}
	const HWND Config::getTimeframesHwnd(void) const
	{
		return timeframesHwnd;
	}
	const HWND Config::getTabsHwnd(void) const
	{
		return tabsHwnd;
	}
	const HWND Config::getQuikHwnd(void) const
	{
		return quikHwnd;
	}
	const HMENU Config::getIntervalHmenu(void) const
	{
		return intervalHmenu;
	}
private:
	Config();
	~Config();
	Config(const Config&);            // intentionally undefined
	Config& operator=(const Config&); // intentionally undefined
	Properties properties;
	TimeframesMap timeframesMap;
	HWND mtHwnd;
	HWND standardHwnd;
	HWND chartsHwnd;
	HWND timeframesHwnd;
	HWND tabsHwnd;
	HWND quikHwnd;
	HMENU intervalHmenu;
	void initProperties(void);
	void initTimeframesMap(void);
	void init(void);
};
