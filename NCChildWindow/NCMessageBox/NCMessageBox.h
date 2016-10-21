// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� NCMESSAGEBOX_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// NCMESSAGEBOX_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef NCMESSAGEBOX_EXPORTS
#define NCMESSAGEBOX_API __declspec(dllexport)
#else
#define NCMESSAGEBOX_API __declspec(dllimport)
#endif

//��ť����
#define BTN_OK                       0
#define BTN_OKCANCEL                 1
#define BTN_YESRETRYCANCEL           2

//ͼ�궨��
#define NCICON_WARN                  0
#define NCICON_ERROR                 1
#define NCICON_QUESTION              2
#define NCICON_HINT                  3
#define NCICON_CORRECT               4

//����ֵ
#define MSGID_CANCEL		         0
#define MSGID_OK	                 1
#define MSGID_RETRY                  2
NCMESSAGEBOX_API int NCMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = BTN_OK, UINT uIcon = NCICON_WARN, POINT pPosition = { 0, 0 });
