#include "stdafx.h"
#include "Config.h"
#include "Util.h"

using namespace std;

Config::Config()
{
	initProperties();
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
	const wstring propertiesFullFileName = getProcessDir(PROCESS_NAME)
		+ PROPERTIES_FILE_NAME;
	if (!properties.parseProperties(propertiesFullFileName))
	{
		wstring errorMessage(_T("Failed to read configuration file "));
		errorMessage += propertiesFullFileName;
		MessageBox(NULL, errorMessage.c_str(), NULL, MB_OK | MB_ICONERROR);
		return;
	}
}
