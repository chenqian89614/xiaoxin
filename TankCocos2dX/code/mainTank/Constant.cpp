#include "Constant.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include <string>

int Constant::THING_TAG[12]={0,1,2,3,4,4,5,5,6,7,8,9};//物体对应BatchNode的Tag
double Constant::PI=3.1415926;//圆周率
int Constant::redOrGreen=-1;//玩家编号
int Constant::level=-1;//关卡编号
int Constant::state=0;//游戏状态编
int Constant::redX=0;
int Constant::redY=0;
int Constant::greenX=0;
int Constant::greenY=0;
float Constant::redTankAngle=0;
float Constant::greenTankAngle=0;
float Constant::redGunAngle=0;
float Constant::greenGunAngle=0;
int Constant::redGunState=0;
int Constant::greenGunState=0;
int Constant::redHealth=0;
int Constant::greenHealth=0;
int Constant::otherGunState=0;

int Constant::offset=0;
int Constant::score=0;

int Constant::bossNum=0;
int Constant::bossX=0;
int Constant::bossY=0;
bool Constant::bossFlag=false;

std::vector<float> Constant::mainBullet;
std::vector<float> Constant::mainMissile;
std::vector<float> Constant::otherBullet;
std::vector<float> Constant::bossBullet;

std::vector<int> Constant::mapData;
std::vector<int> Constant::mapTree;
std::vector<int> Constant::mapTank;
std::vector<int> Constant::explosion;
std::vector<int> Constant::award;

bool Constant::effectFlag = true;
bool Constant::musicFlag = true;

void Constant::playEffect(const char *path)
{
	if(!effectFlag)
	{
		return;
	}
	//播放音效
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(path);
}

void Constant::playMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
	if(!musicFlag)
	{
		return;
	}
	//播放背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		(SOUND_PATH+std::string("background.mp3")).c_str(),
		true
	);
}
