#include "BNSocketUtil.h"
#include "AppMacros.h"
#include "GameLayer.h"
#include "Constant.h"

int BNSocketUtil::socketHandle=0;
LabelTTF*  BNSocketUtil::msgLabel;
bool BNSocketUtil::connectFlag=false;

void BNSocketUtil::connect(const char* ip, unsigned short port)
{
	if(!connectFlag)
	{
		msgLabel->setString("\u8fde\u63a5\u4e2d");//������
		new std::thread(&BNSocketUtil::threadConnectTask,ip,port);//�����߳�
	}
}

void BNSocketUtil::sendInt(int si)
{
	 send(socketHandle,&si,4,0);//����int����
}
//�����ֽ�
char* BNSocketUtil::receiveBytes(int len)
{
	char* result=new char[len];

	int status=recv(socketHandle, result, len, 0);

	while(status!=len)
	{
		int index=status;
		char b[len-status];
		int count=recv(socketHandle, b, len-status, 0);
		status=status+count;
		if(count!=0)
		{
			for(int i=0;i<count;i++)
			{
				result[index+i]=b[i];
			}
		}
	}

	return result;
}
//����int����
int BNSocketUtil::receiveInt()
{
	char* a=receiveBytes(4);
	int ri;

	memset(&ri, 0, sizeof(ri));
	memcpy((char*)(&ri), a,4);
    delete a;
	return ri;
}

void  BNSocketUtil::closeConnect()
{
	if(connectFlag)
	{
		::close(socketHandle);
		connectFlag=false;
	}
}

