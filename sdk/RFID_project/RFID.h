//��ʾ�Ľṹ
#pragma once
#include "PiTypeDef.h"
#include <vector>
#include <deque>
#include <list>
#include "define_gnl.h"
/************************************************************************
    ������3����Ŀ����:
        debug:          ʹ����ʵ����, ���ݲ����͸�ƽ̨
        Test_Debug:     ʹ��ģ������, ���ݲ����͸�ƽ̨, ģ���һ��ʵʱ����
        Release_Debug:  ʵ�ʷ����汾
/************************************************************************/
using namespace std;
struct TAG_DATA_DESC;
//���ܺ���
typedef  bool (_stdcall *FunRFIDEncrypt)(PCSTR, char*);

#define NUM_IMITATE_READER          "30"      //ģ�����������
#define DEBUG_DATA  //�������ݣ� �����������ĵ���, e.g: ǰ�η���ʱ��


#ifdef Release_Debug    //������ ʵ�ʹ����汾
        
#elif defined TEST_DEBUG    //�Լ����ԣ� û�豸���ݰ汾

    #define DEBUG_ALL   //���԰汾, ������
    #define RTDATA_IMITATE
    #define RT_DATA_SELF    //RT����ֻ�����Լ�
    #define TEST_UDP    //����UDP, �ر� ����ǰ�������

#else   //���豸���ݣ� Ҫ����
    #define RT_DATA_SELF    //RT����ֻ�����Լ�
    #define DEBUG_ALL   //���԰汾, ������
#endif

/************************************************************************/
/*  ��־������ƿ���
/************************************************************************/
#define BOOL_OUTPUT_NATIVE_TIMESTAMP            //ԭ�������Դ���ʱ���ת��1970-ms
//#define BOOL_OUTPUT_TWO_TIMES_SPEND           //�յ�����������ϸ�����ʱ��


#define MSG_TYPE_RTDATA                 1       //��Ϣ����- ʵʱ��ǩ����
//#define LOG_THREAD                            //�߳���д��־






#define FILL_TIME 2 //����UDP���ݵ�������

#define FLAG_BK     3   //���ر��
#define FLAG_CK     2   //���ر��

#define NUM_READER_MAX_ANTENNA              4       //һ�����������֧�ֵ�������
#define NUM_CIRCLE_LANE_EPC_NUM_MAX         4       //һ��������һ������һ����������ܶ�����EPC��
#define NUM_CIRCLE_EPC_NUM_MAX              20       //һ��������һ����������ܶ�����EPC��
#define DIRECTION_EAST_TO_WEST              4       //����,������
#define DIRECTION_LOW                       2       // ����IDС���Ǹ�����
#define NUM_READER_NODATA_TIMEOUT           3       //������n��û��������,������һЩ����

#define NUM_READER_LIMIT                    80	    //��д������


#define IS_HIGH_LANE(laneId)    (laneId >= 3 && laneId <= 4)

#define IP_SPECIAL                          "192.192.12.22"//����㣬������������
#define NUMBER_DEVICE_HIGH_LANE             2//�����, ����ID�ߵ��Ǹ������������
#define TABLE_LOCAL_DISPOSE                 "T_ITGS_LOCAL_DISPOSE"


#define NUM_READER_RECV_CACHE_MAX           4000        //һ�����������ջ���������ܴ��ԭʼ���ݵ�����
#define NUM_READER_DB_CHCHE_MAX             20000       //һ�����������ݿ��������ܴ�ŵ�����
#define NUM_READER_DB_CACHE_RATIO_LOG       1000        //��ԭ��DB���и����Ļ�����, ÿ���Ӹ�ϵ��дһ��log
#define NUM_UPDATE_UI_CIRCLE                5000        //��õ����ڸ��½����ʣ������,��λms
#define NUM_LOG_THREAD_SLEEP                40          //д��־�߳���ʱ
//����
#define SEQ_RFID_PASSCAR                "SEQ_RFID_PASSCAR"
#define SEQ_RFID_ALARM                  "SEQ_RFID_ALARM"

