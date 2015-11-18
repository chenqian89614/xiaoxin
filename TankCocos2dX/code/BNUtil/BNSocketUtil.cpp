#include "BNSocketUtil.h"
#include "Constant.h"
#include "SelectLayer.h"
#include "AppMacros.h"

int BNSocketUtil::socketHandle=0;
bool BNSocketUtil::connectFlag=0;
int BNSocketUtil::okFlag=0;
int BNSocketUtil::selectFlag=0;
int BNSocketUtil::fullFlag=0;
int BNSocketUtil::mainBulletFlag=0;
int BNSocketUtil::mainMissileFlag=0;
int BNSocketUtil::otherBulletFlag=0;
int BNSocketUtil::mapDataFlag=0;
int BNSocketUtil::dataFlag=0;
int BNSocketUtil::bossBulletFlag=0;
int BNSocketUtil::bossNewFlag=0;
int BNSocketUtil::bossFlag=0;
int BNSocketUtil::stateFlag=0;
int BNSocketUtil::mapTreeFlag=0;
int BNSocketUtil::explosionFlag=0;
int BNSocketUtil::mapTankFlag=0;
int BNSocketUtil::awardFlag=0;
int BNSocketUtil::exitFlag=0;
int BNSocketUtil::clearFlag=0;
int BNSocketUtil::tankFlag=0;
int BNSocketUtil::bossNumber=-1;

void BNSocketUtil::connect(const char* ip, unsigned short port)
{
	if(!connectFlag)
	{
		new std::thread(&BNSocketUtil::threadConnectTask,ip,port);
	}
}

void BNSocketUtil::sendInt(int si)
{
	 send(socketHandle,&si,4,0);
}

void BNSocketUtil::sendFloat(float sf)
{
	send(socketHandle,&sf,4,0);
}

void BNSocketUtil::sendStr(const char* str,int len)
{
	sendInt(len);
	send(socketHandle,str,len,0);
}

