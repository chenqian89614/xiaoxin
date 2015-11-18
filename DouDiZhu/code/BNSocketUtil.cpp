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
		msgLabel->setString("\u8fde\u63a5\u4e2d");//连接中
		new std::thread(&BNSocketUtil::threadConnectTask,ip,port);//开启线程
	}
}

void BNSocketUtil::sendInt(int si)
{
	 send(socketHandle,&si,4,0);//发送int类型
}
//接收字节
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
//接收int类型
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
	hp = gethostbyname(ip);//用域名或主机名获取IP地址
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
//开启接收线程
void* BNSocketUtil::threadReceiveTask()
{
	while(connectFlag)
	{
		//每一轮先接收标志位整数   0-表示数据为整数  1-表示数据为浮点数 2-表示字符串
		int ri = receiveInt();
		if(ri==0)//绘制玩家图像
		{
			//进入游戏的玩家数目
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
					//上一家id编号
					Constant::lastPlayerId = n;
					//每个玩家的id编号
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
					//上一家
					Constant::lastPlayerId = receiveInt();
				}
				else if(Constant::lastPlayerId==n)
				{
					//本家
					Constant::playerId = receiveInt();
					//下一家
					Constant::nextPlayerId = receiveInt();
				}
				else if(Constant::nextPlayerId==n)
				{
					//上一家id编号
					Constant::lastPlayerId = receiveInt();
					//本家
					Constant::playerId = receiveInt();
				}
			}
        }
		else if(ri==1)//当前准备状态
		{
			//readyNum个成员数目
			Constant::readyNum = receiveInt();
			//判断准备玩家的数目
			if(Constant::readyNum==0)//没有玩家准备
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
			else if(Constant::readyNum==3)//准备标志
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
		else if(ri==2)//接收2，表示玩家均已准备
		{
			//接收扑克数量
			int pukeNum = receiveInt();
			//准备接收17张牌,接收完17张牌之后，准备叫地主
			for(int i=0;i<pukeNum;i++)
			{
				Constant::PUKEARRAY[i] = receiveInt();
			}
			//接收扑克完毕，标志位设为true
			Constant::pukeFlag=true;
			Constant::readyFlag=true;
            Constant::drawAct=true;
		}
		else if(ri==3)//牌权
		{
			//第一轮谁叫地主
			int whoOrder = receiveInt();
			Constant::whoFlag = whoOrder;//初始叫地主玩家
			//将上一次的倍数存进oldBeiNum
			Constant::oldBeiNum = Constant::beiNum;
			//接收当前倍数，并显示到主界面
			Constant::beiNum = receiveInt();
			//计数，判断是叫地主或者抢地主
			Constant::landlordCount++;
			//接收每个玩家的抢地主的状态
			Constant::landlordListNum = receiveInt();//3

			for(int i=0;i<Constant::landlordListNum;i++)
			{
				Constant::landlordList[i] = receiveInt();//0-不叫，1-叫，2-不抢，3-抢，4-无
			}

			//menuitem
			Constant::menuItem=true;
		}
		else if(ri==4)//接收地主的最终牌即20张			直走一次
		{
			if(Constant::landlordCount==4)
			{
				Constant::landlordCount++;
			}
			//接收谁是地主,即地主的id
			int landlord=Constant::whoIsLandlord = receiveInt();

			//将上一次的倍数存进oldBeiNum
			Constant::oldBeiNum = Constant::beiNum;
			//接收当前倍数，并显示到主界面
			Constant::beiNum = receiveInt();

			//接收地主扑克数量
			int pukeLandlordNum = receiveInt();
			//准备接收20张牌
			for(int i=0;i<pukeLandlordNum;i++)
			{
				Constant::tempPUKE[i] = receiveInt();
			}
			//收到20张牌 ,标记，用于删除地主字样
			//用于每个玩家界面的背景牌都旋转的标志位
			Constant::clearLandlordState=true;
			Constant::landlordHadPuke = true;
			//接收剩余牌的数目，即三张牌
			int lastPukeNum = receiveInt();
			//准备接收剩余牌的id,即剩余牌在PUKEARRAY[]数组的索引
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
			Constant::deleteMenu=true;		//删除叫地主 抢地租菜单项
			Constant::drawHeadImage=true;	//画地主，农民头像
			Constant::drawLogo=false;		//不画logo
		}
		else if(ri==5)//接收当前牌是否可以出，0-不出，1-可以出
		{
			Constant::whoFlag=receiveInt();			//当前牌权
			Constant::isCanChuPai = receiveInt();	//是否出牌 1为出牌，0为不能出
			Constant::isDrawChuPai = true;
			Constant::isDrawReset = true;
		}
		else if(ri==6)//准备接收当前牌权玩家手牌数目
		{
			//谁有牌权
			Constant::whoFlag = receiveInt();

			//计数，判断抢地主后出牌的次数
			Constant::landlordCount++;
			//将上一次的倍数存进oldBeiNum
			Constant::oldBeiNum = Constant::beiNum;
			//接收当前倍数，并显示到主界面
			Constant::beiNum = receiveInt();

			//接收音效二维数组的行与列,标志位标记为ture
			Constant::effectRow = receiveInt();
			Constant::effectCol = receiveInt();
			if(Constant::effectRow!=-1&&Constant::effectCol!=-1)
			{
				Constant::isCanPlayEffect=true;
			}
			//接收标志位，判断是否绘制“不出”，0-绘制，1-不绘制
			Constant::isBuChu = receiveInt();
			//接收玩家手牌数目的标志1-可以绘制，0-不绘制----下面准备接收
			Constant::drawCardsFlag = receiveInt();
			if(Constant::playerId==0)
			{
				//0玩家手牌数目
				Constant::playerCardsCount = receiveInt();
				//玩家1手牌数目
				Constant::nextPlayerCardsCount = receiveInt();
				//2玩家手牌数目
				Constant::lastPlayerCardsCount = receiveInt();
			}else if(Constant::playerId==1)
			{
				//0玩家手牌数目
				Constant::lastPlayerCardsCount = receiveInt();
				//玩家1手牌数目
				Constant::playerCardsCount = receiveInt();
				//2玩家手牌数目
				Constant::nextPlayerCardsCount = receiveInt();
			}else if(Constant::playerId==2)
			{
				//0玩家手牌数目
				Constant::nextPlayerCardsCount = receiveInt();
				//玩家1手牌数目
				Constant::lastPlayerCardsCount = receiveInt();
				//2玩家手牌数目
				Constant::playerCardsCount = receiveInt();
			}

			int cardLength = receiveInt();				//接收剩余牌的长度
			Constant::pukeRemainNumber = cardLength;
			for(int i=0;i<cardLength;i++)				//接收剩余牌的ID
			{
				Constant::PUKEARRAY[i]=receiveInt();
			}

			for(int j=0;j<3;j++)
			{
				int card = receiveInt();			//接收玩家ID
				if(card!=100)
				{
					int cardsLength = receiveInt();		//id为card的玩家出牌的长度
					for(int i=0;i<cardsLength;i++)
					{
						if(Constant::playerId==card)	//当前玩家ID
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
					if(Constant::playerId==card)	//当前玩家ID
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
			Constant::drawCards=true;					//画本家扑克
			Constant::drawAlreadyCard=true;				//画已经出的牌
//			Constant::isTishi=true;
		}
		else if(ri==7)				//接收提示
		{
			int Tishi= receiveInt();	//1为有提示
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
				Constant::drawCards=true;					//画本家扑克
				Constant::drawTiShi=true;
			}else
			{
				Constant::drawTiShi=false;
                Constant::upCardsCount=0;
			}
		}else if(ri==8)					// 胜利
		{
			//谁有牌权
			Constant::whoFlag = receiveInt();

			int victory=receiveInt();		//胜利 1为地主胜利，0为农民胜利
			//计数，判断抢地主后出牌的次数
			Constant::victory=victory;
			Constant::landlordCount++;
			//将上一次的倍数存进oldBeiNum
			Constant::oldBeiNum = Constant::beiNum;
			//接收当前倍数，并显示到主界面
			Constant::beiNum = receiveInt();

			//接收音效二维数组的行与列,标志位标记为ture
			Constant::effectRow = receiveInt();
			Constant::effectCol = receiveInt();
			if(Constant::effectRow!=-1&&Constant::effectCol!=-1)
			{
				Constant::isCanPlayEffect=true;
			}
			//接收玩家手牌数目的标志1-可以绘制，0-不绘制----下面准备接收
			Constant::drawCardsFlag = receiveInt();
			if(Constant::playerId==0)
			{
				//0玩家手牌数目
				Constant::playerCardsCount = receiveInt();
				//玩家1手牌数目
				Constant::nextPlayerCardsCount = receiveInt();
				//2玩家手牌数目
				Constant::lastPlayerCardsCount = receiveInt();
			}else if(Constant::playerId==1)
			{
				//0玩家手牌数目
				Constant::lastPlayerCardsCount = receiveInt();
				//玩家1手牌数目
				Constant::playerCardsCount = receiveInt();
				//2玩家手牌数目
				Constant::nextPlayerCardsCount = receiveInt();
			}else if(Constant::playerId==2)
			{
				//0玩家手牌数目
				Constant::nextPlayerCardsCount = receiveInt();
				//玩家1手牌数目
				Constant::lastPlayerCardsCount = receiveInt();
				//2玩家手牌数目
				Constant::playerCardsCount = receiveInt();
			}

			int cardLength = receiveInt();				//接收剩余牌的长度
			Constant::pukeRemainNumber = cardLength;
			for(int i=0;i<cardLength;i++)				//接收剩余牌的ID
			{
				Constant::PUKEARRAY[i]=receiveInt();
			}

			for(int j=0;j<3;j++)
			{
				int card = receiveInt();			//接收玩家ID
				if(card!=100)
				{
					int cardsLength = receiveInt();		//id为card的玩家出牌的长度
					for(int i=0;i<cardsLength;i++)
					{
						if(Constant::playerId==card)	//当前玩家ID
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
					if(Constant::playerId==card)	//当前玩家ID
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
			Constant::drawCards=true;					//画本家扑克
			Constant::drawAlreadyCard=true;				//画已经出的牌
			Constant::drawVictory=true;					//画最后的胜利动画
		}
	}
}