void* BNSocketUtil::threadConnectTask(const char* ip, unsigned short port)
{
	struct sockaddr_in sa;
	struct hostent* hp;
	hp = gethostbyname(ip);//����������������ȡIP��ַ
	if(!hp)
	{
	     return 0;
	}
	memset(&sa, 0, sizeof(sa));
	memcpy((char*)&sa.sin_addr, hp->h_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;
	sa.sin_port = htons(port);
	socketHandle = socket(sa.sin_family, SOCK_STREAM, 0);
	if(socketHandle < 0)
	{
		return 0;
	}
	if(::connect(socketHandle, (sockaddr*)&sa, sizeof(sa)) < 0)
	{
	    ::close(socketHandle);
	    return 0;
	}
	msgLabel->setString("\u8fde\u63a5\u6210\u529f");
	connectFlag=true;
	new std::thread(&BNSocketUtil::threadReceiveTask);
}
//���������߳�
void* BNSocketUtil::threadReceiveTask()
{
	while(connectFlag)
	{
		//ÿһ���Ƚ��ձ�־λ����   0-��ʾ����Ϊ����  1-��ʾ����Ϊ������ 2-��ʾ�ַ���
		int ri = receiveInt();
		if(ri==0)//�������ͼ��
		{
			//������Ϸ�������Ŀ
			Constant::playerCount = receiveInt();
			if(Constant::playerCount==1)
			{
				Constant::playerId = receiveInt();
				Constant::lastPlayerId = 2;
				Constant::nextPlayerId = 1;
			}
			else if(Constant::playerCount==2)
			{
				if(Constant::lastPlayerId==-1)
				{
					Constant::lastPlayerId=0;
				}
				int n = receiveInt();
				if(Constant::playerId==n)
				{
					Constant::nextPlayerId = receiveInt();
				}
				else if(Constant::lastPlayerId==n)
				{
					//��һ��id���
					Constant::lastPlayerId = n;
					//ÿ����ҵ�id���
					Constant::playerId = receiveInt();
				}
				else if(Constant::nextPlayerId==n)
				{
				}
			}
			else if(Constant::playerCount==3)
			{
				if(Constant::nextPlayerId==-1)
				{
					Constant::nextPlayerId=0;
				}
				int n = receiveInt();
				if(Constant::playerId==n)
				{
					Constant::nextPlayerId = receiveInt();
					//��һ��
					Constant::lastPlayerId = receiveInt();
				}
				else if(Constant::lastPlayerId==n)
				{
					//����
					Constant::playerId = receiveInt();
					//��һ��
					Constant::nextPlayerId = receiveInt();
				}
				else if(Constant::nextPlayerId==n)
				{
					//��һ��id���
					Constant::lastPlayerId = receiveInt();
					//����
					Constant::playerId = receiveInt();
				}
			}
        }
		else if(ri==1)//��ǰ׼��״̬
		{
			//readyNum����Ա��Ŀ
			Constant::readyNum = receiveInt();
			//�ж�׼����ҵ���Ŀ
			if(Constant::readyNum==0)//û�����׼��
			{

			}
			else if(Constant::readyNum==1)
			{
				int id = receiveInt();
				if(id==Constant::playerId)
				{
					Constant::playerReady=1;
				}
				else if(id==Constant::lastPlayerId)
				{
					Constant::lastPlayerReady=1;
				}
				else if(id==Constant::nextPlayerId)
				{
					Constant::nextPlayerReady=1;
				}
			}
			else if(Constant::readyNum==2)
			{
				int id1[2];
				id1[0] = receiveInt();
				id1[1] = receiveInt();
				for(int i=0;i<2;i++)
				{
					if(id1[i]==Constant::playerId)
					{
						Constant::playerReady=1;
					}
					else if(id1[i]==Constant::lastPlayerId)
					{
						Constant::lastPlayerReady=1;
					}
					else if(id1[i]==Constant::nextPlayerId)
					{
						Constant::nextPlayerReady=1;
					}
				}
			}
			else if(Constant::readyNum==3)//׼����־
			{
				int id2[3];
				id2[0] = receiveInt();
				id2[1] = receiveInt();
				id2[2] = receiveInt();
				for(int i=0;i<3;i++)
				{
					if(id2[i]==Constant::playerId)
					{
						Constant::playerReady=1;
					}
					else if(id2[i]==Constant::lastPlayerId)
					{
						Constant::lastPlayerReady=1;
					}
					else if(id2[i]==Constant::nextPlayerId)
					{
						Constant::nextPlayerReady=1;
					}
				}
			}
		}
		else if(ri==2)//����2����ʾ��Ҿ���׼��
		{
			//�����˿�����
			int pukeNum = receiveInt();
			//׼������17����,������17����֮��׼���е���
			for(int i=0;i<pukeNum;i++)
			{
				Constant::PUKEARRAY[i] = receiveInt();
			}
			//�����˿���ϣ���־λ��Ϊtrue
			Constant::pukeFlag=true;
			Constant::readyFlag=true;
            Constant::drawAct=true;
		}
		else if(ri==3)//��Ȩ
		{
			//��һ��˭�е���
			int whoOrder = receiveInt();
			Constant::whoFlag = whoOrder;//��ʼ�е������
			//����һ�εı������oldBeiNum
			Constant::oldBeiNum = Constant::beiNum;
			//���յ�ǰ����������ʾ��������
			Constant::beiNum = receiveInt();
			//�������ж��ǽе�������������
			Constant::landlordCount++;
			//����ÿ����ҵ���������״̬
			Constant::landlordListNum = receiveInt();//3

			for(int i=0;i<Constant::landlordListNum;i++)
			{
				Constant::landlordList[i] = receiveInt();//0-���У�1-�У�2-������3-����4-��
			}

			//menuitem
			Constant::menuItem=true;
		}
		else if(ri==4)//���յ����������Ƽ�20��			ֱ��һ��
		{
			if(Constant::landlordCount==4)
			{
				Constant::landlordCount++;
			}
			//����˭�ǵ���,��������id
			int landlord=Constant::whoIsLandlord = receiveInt();

			//����һ�εı������oldBeiNum
			Constant::oldBeiNum = Constant::beiNum;
			//���յ�ǰ����������ʾ��������
			Constant::beiNum = receiveInt();

			//���յ����˿�����
			int pukeLandlordNum = receiveInt();
			//׼������20����
			for(int i=0;i<pukeLandlordNum;i++)
			{
				Constant::tempPUKE[i] = receiveInt();
			}
			//�յ�20���� ,��ǣ�����ɾ����������
			//����ÿ����ҽ���ı����ƶ���ת�ı�־λ
			Constant::clearLandlordState=true;
			Constant::landlordHadPuke = true;
			//����ʣ���Ƶ���Ŀ����������
			int lastPukeNum = receiveInt();
			//׼������ʣ���Ƶ�id,��ʣ������PUKEARRAY[]���������
			for(int j=0;j<lastPukeNum;j++)
			{
				Constant::lastPukeId[j] = receiveInt();
			}

			if(landlord==Constant::playerId)
			{
				Constant::playerCardsCount=20;
			}else if(landlord==Constant::lastPlayerId)
			{
				Constant::lastPlayerCardsCount=20;
			}else if(landlord==Constant::nextPlayerId)
			{
				Constant::nextPlayerCardsCount=20;
			}
			Constant::drawCardsFlag=1;
			Constant::deleteMenu=true;		//ɾ���е��� ������˵���
			Constant::drawHeadImage=true;	//��������ũ��ͷ��
			Constant::drawLogo=false;		//����logo
		}
		else if(ri==5)//���յ�ǰ���Ƿ���Գ���0-������1-���Գ�
		{
			Constant::whoFlag=receiveInt();			//��ǰ��Ȩ
			Constant::isCanChuPai = receiveInt();	//�Ƿ���� 1Ϊ���ƣ�0Ϊ���ܳ�
			Constant::isDrawChuPai = true;
			Constant::isDrawReset = true;
		}
		else if(ri==6)//׼�����յ�ǰ��Ȩ���������Ŀ
		{
			//˭����Ȩ
			Constant::whoFlag = receiveInt();

			//�������ж�����������ƵĴ���
			Constant::landlordCount++;
			//����һ�εı������oldBeiNum
			Constant::oldBeiNum = Constant::beiNum;
			//���յ�ǰ����������ʾ��������
			Constant::beiNum = receiveInt();

			//������Ч��ά�����������,��־λ���Ϊture
			Constant::effectRow = receiveInt();
			Constant::effectCol = receiveInt();
			if(Constant::effectRow!=-1&&Constant::effectCol!=-1)
			{
				Constant::isCanPlayEffect=true;
			}
			//���ձ�־λ���ж��Ƿ���ơ���������0-���ƣ�1-������
			Constant::isBuChu = receiveInt();
			//�������������Ŀ�ı�־1-���Ի��ƣ�0-������----����׼������
			Constant::drawCardsFlag = receiveInt();
			if(Constant::playerId==0)
			{
				//0���������Ŀ
				Constant::playerCardsCount = receiveInt();
				//���1������Ŀ
				Constant::nextPlayerCardsCount = receiveInt();
				//2���������Ŀ
				Constant::lastPlayerCardsCount = receiveInt();
			}else if(Constant::playerId==1)
			{
				//0���������Ŀ
				Constant::lastPlayerCardsCount = receiveInt();
				//���1������Ŀ
				Constant::playerCardsCount = receiveInt();
				//2���������Ŀ
				Constant::nextPlayerCardsCount = receiveInt();
			}else if(Constant::playerId==2)
			{
				//0���������Ŀ
				Constant::nextPlayerCardsCount = receiveInt();
				//���1������Ŀ
				Constant::lastPlayerCardsCount = receiveInt();
				//2���������Ŀ
				Constant::playerCardsCount = receiveInt();
			}

			int cardLength = receiveInt();				//����ʣ���Ƶĳ���
			Constant::pukeRemainNumber = cardLength;
			for(int i=0;i<cardLength;i++)				//����ʣ���Ƶ�ID
			{
				Constant::PUKEARRAY[i]=receiveInt();
			}

			for(int j=0;j<3;j++)
			{
				int card = receiveInt();			//�������ID
				if(card!=100)
				{
					int cardsLength = receiveInt();		//idΪcard����ҳ��Ƶĳ���
					for(int i=0;i<cardsLength;i++)
					{
						if(Constant::playerId==card)	//��ǰ���ID
						{
							Constant::playerCards[i] = receiveInt();

							Constant::playerLength = cardsLength;
						}
						else if(Constant::lastPlayerId==card)
						{
							Constant::lastPlayerCards[i] = receiveInt();
							Constant::lastPlayerLength = cardsLength;
						}else if(Constant::nextPlayerId==card)
						{
							Constant::nextPlayerCards[i] = receiveInt();
							Constant::nextPlayerLength = cardsLength;
						}
					}
				}else
				{
					if(Constant::playerId==card)	//��ǰ���ID
					{
						Constant::playerLength=0;
					}
					else if(Constant::lastPlayerId==card)
					{
						Constant::lastPlayerLength =0;
					}else if(Constant::nextPlayerId==card)
					{
						Constant::nextPlayerLength =0;
					}
				}
			}
			Constant::isDrawChuPai = true;
			Constant::isDrawReset = true;
			Constant::drawCards=true;					//�������˿�
			Constant::drawAlreadyCard=true;				//���Ѿ�������
//			Constant::isTishi=true;
		}
		else if(ri==7)				//������ʾ
		{
			int Tishi= receiveInt();	//1Ϊ����ʾ
			if(Tishi==1)
			{
				int length=receiveInt();
				for(int i=0;i<length;i++)
				{
					Constant::tishiCard[i]=receiveInt();
				}
				for(int j=0;j<Constant::playerCardsCount;j++)
				{
					Constant::upCards[Constant::PUKEARRAY[j]]=0;
				}
				for(int n=0;n<length;n++)
				{
					for(int j=0;j<Constant::playerCardsCount;j++)
					{
						if(Constant::tishiCard[n]==Constant::PUKEARRAY[j])
						{
							Constant::upCards[Constant::PUKEARRAY[j]]=1;
						}
					}
				}
				Constant::drawCards=true;					//�������˿�
				Constant::drawTiShi=true;
			}else
			{
				Constant::drawTiShi=false;
                Constant::upCardsCount=0;
			}
		}else if(ri==8)					// ʤ��
		{
			//˭����Ȩ
			Constant::whoFlag = receiveInt();

			int victory=receiveInt();		//ʤ�� 1Ϊ����ʤ����0Ϊũ��ʤ��
			//�������ж�����������ƵĴ���
			Constant::victory=victory;
			Constant::landlordCount++;
			//����һ�εı������oldBeiNum
			Constant::oldBeiNum = Constant::beiNum;
			//���յ�ǰ����������ʾ��������
			Constant::beiNum = receiveInt();

			//������Ч��ά�����������,��־λ���Ϊture
			Constant::effectRow = receiveInt();
			Constant::effectCol = receiveInt();
			if(Constant::effectRow!=-1&&Constant::effectCol!=-1)
			{
				Constant::isCanPlayEffect=true;
			}
			//�������������Ŀ�ı�־1-���Ի��ƣ�0-������----����׼������
			Constant::drawCardsFlag = receiveInt();
			if(Constant::playerId==0)
			{
				//0���������Ŀ
				Constant::playerCardsCount = receiveInt();
				//���1������Ŀ
				Constant::nextPlayerCardsCount = receiveInt();
				//2���������Ŀ
				Constant::lastPlayerCardsCount = receiveInt();
			}else if(Constant::playerId==1)
			{
				//0���������Ŀ
				Constant::lastPlayerCardsCount = receiveInt();
				//���1������Ŀ
				Constant::playerCardsCount = receiveInt();
				//2���������Ŀ
				Constant::nextPlayerCardsCount = receiveInt();
			}else if(Constant::playerId==2)
			{
				//0���������Ŀ
				Constant::nextPlayerCardsCount = receiveInt();
				//���1������Ŀ
				Constant::lastPlayerCardsCount = receiveInt();
				//2���������Ŀ
				Constant::playerCardsCount = receiveInt();
			}

			int cardLength = receiveInt();				//����ʣ���Ƶĳ���
			Constant::pukeRemainNumber = cardLength;
			for(int i=0;i<cardLength;i++)				//����ʣ���Ƶ�ID
			{
				Constant::PUKEARRAY[i]=receiveInt();
			}

			for(int j=0;j<3;j++)
			{
				int card = receiveInt();			//�������ID
				if(card!=100)
				{
					int cardsLength = receiveInt();		//idΪcard����ҳ��Ƶĳ���
					for(int i=0;i<cardsLength;i++)
					{
						if(Constant::playerId==card)	//��ǰ���ID
						{
							Constant::playerCards[i] = receiveInt();

							Constant::playerLength = cardsLength;
						}
						else if(Constant::lastPlayerId==card)
						{
							Constant::lastPlayerCards[i] = receiveInt();
							Constant::lastPlayerLength = cardsLength;
						}else if(Constant::nextPlayerId==card)
						{
							Constant::nextPlayerCards[i] = receiveInt();
							Constant::nextPlayerLength = cardsLength;
						}
					}
				}else
				{
					if(Constant::playerId==card)	//��ǰ���ID
					{
						Constant::playerLength=0;
					}
					else if(Constant::lastPlayerId==card)
					{
						Constant::lastPlayerLength =0;
					}else if(Constant::nextPlayerId==card)
					{
						Constant::nextPlayerLength =0;
					}
				}
			}
			Constant::isDrawChuPai = true;
			Constant::drawCards=true;					//�������˿�
			Constant::drawAlreadyCard=true;				//���Ѿ�������
			Constant::drawVictory=true;					//������ʤ������
		}
	}
}
