/***********************************************************************
 Copyright (c), 2012, Unicorn Tech. Co., Ltd.

 File name   : Directory.h
 Description : ��ȡϵͳĿ¼ 
 Version     : 1.0
 Author      : xuemingzhi
 Date        : 2014/08/14
 Other       :
 -----------------------------------------------------------------------
 History 1 
      Date   : 
      Author : 
      Modification : 
***********************************************************************/

#include "k_filepath.h"

/* Ŀ¼������
     ֧�ֿ�ݻ�ȡ��Ҫ��Ŀ¼������������������װ����
*/
class CDirectorys
{
public:
	// [Unicorn]:CSP�Զ����ز����ݿ���Ŀ¼
	static KFilePath GetCSPMaterialDB();
	// [Unicorn]:CSP�Զ����زĴ��Ŀ¼
	static KFilePath GetCSPMaterialInstall();   
    static KFilePath GetCSPMTPreSetupDirMain();
    static KFilePath GetCSPMTPreSetupDirBackup();
    static KFilePath GetExpandDir(LPCTSTR szSrc);	
public:
	/* ��ȡ����ϵͳԤ����Ŀ¼

		CSIDL_BITBUCKET				����վ
		CSIDL_CONTROLS				�������
		CSIDL_DESKTOP				Windows ����Desktop
		CSIDL_DESKTOPDIRECTORY		Desktop��Ŀ¼
		CSIDL_DRIVES				�ҵĵ���
		CSIDL_FONTS					����Ŀ¼
		CSIDL_NETHOOD				�����ھ�
		CSIDL_NETWORK				�����ھ�����Ŀ¼
		CSIDL_PERSONAL				�ҵ��ĵ�
		CSIDL_PRINTERS				��ӡ��
		CSIDL_PROGRAMS				������
		CSIDL_RECENT				����򿪵��ĵ�
		CSIDL_SENDTO				�����͵����˵���
		CSIDL_STARTMENU				�����������˵���
		CSIDL_STARTUP				����Ŀ¼
		CSIDL_TEMPLATES				�ĵ�ģ��
	*/
	static KFilePath GetSysPredefineDir(int csidl);
};

