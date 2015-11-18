#ifndef _Weapon_H_
#define _Weapon_H_
#include "cocos2d.h"
#include "WarShipObject.h"
using namespace cocos2d;
class Weapon :public cocos2d::Sprite3D
{
public :
	Weapon(int launchForm);
	static Weapon* create(int index,Point p,int launchForm);
	WarShipObject* weaponFromShip;
	bool isMove = false;
	Point startPoint;
	Point targetPoint;
	float currX = 0;
	float currZ = 0;
	float currY = 0;
	float a = 0;
	float k = 0;
	float b = 0;
	float rotationZ = 0;
	float degreeB = 0;
	bool forwardLeft = true;
	float midy = 0;
	float midx = 0;
	int count = 0;
	int step = 0;
	int power = 0;
	//记录导弹发射方---1为玩家---2为敌方
	int launchForm = 0;
};
#endif