char* BNSocketUtil::receiveBytes(int len)
{
	char* result=new char[len];

	int status=0;
	status=recv(socketHandle, result, len, 0);
	if(status==0)
	{
		return "close";
	}

	while(status!=len)
	{
		int index=status;
		char b[len-status];
		int count=recv(socketHandle, b, len-status, 0);
		if(count==0)
		{
			return "close";
		}
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

int BNSocketUtil::receiveInt()
{
	char* a=receiveBytes(4);
	if(strcmp(a,"close")==0)
	{
		return 0;
	}
	int ri;

	memset(&ri, 0, sizeof(ri));
	memcpy((char*)(&ri), a,4);
    delete a;
	return ri;
}

float BNSocketUtil::receiveFloat()
{
	char* a=receiveBytes(4);
	if(strcmp(a,"close")==0)
	{
		return 0;
	}
	float ri;
	memset(&ri, 0, sizeof(ri));
	memcpy((char*)(&ri), a,4);
	delete a;
	return ri;
}

char* BNSocketUtil::receiveStr()
{
	int len=receiveInt();
	if(len==0)
	{
		return "0";
	}
	char* a=receiveBytes(len);
	if(strcmp(a,"close")==0)
	{
		return "0";
	}
	char* result=new char[len+1];
	memset(result, 0, len+1);
	memcpy(result, a,len);
	return result;
}

void  BNSocketUtil::closeConnect()
{
	if(connectFlag)
	{
		BNSocketUtil::sendStr("<#EXIT#>",8);
		::close(socketHandle);
		connectFlag=false;
	}else
	{
		TankSceneManager::backMenuLayer();
	}
}

void* BNSocketUtil::threadConnectTask(const char* ip, unsigned short port)
{
	struct sockaddr_in sa;
	struct hostent* hp;
	hp = gethostbyname(ip);
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
	connectFlag=true;
	new std::thread(&BNSocketUtil::threadReceiveTask);
	sendStr("<#CONNECT#>", 11);
}

void* BNSocketUtil::threadReceiveTask()
{
	while(connectFlag)
	{
		char* data=receiveStr();
		CCLOG("data=%s",data);
		if(strcmp(data,"<#OK#>")==0)//连接成功信息
		{
			Constant::redOrGreen=receiveInt();
			Constant::level=receiveInt();
			CCLOG("data=%s",data);
			okFlag = 1;
		}
		else if(strcmp(data,"<#FULL#>")==0)//服务器满
		{
			::close(socketHandle);
			connectFlag=false;
			TankSceneManager::backMenuLayer();
		}
		else if(strcmp(data,"<#SELECT2#>")==0)//关卡信息
		{
			Constant::level=receiveInt();
			selectFlag = 1;
		}
		else if(strcmp(data,"<#GAME_BULLET#>")==0)//主坦克子弹
		{
			Constant::redGunState=(receiveInt()==0)?0:1;
			Constant::greenGunState=(receiveInt()==0)?0:1;

			int length=receiveInt();
			float *temp=new float[length];
			for(int i=0;i<length;i++)
			{
				temp[i]=receiveFloat();
			}
			if(mainBulletFlag == 0)
			{
				Constant::mainBullet.clear();
				for(int i=0;i<length;i++)
				{
					Constant::mainBullet.push_back(temp[i]);
				}
				mainBulletFlag = 1;
			}
		}
		else if(strcmp(data,"<#GAME_MISSILE#>")==0)//主坦克导弹
		{
			int missileFlag=receiveInt();
			if(missileFlag==1)
			{
                Constant::playEffect((PIC_PATH+std::string("rocket_shoot2.mp3")).c_str());
			}
			int length=receiveInt();
			float *temp=new float[length];
			for(int i=0;i<length;i++)
			{
				temp[i]=receiveFloat();
			}
			if(mainMissileFlag == 0)
			{
				Constant::mainMissile.clear();
				for(int i=0;i<length;i++)
				{
					Constant::mainMissile.push_back(temp[i]);
				}
				mainMissileFlag = 1;
			}
		}
		else if(strcmp(data,"<#GAME_OTHERBULLET#>")==0)//地方坦克子弹
		{
			Constant::otherGunState=(receiveInt()==0)?0:1;
			int length=receiveInt();
			float *temp=new float[length];
			for(int i=0;i<length;i++)
			{
				temp[i]=receiveFloat();
			}
			if(otherBulletFlag==0)
			{
				Constant::otherBullet.clear();
				for(int i=0;i<length;i++)
				{
					Constant::otherBullet.push_back(temp[i]);
				}
				otherBulletFlag = 1;
			}
		}
		else if(strcmp(data,"<#GAME_MAP#>")==0)//地图数据
		{
			int length=receiveInt()-1;
			Constant::offset=receiveInt();//接收地图偏移量
			int *temp=new int[length];
			for(int i=0;i<length;i++)
			{
				temp[i]=receiveInt();
			}
			if(mapDataFlag==0)
			{
				Constant::mapData.clear();
				for(int i=0;i<length;i++)
				{
					Constant::mapData.push_back(temp[i]);
				}
				mapDataFlag = 1;
			}
		}
		else if(strcmp(data,"<#GAME_DATA#>")==0)
		{
			Constant::redHealth=receiveInt();
			Constant::greenHealth=receiveInt();
			Constant::score=receiveInt();
			dataFlag = 1;
		}
		else if(strcmp(data,"<#GAME_BOSS#>")==0)
		{
			Constant::bossNum=receiveInt();
			Constant::bossX=receiveInt();
			Constant::bossY=receiveInt();
			Constant::bossFlag=(receiveInt()!=0);
			if(Constant::bossNum!=bossNumber)//判断boss是否需要创建
			{
				bossNumber=Constant::bossNum;
				bossNewFlag = 1;
			}
			int bulletFlag=receiveInt();
			if(bulletFlag==1)
			{
				int length=receiveInt();
				float *temp=new float[length];
				for(int i=0;i<length;i++)
				{
					temp[i]=receiveFloat();
				}
				if(bossBulletFlag==0)
				{
					Constant::bossBullet.clear();
					for(int i=0;i<length;i++)
					{
						Constant::bossBullet.push_back(temp[i]);
					}
					bossBulletFlag = 1;
				}
			}
			bossFlag = 1;
		}
		else if(strcmp(data,"<#GAME_GAMESTATE#>")==0)
		{
			Constant::state=receiveInt();
			stateFlag = 1;
		}
		else if(strcmp(data,"<#GAME_TREE#>")==0)
		{
			int length=receiveInt();
			int *temp=new int[length];
			for(int i=0;i<length;i++)
			{
				temp[i]=receiveInt();
			}
			if(mapTreeFlag==0)
			{
				Constant::mapTree.clear();
				for(int i=0;i<length;i++)
				{
					Constant::mapTree.push_back(temp[i]);
				}
				mapTreeFlag = 1;
			}
		}
		else if(strcmp(data,"<#GAME_EXPLOSION#>")==0)
		{
			int length=receiveInt();
			int *temp=new int[length];
			for(int i=0;i<length;i++)
			{
				temp[i]=receiveInt();
                if(temp[i]==1)
                {
                    Constant::playEffect((PIC_PATH+std::string("grenada.mp3")).c_str());
                }
			}
			if(explosionFlag==0)
			{
				Constant::explosion.clear();
				for(int i=0;i<length;i++)
				{
					Constant::explosion.push_back(temp[i]);
				}
				explosionFlag = 1;
			}
		}
		else if(strcmp(data,"<#GAME_OTANK#>")==0)
		{
			int length=receiveInt();
			int *temp=new int[length];
			for(int i=0;i<length;i++)
			{
				temp[i]=receiveInt();
			}
			if(mapTankFlag==0)
			{
				Constant::mapTank.clear();
				for(int i=0;i<length;i++)
				{
					Constant::mapTank.push_back(temp[i]);
				}
				mapTankFlag = 1;
			}
		}
		else if(strcmp(data,"<#GAME_TANK#>")==0)
		{
			int redX=receiveInt();
			int redY=receiveInt();
			int greenX=receiveInt();
			int greenY=receiveInt();
			float redTankAngle=receiveFloat();
			float greenTankAngle=receiveFloat();
			float redGunAngle=receiveFloat();
			float greenGunAngle=receiveFloat();
			if(tankFlag == 0)
			{
				Constant::redX=redX;
				Constant::redY=redY;
				Constant::greenX=greenX;
				Constant::greenY=greenY;
				Constant::redTankAngle=redTankAngle;
				Constant::greenTankAngle=greenTankAngle;
				Constant::redGunAngle=redGunAngle;
				Constant::greenGunAngle=greenGunAngle;
				CCLOG("receiveTank");
				tankFlag = 1;
			}
		}
		else if(strcmp(data,"<#GAME_AWARD#>")==0)
		{
			int length=receiveInt();
			int *temp=new int[length];
			for(int i=0;i<length;i++)
			{
				temp[i]=receiveInt();
			}
			if(awardFlag==0)
			{
				Constant::award.clear();
				for(int i=0;i<length;i++)
				{
					Constant::award.push_back(temp[i]);
				}
				awardFlag = 1;
			}
		}
		else if(strcmp(data,"<#EXIT#>")==0)
		{
			Constant::state=0;
			exitFlag = 1;
		}
		else if(strcmp(data,"<#VICTORY#>")==0)
		{
			Constant::state=0;
			stateFlag = 1;
		}
		else if(strcmp(data,"<#CLEAR#>")==0)
		{
			clearFlag = 1;
		}
		else if(strcmp(data,"0")==0)
		{
			TankSceneManager::backMenuLayer();
			break;
		}
	}
}

