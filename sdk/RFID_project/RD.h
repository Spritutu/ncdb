
// #define CONFIG_FILE L"D:/svn_work/c++/sdk/config.ini"
// #define CONFIG_FILEA "D:/svn_work/c++/sdk/config.ini"
#define CONFIG_FILE L"config.ini"
#define CONFIG_FILEA "config.ini"

//�Զ�����Ϣ
#define UM_SHOW_DATA	WM_USER + 100
#define UM_DELAY_MSG	WM_USER + 101
struct ComplexSt
{
	void* p1;
	void* p2;
};

struct TrackInfo
{
	int loopId;//����id
	int avgSpeed;//ƽ����
	int userRatio;//ռ����
	int avgDistance;;//��ͷ���
	int carNumB;//������   ��
	int carNumM;//������	��
	int carNumS;//������    С
	int wait;//�ȴ�ʱ��	
	int isHaveData;//������ʶ
};

struct TrafficInfo
{
	char tag[4];
	char devsn[12];//�豸���
	char tim[24];//�ϴ�ʱ��
	int len;//������ʹ��
	TrackInfo info[32];
	int jpeg_file_len;//jpeg�ļ����ȣ������ֽ���,��ntohlת��
	void* jpeg_file_buf;//ץ��ͼ������
};

//��ʾ�Ľṹ
struct TrackShow
{
	char tag[5];
	char devsn[11];//�豸���
	char tim[25];//�ϴ�ʱ��

	char loopId[4];//����id
	char avgSpeed[8];//ƽ����
	char userRatio[6];//ռ���� 0 - 1000 .3
	char avgDistance[7];;//��ͷʱ��
	char carNumB[4];//������   ��  4byte, ��������
	char carNumM[4];//������	��
	char carNumS[4];//������    С
	char carTotal[5];//�ܳ�����
	int wait;//�ȴ�ʱ��	
	int isHaveData;//������ʶ
};