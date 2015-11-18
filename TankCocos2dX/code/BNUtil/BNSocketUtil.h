#ifndef  _BNSocketUtil_H_
#define  _BNSocketUtil_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include "cocos2d.h"
#include "TankSceneManager.h"


USING_NS_CC;

class BNSocketUtil
{
  public:
	//����ִ�б�־λ
	static int okFlag;
	static int selectFlag;
	static int fullFlag;
	static int mainBulletFlag;
	static int mainMissileFlag;
	static int otherBulletFlag;
	static int mapDataFlag;
	static int dataFlag;
	static int bossBulletFlag;
	static int bossFlag;
	static int bossNewFlag;
	static int stateFlag;
	static int mapTreeFlag;
	static int explosionFlag;
	static int mapTankFlag;
	static int awardFlag;
	static int exitFlag;
	static int clearFlag;
	static int tankFlag;

	static int bossNumber;

	static int socketHandle;
	//�Ƿ����ӷ������ɹ���־
	static bool connectFlag;
	//���ӷ������ķ���
	static void connect(const char* ip, unsigned short port);

	static void sendInt(int si);

	static char* receiveBytes(int len);

	static void sendFloat(float sf);

	static void sendStr(const char* str,int len);

	static int receiveInt();

	static float receiveFloat();

	static char* receiveStr();
	//�������񷽷������߳�ִ��
	static void* threadConnectTask(const char* ip, unsigned short port);
	//�������񷽷������߳�ִ��
	static void* threadReceiveTask();

	static void closeConnect();
};

#endif
