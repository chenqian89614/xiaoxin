#include "cocos2d.h"
#include "WarShipObject.h"
#include "ChooseLevelLayer.h"
using namespace cocos2d;

WarShipObject::WarShipObject(int selectNum,int shipType,Point point)
{
	speed = (12-selectNum)*4 + 10;
	this->startPoint = point;
	this->shipType = shipType;
	CCLOG("shipType = %d",shipType);
	if(selectNum == 1)
	{
		itemCount = 1;
	}else
	{
		itemCount = 2;
	}
	Point RC = touchPointToRowCol(point);
	if(shipType == 1)
	{
		initRow = 24;
		initCol = 70;
		this->attackPower = (selectNum+1) * 100;
		this->lifeValue = (selectNum+1)*200;
	}else if(shipType == 2)
	{
		initRow = RC.y;
		initCol = RC.x;
		this->attackPower = (selectNum+1) * 50;
		this->lifeValue = (selectNum+1)*100+ChooseLevelLayer::enemyBaseLife ;
	}
	shipNum = selectNum;
}
WarShipObject* WarShipObject::create(std::string path,Point point,int selectNum,int shipType)
{
	WarShipObject* wso = new WarShipObject(selectNum,shipType,point);
	wso->initWithFile(path);
	wso->setPosition(point);
	return wso;
}
Point WarShipObject::touchPointToRowCol(Point point)
{
	Point resultPoint;
	int row = point.x/16;
	int col = (768-point.y)/16;
	resultPoint = Point(row,col);
	return resultPoint;
}