//3��ip, ���ظ�����һ�����ĵ�
#define STR_FILTER_READER_IP_LEFT              "192.192.12.23"
#define STR_FILTER_READER_IP_MIDDLE            "192.192.12.22"
#define STR_FILTER_READER_IP_RIGHT             "192.192.12.21"

#define STR_DB_TEMP_SEQUENCE                    L"SequenceId"
// �ظ���EPC�ķֱ����ļ�������
#define NUM_FILTER_READER_LANE_LEFT             1
#define NUM_FILTER_READER_LANE_MIDDLE_LEFT      1
#define NUM_FILTER_READER_LANE_MIDDLE_RIGHT     4
#define NUM_FILTER_READER_LANE_RIGHT            1

//����epc����������������
#define NUM_FILTER_READER_EPC_CACHE             40
#define NUM_FILTER_EPC_LIST                     10             //���˵�epc�б����

const UINT TAG_DATA_REMAIN_SIZE = 21;
const byte FRONT_FIX_DATA_SIZE  = 9;

//������
const UINT NUM_BATCH_WRITE_DB               =     4;         //�����������10���������

//UDP ��������
#define UDP_CIRCLE_250

#ifdef UDP_CIRCLE_250
    const UINT NUM_SEND_UDP_CYCLE       = 250;//����UDP����
    const UINT NUM_SEND_CIRCLE_TIMES    = 4;//һ�뷢��������
#else
    const UINT NUM_SEND_UDP_CYCLE       = 500;//����UDP����
    const UINT NUM_SEND_CIRCLE_TIMES    = 2;//һ�뷢������
#endif


#ifdef TEST_DEBUG
    //#define INFO(msg) OutputDebugStringA(msg)
#elif defined(LOG_THREAD)
    #define INFO(msg) CSingleLog::PutThread(msg);
#else
    #define INFO(msg) CSingleLog::WriteLog(msg);
#endif

//�ڴ汨�����ͽṹ
class ALARM_RECORD_DATA
{
public:
    void Reset()
    {
        strID       = "";
        strHPHM     = "";
        strHPYS     = "";
        strBCKBJ    = "";
        strBJLX     = "";
    }
    string  strID;
    string  strBJLX;//��������
    string  strHPHM;
    string  strHPYS;
    string  strBCKBJ;
};

struct TrackShow
{
	wstring id;//id
	wstring deviceId; //�豸���
	//WCHAR deviceName;//�豸����
	//WCHAR direction;;//������
	wstring laneId;//����id

	wstring tagCode;//��ǩ����
	wstring CarCardID;//���ƺ���
    wstring strHPYS;//������ɫ
	wstring CarKind;//��������
	wstring speed;//�����ٶ�
	wstring EnterTime;//����ʱ��
	wstring LevelTime;//�뿪ʱ��
	wstring responseCount;//��Ӧ����
    wstring strCount;   //�ó���DB����ʣ������
    wstring carCount;    //�������ж�������
};


struct RECV_DATA_TCP
{
	u_short err;//������
	byte	optType;
	byte	epcLen;//epc����
	byte	epc[64];//
	byte	ret;//���
	byte	dataLen;//���ݳ���
	byte	data[64];//����
	byte	antennaId;//����ID
	byte	byProtocol;//Э��
	byte	epcRCnt;//EPC������
	byte	user;//�ɹ�����
	byte	timestamp[14];//ʱ���
};

//***************** �°汾Э�� *****************
//�µĳ�����, һ����250msȫ��������

#pragma pack(push)
#pragma pack(1)
struct TAG_DATA
{
    byte				byTagCount;//��ǩ����
    TAG_DATA_DESC*		pTddArr;//��ǩ��������������
    byte				ReaderNameLen;//��д�����Ƴ���
    char*				ReaderName;//��д������
};

struct RECV_DATA_TCP_SET
{
	short				msgVer;//��Ϣ�汾
	byte				msgType;//��Ϣ����, 1��ʾʵʱ��ǩ���ݣ�2��ʾ���߱�ǩ����
	UNINT				msgSN;//��Ϣ���к�
	short				uTagDataLen;//��Ϣ���ݲ��ֳ���
	TAG_DATA            tagData;//��Ϣ���ݲ���
    void*               pTAG_DATA;//�����ͷŵı�ǩ�������ָ��
};


