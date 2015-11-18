#ifndef _UpgradeLayer_H_
#define _UpgradeLayer_H_

#include "cocos2d.h"
#include "WarshipsFightSceneManager.h"
using namespace cocos2d;

class UpgradeLayer : public cocos2d::Layer
{
public:
	WarshipsFightSceneManager* wfsm;
	Sprite3D* weapon;
	Sprite* selectToolSp;
	MenuItemImage* shipMenu[5];
	LabelAtlas* moneyLabel;
	int restMoney;
	int moneyCount;
	LabelAtlas* nMoneyLabel ;
	Sprite* wqSp;
	std::string selectShipst = "SHIPZERO";
	Sprite* ddjjSp[2];
	int deltaAngleY = 0;
	int daodanIndex = 1;
	Animate* anmiAc;
	Sprite* toolBarSp;
	Sprite* toolSZJSp;
	Sprite* toolPacSp;
	Sprite* toolGGSp;
	Sprite* toolGG1Sp;

	int rotation[3];
	//ѡ�ед����
	int menuIndex = 0;
	Point tempCoinPoint;
	bool decMoneyFlag = false;
	int creatCoinNum = 0;
	Sprite3D* stars3D[4];
	int starsNum = 1;
	bool starsRotationFlag = false;
	int starsRotation =0;
	//��ʼ���ķ���
	virtual bool init();
	void initShipMenu();
	void disWeaponStar(std::string key);
	void direcMenuCallback();
	void shipZeroCallback();
	void shipOneCallback();
	void shipTwoCallback();
	void shipThreeCallback();
	void shipFourCallback();
	void sjwqMenuCallback();
	void weaponStageUpdate();
	void updateDaoDan(int index);
	void backMenuCallback();
	void sjRunAction();
	void toolGGSpRunAction();
	void openSZJ();
	void removePacSp();
	void addPacSp();
	void rotateGG1();
	void createCoin();
	void liangPlist();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(UpgradeLayer);
};
#endif
