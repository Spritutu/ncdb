#ifndef _PIPE_DATA_TYPE_SOURCE_H_
#define _PIPE_DATA_TYPE_SOURCE_H_

//*******************************************************
//����:����ָ�������ܵ��Ĺ����������Ͷ���

//******************************************************

#ifdef TEST_PIPE
	#define NUM_PIPE_WRITE_TIMEOUT		INFINITE
#else
	#define NUM_PIPE_WRITE_TIMEOUT		2000		//д������ʱʱ��

#endif
#define NUM_PIPE_TIMEOUT_CONNECT		10 * 1000		//���ӹܵ���ʱʱ��

typedef void (*m_pReadFun)(char *, int nSize);

//������ȡʧ��N������,�˳������߳�
//const int g_nReadErrorCount = 3;
//һ�ζ�д����ֽ���
//const int g_nReadDataMaxSize = MAX_PATH;


//���� PIPE ����
typedef	enum
{
	ENUM_PIPE_TYPE_SERVER = 0,				//�����
	ENUM_PIPE_TYPE_CLIENT,					//�ͻ���
} ENUM_CREATE_PIPE_TYPE;

//�̹߳���״̬
typedef enum
{
	ENUM_THREAD_STATE_START = 0,			//��ʼ
	ENUM_THREAD_STATE_WAIT,					//��ͣ
	ENUM_THREAD_STATE_STOP,					//ֹͣ
} ENUM_THREAD_STATE_TYPE;

enum ENUM_PIPE_DATA_TYPE
{
	dt_single = 0			,
	dt_struct
};
#endif //_PIPE_DATA_TYPE_SOURCE_H_
