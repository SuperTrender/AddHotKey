// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ADDHOTKEYHOOK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ADDHOTKEYHOOK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ADDHOTKEYHOOK_EXPORTS
#define ADDHOTKEYHOOK_API __declspec(dllexport)
#else
#define ADDHOTKEYHOOK_API __declspec(dllimport)
#endif

// This class is exported from the AddHotKeyHook.dll
class ADDHOTKEYHOOK_API CAddHotKeyHook {
public:
	CAddHotKeyHook(void);
	// TODO: add your methods here.
};

extern ADDHOTKEYHOOK_API int nAddHotKeyHook;

ADDHOTKEYHOOK_API int fnAddHotKeyHook(void);

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
