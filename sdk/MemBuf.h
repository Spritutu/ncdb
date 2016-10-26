#pragma once
#include "PiTypeDef.h"

class CMemBuf
{
public:
	CMemBuf(void);
	~CMemBuf(void);

public:
	/************************************************************************/
	/*	fun: ׷���µ��ڴ����ݵ���ά���Ļ�������, ����ڴ治��,����Զ���������ڴ�
		ret: ���������ڴ�ռ��,ԭ�ȵ��ڴ�ᱻ�ͷŵ�
	/************************************************************************/
	void AppendData(void* pData, UNLONG dwSize);
	void ReleaseMem();
	char*	GetBuffer();
	UNLONG	GetBufTotalSize();
protected:
	/************************************************************************/
	/*	fun: ���������ڴ�,����ԭ�ȵ������ƶ����µ��ڴ���
		ret: ���Լ��ͷŵ�ԭ�����ڴ�
	/************************************************************************/
	void	MoreToBigger();

private:
	UNLONG	m_bufTotalSize;//ά���Ļ�������С
	UNLONG	m_dataSize;//ʵ���д�����ݵĴ�С

};
