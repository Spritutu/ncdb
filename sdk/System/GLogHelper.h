#pragma once
class CGLogHelper
{
public:
	CGLogHelper(void);
	~CGLogHelper(void);
public:
	bool Init();
	bool SetInstallFailureWriter();
	virtual bool InitParam();
	/********************************************************************
		fun:	���г�ʼ����־����,
		param:	
		ret:	�ɹ���ʼ������true, ����ʼ���򷵻�false
	********************************************************************/
	virtual bool IsWriteLog();
	bool		m_bHasInit;		//��־�Ƿ��ѳ�ʼ��
};


void FuncFailureWriter(const char* data, int size);
void FuncFa33();
