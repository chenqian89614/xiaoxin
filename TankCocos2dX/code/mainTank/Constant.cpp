#include "Constant.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include <string>

int Constant::THING_TAG[12]={0,1,2,3,4,4,5,5,6,7,8,9};//�����ӦBatchNode��Tag
double Constant::PI=3.1415926;//Բ����
int Constant::redOrGreen=-1;//��ұ��
int Constant::level=-1;//�ؿ����
int Constant::state=0;//��Ϸ״̬��
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
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(path);
}

void Constant::playMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
	if(!musicFlag)
	{
		return;
	}
	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		(SOUND_PATH+std::string("background.mp3")).c_str(),
		true
	);
}
