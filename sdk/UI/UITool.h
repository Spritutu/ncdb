#pragma once
#include "..\PiTypeDef.h"
using std::string;
/************************************************************************/
/*	fun: ��ȡһ���Ϸ��ļ�·��, ������Ҫ֧���Ϸ�:ͨ��DragAcceptFiles����
/************************************************************************/
tstring GetOneDragFilePath(const HDROP& hd);