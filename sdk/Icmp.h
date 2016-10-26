#pragma once
#include <WinSock2.h>
#include "PiTypeDef.h"
typedef struct icmp_hdr  
{  
    unsigned char   icmp_type;      // ��Ϣ����   
    unsigned char   icmp_code;      // ����   
    unsigned short  icmp_checksum;  // У���   

    // �����ǻ���ͷ   
    unsigned short  icmp_id;        // ����Ωһ��ʶ�������ID�ţ�ͨ������Ϊ����ID   
    unsigned short  icmp_sequence;  // ���к�   
    unsigned long   icmp_timestamp; // ʱ���   
} ICMP_HDR, *PICMP_HDR; 


USHORT checksum(USHORT* buffer,int size);

class CIcmp
{
public:
    CIcmp(void);
    ~CIcmp(void);
public:
    bool    IsDeviceNormal(const char* m_DeviceIp);
    void    SetRecvTimeout(UNINT nTimeout);
private:
    UNINT   m_nRecvTimeout;
};
