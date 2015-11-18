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

USING_NS_CC;

class BNSocketUtil
{
  public:
	static int  socketHandle;
	static LabelTTF* msgLabel;
	//�Ƿ����ӷ������ɹ���־
	static bool connectFlag;
	//���ӷ������ķ���
	static void connect(const char* ip, unsigned short port);

	static void sendInt(int si);

//	static void sendFloat(float sf);

//	static void sendStr(const char* str,int len);
	static char* receiveBytes(int len);

	static int receiveInt();

//	static float receiveFloat();

//	static char* receiveStr();
	//�������񷽷������߳�ִ��
	static void* threadConnectTask(const char* ip, unsigned short port);
	//�������񷽷������߳�ִ��
	static void* threadReceiveTask();

	static void closeConnect();
};

#endif
