#pragma once
#ifndef _PIPE_MANAGE_H_
#define _PIPE_MANAGE_H_

#include "PipeDataTypeSource.h"
#include "Lock.h"
#include "PiTypeDef.h"
#include "threadlight.h"
/*******************************************************
����:	�������������ܵ��Ĺ���, �����ܵ�\���ӹܵ�,���ҶԹܵ����ݵĶ�д
����:   �ڲ������߳�����д�ܵ�

ʹ��˵��:
   ʵ�ֽӿ�
   DealReadData, ��ȡ������Э�����øýӿ�, �ڲ�����Э�����ͻ�ȡ����
   DealReadStruct, ��ȡ���ṹ��Э�����øýӿ�, ����Э�����ͻ�ȡ����, �ɽ�����õ�Transfer�ӿڷ�װ��дһ�廯�ӿ�
   DoReadFail, ��ȡʧ��ʱ����

��������:
    ������������(�������ݻ�ṹ��) -> ����Э��, ��������

    ������������ -> ��ȡЭ��-> ����Э���ȡЭ������
******************************************************/

class CPipeManage:public CThreadLight
{
public:
	typedef UNINT	DataSize;
	enum ENUM_TRANSFER_TYPE {type_read = 0, type_write};
    CPipeManage();
    virtual ~CPipeManage();
public:



protected:
/************************************************************************
    fun:    �ܵ����ܵ����ݺ���øýӿ�, 
    param: 
    remark: ���ݱ�����m_pBuf, ��СΪm_nReadSize
************************************************************************/
	virtual bool DealReadData();
	/*------------------------------------------------------------
			fun:	��ȡ����ʧ��ʱ����ã� �ɵ���IsCloseBySelf�ж��Ƿ�Ϊ��һ�˹ر��˹ܵ�
			ret:	
			param: 
			remark:	
	------------------------------------------------------------*/
	virtual bool DoReadFail();
	virtual bool DealReadStruct();
public:
	virtual DWORD DoWork();

/************************************************************************
    fun:    �ܵ���ȡ����ʧ��ʱ���øýӿ�, 
    param: 
    remark: ���ݱ�����m_pBuf, ��СΪm_nReadSize
************************************************************************/
	void ReadFail();
public:
    bool Init();
    bool UnInit();

	//����/��ָ�����͵�PIPE
	bool CreatePipe(	LPCTSTR lpPipeName = _T("\\\\.\\pipe\\mypipe"),			//strPipeName ָ����Pipe����
						ENUM_CREATE_PIPE_TYPE enumCreateType = ENUM_PIPE_TYPE_CLIENT,	//ָ������������,�����/�ͻ���
						void(*ptr)(char *, int ) = NULL									//����ܵ������ݵĺ���ָ��
						);
	//�رչܵ�
    bool ClosePipe();
	/*------------------------------------------------------------
			fun:	�жϹܵ��Ƿ�Ϊ�Լ���������رյ���
			ret:	
			param: 
			remark:	
	------------------------------------------------------------*/
	bool IsCloseBySelf();
	bool EndPipe(void);
	bool DealReadFail();

	//��ܵ�д����
	//char * pBuf ����ָ��  nBufSize ���ݴ�С
    bool Write(void * pBuf, int nBufSize, bool bWriteSize = true);
	bool Write(int nValue, bool bWriteSize = true);
	bool Write(UNINT nValue, bool bWriteSize = true);
	bool Write(LLONG nValue, bool bWriteSize = true);
	bool Write(bool nValue, bool bWriteSize = true);
	bool Write(tcpchar nValue);
	bool Write(StringCRef nValue);

	bool Transfer(int& nValue, ENUM_TRANSFER_TYPE enType);
	bool Transfer(UNINT& nValue, ENUM_TRANSFER_TYPE enType);
	bool Transfer(LLONG& nValue, ENUM_TRANSFER_TYPE enType);
	bool Transfer(bool& nValue, ENUM_TRANSFER_TYPE enType);
	bool Transfer(tstring& nValue, ENUM_TRANSFER_TYPE enType);

	bool WriteSingleBegin();
	bool WriteSingleEnd();
	bool WriteSingleData( int nValue );

    bool IsValidHandle();

	//��ܵ�д����
	//int nData ��������
	bool WriteStr(int nData);

	//�ж��Ƿ��Ѿ�����/����PIPE
    bool IsCreatePipe();
    bool WaitConnect();
	//��ȡ��ǰ����PIPE����
    ENUM_CREATE_PIPE_TYPE GetCurPipeType();

	bool WriteStructBegin();
	bool WriteStructBegin(ENUM_TRANSFER_TYPE enMode);
	bool WriteStructEnd();
	bool WriteStructEnd(ENUM_TRANSFER_TYPE enMode);

protected:
	//���������
	bool CreatePipeServer(LPCTSTR lpPipeName);
	//�����ͻ���
	bool CreatePipeClient(LPCTSTR lpPipeName);

    bool ConnectPipe( LPCTSTR lpPipeName );

/************************************************************************
    fun:    ��ȡ�ܵ�����, ���û����������
    param: 
    remark: ��ȡ�ɹ�����true, ���ݱ�����m_pBuf, ��СΪm_nReadSize
************************************************************************/
	bool ReadPipe(void);
	bool ReadPipeCatch(void);
	bool ReadPipe(bool& nValue);
	bool ReadPipe(int& nValue);
	bool ReadPipe(UNINT& nValue);
	bool ReadPipe(LLONG& nValue);
	bool ReadPipe(tstring& nValue);

    bool IsReadErr();

    bool CreateWorkThread(void);
	//	static DWORD WINAPI RunProc(LPVOID lpParam);
	//void Porc(void);
protected:
	void (*m_pReadFun)(char *, int nSize);
    //��һ�˽����˹ܵ�
    bool DealPipeEnd();
    bool ReWaitConnect();
    bool IsClose();

	bool ReadDataType( ENUM_PIPE_DATA_TYPE& dType );
/************************************************************************
    fun:    �ͻ������ӳɹ�����øýӿ�
    param: 
    remark: 
************************************************************************/
	virtual bool DoClientConnectOk();
	bool TransferSP( POINT * param1, ENUM_TRANSFER_TYPE enType);
	HANDLE m_hPipe;
	//HANDLE m_hThread;
	ENUM_CREATE_PIPE_TYPE m_enumPipeType;
	ENUM_THREAD_STATE_TYPE m_enumThreadState;
    void*                   m_pBuf;			//�������ݻ���
    DWORD                   m_nReadSize;	//���յ������ݴ�С, �ֽ���

    HANDLE                  m_hEvent;
    HANDLE                  m_hEventRead;
    HANDLE                  m_hEventWrite;
    CLock                   m_lockWrite;
    tstring                 m_strPipeName;
    bool                    m_bEnd;
	bool					m_bStruct;		//��ǵ�ǰ���͵��Ƿ��ǽṹ��
	bool					m_bConnectOk;
	bool					m_bCloseActive;	//�Ƿ��������رյ�
};

#endif//_PIPE_MANAGE_H_
