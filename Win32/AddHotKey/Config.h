#pragma once

#include "Properties.h"

#define PROCESS_NAME _T("AddHotKey.exe")
#define PROPERTIES_FILE_NAME _T("AddHotKey.ini")
#define META_TRADER_CLASS_NAME_PROPERTY_NAME _T("meta_trader_class_name")
#define QUIK_CLASS_NAME_PROPERTY_NAME _T("quik_class_name")
#define STANDARD_META_TRADER_PROPERTY_NAME _T("standard_meta_trader")
#define CHARTS_META_TRADER_PROPERTY_NAME _T("charts_meta_trader")
#define TIMEFRAMES_META_TRADER_PROPERTY_NAME _T("timeframes_meta_trader")
#define PERIOD_META_TRADER_PROPERTY_NAME _T("period_meta_trader")
#define TABS_CLASS_NAME_PROPERTY_NAME _T("tabs_class_name")
#define TEMPLATES_LEFT_PROPERTY_NAME _T("templates_left")
#define TEMPLATES_RIGHT_PROPERTY_NAME _T("templates_right")

// Singleton (http://en.wikipedia.org/wiki/Singleton_pattern#C.2B.2B)
class Config
{
public:
	static Config& getInstance();
	const std::wstring Config::getMetaTraderClassName(void) const
	{
		return properties.getProperty(META_TRADER_CLASS_NAME_PROPERTY_NAME);
	}
	const std::wstring Config::getQuikClassName(void) const
	{
		return properties.getProperty(QUIK_CLASS_NAME_PROPERTY_NAME);
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
	const std::wstring Config::getPeriodMetaTrader(void) const
	{
		return properties.getProperty(PERIOD_META_TRADER_PROPERTY_NAME);
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
private:
	Config();
	~Config();
	Config(const Config&);            // intentionally undefined
	Config& operator=(const Config&); // intentionally undefined
	Properties properties;
	void initProperties(void);
};
