// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 NCCHILDWINDOW_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// NCCHILDWINDOW_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef NCCHILDWINDOW_EXPORTS
#define NCCHILDWINDOW_API __declspec(dllexport)
#else
#define NCCHILDWINDOW_API __declspec(dllimport)
#endif

// 此类是从 NCChildWindow.dll 导出的
class NCCHILDWINDOW_API CNCChildWindow {
public:
	CNCChildWindow(void);
	// TODO:  在此添加您的方法。
	
};

extern NCCHILDWINDOW_API int nNCChildWindow;
struct TCFormFrame
{
	char* caption;
	char* path;
	HWND pWnd;
	char* formTag;
	bool isOnly;
	bool isShowModal;
};
struct TCFormSysButton
{
	bool sbClose;
	bool sbMax;
	bool sbMin;
	bool sbFeedback;
	bool sbOther;
};
typedef	int(*TCFormInitCallBack)(const HWND AFormHandle, const int AWidth, int AHeight);
NCCHILDWINDOW_API int fnNCChildWindow(void);
NCCHILDWINDOW_API HWND CShowChildWindow(TCFormFrame frame, TCFormSysButton button, TCFormInitCallBack callback);
