#pragma once
#include "PiTypeDef.h"
/************************************************************************
	fun:des�ײ�����߼�
	remark:���ܺ�����ݳ��ȸ�ԭ��һ��
************************************************************************/

class CPiDES {  
public:  
    BYTE bOriMsg[8] ;               // ��ʼ��Ϣ ( 64 bit )  
    BYTE LMsg[17][4], RMsg[17][4] ; // �м����L0-->L16,R0-->R16 ( 32 bit )  
    BYTE bKey[8] ;                  // ������Կ ( 64 bit )  
    BYTE bSubKey[17][6] ;           // ��������ԿK1-->K16 ( 48 bit )  
    BYTE bCryptedMsg[8] ;           // ����  
public:  
    void DES_Encrypt ( ) ;  
    void DES_Decrypt ( ) ;  
	bool DES_Encrypt ( LPBYTE lpSour, LPBYTE lpDest, UINT uLen, LPBYTE lpKey ) ;  
	/************************************************************************
		fun:	����, ���ܺ�����������ڴ����ڲ�����
		param:lpDest:out, ���ؼ��ܺ����ݵ��ڴ��ַ, ��Ҫ�ⲿ�ͷ�. uLen: ԭ�ĳ���, key:8���ֽ�
		ret:	���ܺ����ݵĴ�С, �ֽ���
	************************************************************************/
	UNINT DES_EncryptEx ( LPBYTE lpSour, LPBYTE& lpDest, UNINT uLen, LPBYTE lpKey ) ;
    UNINT DES_EncryptEx ( LPBYTE lpSour, LPBYTE& lpDest, UNINT uLen, const char* lpKey ) ;

	bool DES_Decrypt ( LPBYTE lpSour, LPBYTE lpDest, UINT uLen, LPBYTE lpKey ) ;  
	UNINT DES_DecryptEx ( LPBYTE lpSour, LPBYTE& lpDest, UINT uLen, LPBYTE lpKey ) ;  
	UNINT DES_DecryptEx ( LPBYTE lpSour, LPBYTE& lpDest, UINT uLen, const char* lpKey ) ;  
    UNINT DES_DecryptEx ( LPBYTE lpSour, string& lpDest, UINT uLen, const char* lpKey ) ;  
public:  
    // ��ʼ�û�  
    void DESInitSwap ( ) ;  
    // ��ʼ���û�  
    void DESInitReSwap () ;  
    // ��������Կ  
    void DESGenSubKey ( ) ;  
    // DES�ĵ��ּ��ܹ���  
    void DESSingleTurn ( BYTE nTurnIndex, bool bMode ) ;  
    // DES��F����  
    void DES_f ( BYTE bTurnIndex, bool bMode ) ;  
public:  
    // ��ʼ��  
    void DES_SysInit () ;   
    // ��������  
    void DES_SetOriMsg ( PBYTE pMsg, UINT uLen ) ;  
    // ������Կ  
    void DES_SetKey ( PBYTE pKey, UINT uLen ) ;  
} ; 