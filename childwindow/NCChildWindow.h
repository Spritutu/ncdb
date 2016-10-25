// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� NCCHILDWINDOW_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// NCCHILDWINDOW_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef NCCHILDWINDOW_EXPORTS
#define NCCHILDWINDOW_API __declspec(dllexport)
#else
#define NCCHILDWINDOW_API __declspec(dllimport)
#endif

// �����Ǵ� NCChildWindow.dll ������
class NCCHILDWINDOW_API CNCChildWindow {
public:
	CNCChildWindow(void);
	// TODO:  �ڴ�������ķ�����
	
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
