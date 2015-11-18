#ifndef  _PhyObject_H_
#define  _PhyObject_H_
#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

//几个像素等于1米
#define pixToMeter 5

//物理和绘制封装类基类
class PhyObject
{
	public:
	 //此物件的id
	 std::string* poId;
	 //绘制刚体用的精灵
     Sprite* dSp;
     //物体对应的刚体
     b2Body* body;
     PhyObject
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
    );
    virtual void refresh();
};


//物理和绘制封装类——矩形
class RectPhyObject:public PhyObject
{
  public:
	RectPhyObject
	(
		std::string* id,
		bool isStaticIn,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
    );
};

//物理和绘制封装类——圆形
class CirclePhyObject:public PhyObject
{
  public:
	CirclePhyObject
	(
		std::string* id,
		bool isStaticIn,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
    );
};

//物理和绘制封装类——多边形
class PolygonPhyObject:public PhyObject
{
  public:
	PolygonPhyObject
	(
		std::string* id,
		bool isStaticIn,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
    );
};

//物理和绘制封装类——线段类型
class EdgePhyObject:public PhyObject
{
  public:
	EdgePhyObject
	(
		std::string* id,
		bool isStaticIn,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
    );
	void refresh();
  private:
	b2Rot r;
};
#endif
