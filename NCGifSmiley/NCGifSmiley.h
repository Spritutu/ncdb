// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� NCGIFSMILEY_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// NCGIFSMILEY_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef NCGIFSMILEY_EXPORTS
#define NCGIFSMILEY_API __declspec(dllexport)
#else
#define NCGIFSMILEY_API __declspec(dllimport)
#endif

// �����Ǵ� NCGifSmiley.dll ������
class NCGIFSMILEY_API CNCGifSmiley {
public:
	CNCGifSmiley(void);
	// TODO:  �ڴ�������ķ�����
};

extern NCGIFSMILEY_API int nNCGifSmiley;

NCGIFSMILEY_API int fnNCGifSmiley(void);
NCGIFSMILEY_API void CShowGifWindow();
