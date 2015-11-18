#include "PhyObject.h"

//data是刚体数据,单位为像素
PhyObject:: PhyObject
(
		std::string* idIn,
    	bool isStaticIn,
    	Layer* layer,
    	b2World* world,
    	std::string pic,
    	float* data,
    	float density,
    	float friction,
    	float restitution
)
{
	this->poId=idIn;
}

//更新精灵位置、姿态信息的方法
void PhyObject::refresh()
{
    //获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();
	//获取精灵对应的刚体位置
	b2Vec2 position=body->GetPosition();
	//获取精灵对应的刚体姿态角
	float angle=body->GetAngle();
	//设置精灵的位置
	dSp->setPosition
	(
		Point
		(
			origin.x+visibleSize.width/2+position.x*pixToMeter,
			origin.y+visibleSize.height/2+position.y*pixToMeter
		)
	);
	//设置精灵的姿态
	dSp->setRotation(-angle*180.0/b2_pi);
}
