#ifndef _WarShipObject_H_
#define _WarShipObject_H_

#include "cocos2d.h"
using namespace cocos2d;

class WarShipObject :public cocos2d::Sprite
{
public :
	WarShipObject(int selectNum,int shipType,Point point);
	static WarShipObject* create(std::string path,Point point,int selectNum, int shipType);
	Point startPoint ;
	int shipType ;//我方船只-------1，敌方船只-----2
	int shipNum ;
	int lifeValue = 100;
	int attackPower ;
	int speed = 0;
	std::vector<Point>* warShipPath;
	int rotation = 0;
	//若被选中则为1，不选中则为0
	int state = 0;
	int itemCount = 0;
	int initRow;
	int initCol;
	int targetRow = -1 ;
	int targetCol = -1 ;
	int sequence[8][2];
	int enemyShipTargetRow;
	int enemyShipTargetCol;
	int weapon0CoolTime = 0;
	int weapon1CoolTime = 0;
	bool isMoved = true;
	int destroyESN = 0;
	int junxian = 0;
	bool isDie = false;
	Point touchPointToRowCol(Point point);
};
#endif
