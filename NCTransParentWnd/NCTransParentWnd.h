// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� NCTRANSPARENTWND_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// NCTRANSPARENTWND_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef NCTRANSPARENTWND_EXPORTS
#define NCTRANSPARENTWND_API __declspec(dllexport)
#else
#define NCTRANSPARENTWND_API __declspec(dllimport)
#endif

NCTRANSPARENTWND_API void CShowTransParentWindow(HWND pWnd);