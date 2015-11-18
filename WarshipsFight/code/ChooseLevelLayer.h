#ifndef _ChooseLevelLayer_H_
#define _ChooseLevelLayer_H_

#include "cocos2d.h"
#include "WarshipsFightSceneManager.h"
using namespace cocos2d;

class ChooseLevelLayer :public Layer
{
public:
	Sprite* wzbgSp;
	WarshipsFightSceneManager* wfsm;
	Sprite* worldMapSp;
	Point worldMapPoint;
	Point currPoint;
	Sprite* levelSp[5];
	Sprite* taskSp;
	Label* jbLabel;
	bool isSelect = false;
	int levelCount = 0;
	static int  levelNum;
	static int enemyBaseLife ;
	static bool bacMusicFlag ;
	static bool froMusicFlag ;
	Sprite* touchSp ;
	bool selecItem = false;
	MenuItemImage* menuItem[5];
	MenuItemImage* musicItem[2];
	int jbIndex = 0 ;

	Sprite3D* ship3DSp;
	bool cjFlag = false;

	Animate* anmiAc[1];
	Sprite* boomSp[3];
	bool PopTaskWdFlag = false;
	void resetBoom0spPosition();
	void resetBoom1spPosition();
	void resetBoom2spPosition();
	//��ʼ����������
	virtual bool init();
	void mapStartAnimation();
	void initLevelSpListenerTouch();
	void initSound();
	void initMenuItem();
	void initBoomFrame();
	//���ò˵���ص�����
	void szCallback();
	//����
	void sjCallback();
	//�ɾ�
	void cjCallback();
	void PopTaskWindow(int levelIndex);
	void setMenuEnabled(bool b);
	void ksMenuCallback();
	void jbMenuCallback();
	void closeMenuCallback();
	void bacMusicMenuCallback();
	void froMusicMenuCallback();
	int myGetIntegerForKey (std::string key);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void backMenuCallback();
	void shipRotationUpdate();
	void levelCallback();
	CREATE_FUNC(ChooseLevelLayer);
};

#endif
