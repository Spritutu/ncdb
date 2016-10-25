#include "StdAfx.h"
#include "GLogHelper.h"
#include "PathLight.h"
#define WIN32_LEAN_AND_MEAN
#include "define_gnl.h"
#undef ERROR

//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "glog/logging.h"
#include "PathLight.h"
#include "functional.h"
#include "UCommon.h"
#include "StrCoding.h"

CGLogHelper::CGLogHelper(void)
{
}


CGLogHelper::~CGLogHelper(void)
{
	if (!m_bHasInit)
	{
		return;
	}
	google::ShutdownGoogleLogging();
}

bool CGLogHelper::SetInstallFailureWriter()
{
	//google::InstallFailureSignalHandler();	//TODO:�޷����ӵķ���
	//google::InstallFailureFunction(FuncFa33);	//TODO:�޷����ӵķ���
	
	//google::InstallFailureWriter(FuncFailureWriter);
	return true;
}

bool CGLogHelper::Init()
{
	InitParam();
	m_bHasInit = IsWriteLog();
	if(!m_bHasInit)
	{
		return true;
	}
	google::InitGoogleLogging("CaptionRenRenLog");
	CPathLight path = CPathLight(GetSelfModuleFolder());
	path.AddSubSession(_T("log"));

	CDirectoryUtil::CreateMultipleDirectory(path);
	google::SetLogDestination(google::GLOG_INFO, pw2psSmart(path + _T("info_")));
	google::SetLogDestination(google::GLOG_WARNING, pw2psSmart(path + _T("warn_")));
	google::SetLogDestination(google::GLOG_ERROR, pw2psSmart(path + _T("erro_")));
	google::SetLogFilenameExtension(".log");
	return SetInstallFailureWriter();
}

bool CGLogHelper::InitParam()
{
	FLAGS_logbufsecs = 0;		//����д
	FLAGS_max_log_size = 200;	//�����ļ����(N)M
	/*FLAGS_minloglevel = 1;
	FLAGS_logbuflevel	= 0;*/
	FLAGS_v				= 1;	//�������С�ڸ���ֵ����־VLOG(N)
	FLAGS_stop_logging_if_full_disk = true;
	FLAGS_log_size_total_limit = 1024 * 14;//2^20 * 50;
	//google::SetStderrLogging(google::INFO);
	return true;
}

bool CGLogHelper::IsWriteLog()
{
	return true;
}

void FuncFailureWriter(const char* data, int size)
{
	string strLog(data, size);
	LOG(INFO) << "encounter FailureWrite:" << strLog;
	return ;
}

void FuncFa33()
{

}