struct TAG_DATA_DESC
{
	byte	byEpcLen;//Epc����
	char*	pEpc;//Epc
	byte	byTagMemDataLen;//��ǩ�ڴ����ݳ���
	void*	pTagMemData;//�ڴ�����
	byte	byAntennaID;//����
    byte	byReadCnt;//������
	byte	byProtocal;//Э��
	byte	byRssi;//�ź�ǿ��
	char	szTimeStamp[17];//ʱ���
};
#pragma pack(pop)
//***************** �°汾Э�� *****************



//UDP��������
typedef struct tagSendData
{
    string  strDZBQH;	//���ӱ�ǩ��RFID
    byte	nCXFX;		//���з���
    byte	nCDH;		//������/���ߺ�
    int		nGYCS;		//��Ӧ����

    time_t tSCSJ;	    //�ɼ�ʱ��
    DWORD dwIndex;      //����ˮ��, ͬһ��250ms���ڵ���ˮ��һ��
    void Reset()
    {
        nCXFX       = 0;
        nCDH        = 0;
        nGYCS       = 0;
        dwIndex     = 0;
        strDZBQH    = "";
    }
    bool operator< (const tagSendData& sd) const
    {
        return strDZBQH < sd.strDZBQH;
    }
}SENDDATA;

//һ����������, �����ܶ�������, ����ʱ����뿪ʱ��
class SDPassCar
{
public:
    /*SDPassCar()
    {
        
    };*/
    SENDDATA sd;
    time_t  tNewTime;  //�ó����µ�ʱ��
    bool bPass;        //���ͨ��, �򲻸��¸ó�
};

//�о������Ƿ�ͨ��
struct timeDecidePassCar
{
    time_t  tNow;
    time_t  tCarTimeout;
    //UINT    nPassCarCount;      //ͨ���ĳ�����
};

//���Ͷ���
typedef vector<SENDDATA> SendDataList;  //һ�����ڵ�����epc����
typedef deque<SENDDATA> DqSendData;
typedef list<SENDDATA>  LISTSendData;
typedef deque<SDPassCar> DqPassCar;

//UDP����ṹ�� ��������©��������
class CACHE_SD
{   
public:
    byte laneId;//������
    byte byDirection;//����,һ�������������������Ҫ�õ�
    string EPC;
    byte remainTime;//ʣ�����, delete this record when this field == 0
    void Reset()
    {
        laneId = 0;
        EPC  = "";
        byDirection = 0;
        remainTime = FILL_TIME;
    }
};

//EPC�ṹ����Ϣ, ���ڳ�����������������ʱ�Ĺ���
class EpcInfo
{
public:
    byte    byReaderID;
    byte    byAntennaId;
    string  strEpc;

    void Reset()
    {
        byReaderID  = 0;
        byAntennaId = 0;
        strEpc      = "";
    }
};

class PassCarData
{
public:
    string strDeviceID; //�豸ID
    string strDDBH;     //�ص���
    string strDZBQH;    //EPC
    string strSBMC;     //�豸����
    string strHPHM;     //���ƺ���
    string strHPYS;     //������ɫ
    string strHPZL;     //��������
    byte    byFX;       //����
    byte    byCDH;      //������
    string  strBeginTime;
    string  strEndTime;
    ULONG   lGYCS;      //��Ӧ����
    void Reset()
    {
        strDeviceID     = "";
        strDDBH         = "";    
        strDZBQH        = "";   
        strSBMC         = "";    
        strHPHM         = "";    
        strHPYS         = ""; 
        strHPZL         = "";
        strBeginTime    = "";
        strEndTime      = "";
        byFX            = 0;
        byCDH           = 0;
        lGYCS           = 0;

    }
};


typedef vector<CACHE_SD>        vectorCache;
typedef deque<SendDataList*>    LaneQueue;      //һ�������������ڵ�����