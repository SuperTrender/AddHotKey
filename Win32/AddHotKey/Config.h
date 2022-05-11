#pragma once

#include "AddHotKey.h"
#include "Properties.h"

#define PROCESS_NAME _T("AddHotKey.exe")
#define PROPERTIES_FILE_NAME _T("AddHotKey.ini")
#define YES _T("yes")
#define WITH_META_TRADER_PROPERTY_NAME _T("with_meta_trader")
#define META_TRADER_CLASS_NAME_PROPERTY_NAME _T("meta_trader_class_name")
#define STANDARD_META_TRADER_PROPERTY_NAME _T("standard_meta_trader")
#define CHARTS_META_TRADER_PROPERTY_NAME _T("charts_meta_trader")
#define TIMEFRAMES_META_TRADER_PROPERTY_NAME _T("timeframes_meta_trader")
#define FIND_TABS_PROPERTY_NAME _T("find_tabs")
#define TABS_CLASS_NAME_PREFIX_PROPERTY_NAME _T("tabs_class_name_prefix")
#define TABS_CLASS_NAME_PROPERTY_NAME _T("tabs_class_name")
#define TEMPLATES_LEFT_PROPERTY_NAME _T("templates_left")
#define TEMPLATES_RIGHT_PROPERTY_NAME _T("templates_right")
#define WITH_QUIK_PROPERTY_NAME _T("with_quik")
#define QUIK_CLASS_NAME_PROPERTY_NAME _T("quik_class_name")

#define MAX_CLASS_NAME 256

enum Timeframes { H1 = 4, H4 = 5, D1 = 6, W1 = 7, MN = 8 };
enum TimeframesQuik { Hourly = 11, Daily = 14, Weekly = 15, Monthly = 16 };

const COLORREF ACTIVE_TAB_COLORREF = 16777215;
const int CHARTS_MENU_POSITION = 4;
const int TEMPLATE_MENU_POSITION = 9;
const int AUTO_SCROLL_BUTTON_INDEX = 8;
const int UNKNOWN_INDEX = -1;
const int UNKNOWN_BUTTON_INDEX = -1;
const int UNKNOWN_MENU_ITEM_INDEX = -1;
const int UNKNOWN_MENU_ID_COMMAND = -1;
const int CHARTS_TAB_COUNT = 9;
const int DATA_EXPORT_MENU_POSITION_QUIK = 1;
const int CHARTS_MENU_POSITION_QUIK = 2;
const int INTERVAL_MENU_POSITION_QUIK = 15;

typedef std::map<std::wstring, int> TimeframesMap;
typedef std::map<int, int> TimeframesButtonIdCommandMap;

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
    const std::wstring Config::getFindTabs(void) const
    {
        return properties.getProperty(FIND_TABS_PROPERTY_NAME);
    }
    const std::wstring Config::getTabsClassNamePrefix(void) const
    {
        return properties.getProperty(TABS_CLASS_NAME_PREFIX_PROPERTY_NAME);
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
    const std::vector<int> Config::getTimeframes(void) const
    {
        return timeframes;
    }
    const std::vector<int> Config::getTimeframesQuik(void) const
    {
        return timeframesQuik;
    }
    const TimeframesMap Config::getTimeframesMap(void) const
    {
        return timeframesMap;
    }
    const TimeframesButtonIdCommandMap Config::getTimeframesButtonIdCommandMap(void) const
    {
        return timeframesButtonIdCommandMap;
    }
    const std::vector<std::wstring> Config::getTemplates(void) const
    {
        return templates;
    }
    const std::vector<std::wstring> Config::getTemplatesFX(void) const
    {
        return templatesFX;
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
    const int Config::getAutoScrollButtonIdCommand(void) const
    {
        return autoScrollButtonIdCommand;
    }
private:
    Config();
    ~Config();
    Config(const Config&);            // intentionally undefined
    Config& operator=(const Config&); // intentionally undefined
    Properties properties;
    std::vector<int> timeframes;
    std::vector<int> timeframesQuik;
    TimeframesMap timeframesMap;
    TimeframesButtonIdCommandMap timeframesButtonIdCommandMap;
    std::vector<std::wstring> templates;
    std::vector<std::wstring> templatesFX;
    HWND mtHwnd;
    HWND standardHwnd;
    HWND chartsHwnd;
    HWND timeframesHwnd;
    HWND tabsHwnd;
    HWND quikHwnd;
    HMENU intervalHmenu;
    int autoScrollButtonIdCommand;
    void initProperties(void);
    void initTimeframes(void);
    void initTimeframesQuik(void);
    void initTimeframesMap(void);
    void initTimeframesButtonIdCommandMap(void);
    void initTemplates(void);
    void initTemplatesFX(void);
    void init(void);
    void initAutoScrollButtonIdCommand(void);
    const HWND getHwndMain(const std::wstring& className);
    const HWND getHwndMT(const std::wstring& className);
    const HWND getHwndStandard(HWND hwndMT, const std::wstring& standardMetaTrader);
    const HWND getHwndCharts(HWND hwndStandard, const std::wstring& chartsMetaTrader);
    const HWND getHwndTimeframes(HWND hwndStandard, const std::wstring& timeframesMetaTrader);
    const HWND getHwndTabs(HWND hwndMT, const std::wstring& tabsClassName);
    const HWND getHwndQuik(const std::wstring& className);
    const HMENU getHmenuInterval(HWND hwndQuik);
    const int getButtonIdCommand(HWND hWnd, const int buttonIndex);
};
