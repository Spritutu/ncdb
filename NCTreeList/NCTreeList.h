// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� NCTREELIST_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// NCTREELIST_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef NCTREELIST_EXPORTS
#define NCTREELIST_API __declspec(dllexport)
#else
#define NCTREELIST_API __declspec(dllimport)
#endif

// �����Ǵ� NCTreeList.dll ������

NCTREELIST_API void fnNCTreeList(void);
