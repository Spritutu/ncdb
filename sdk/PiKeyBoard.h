#pragma once
class CPiKeyBoard
{
public:
    CPiKeyBoard(void);
    virtual ~CPiKeyBoard(void);
public:
/************************************************************************
        fun:	�ж�ָ���İ����Ƿ��ڰ���״̬
        param:  
        ret:    true: ָ������Ϊ����״̬
        remark:  ���ⰴ��, �� VK_SHIFT
/************************************************************************/
    static bool IsKeyPush( int nKeyCode );
};

