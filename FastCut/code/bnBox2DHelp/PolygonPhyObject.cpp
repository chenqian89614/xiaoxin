#include "PhyObject.h"

#include <string.h>

//data是刚体数据,单位为像素
//对于多边形  0-x 1-y 2-count 3...-xyxyxyxy
PolygonPhyObject:: PolygonPhyObject
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
):PhyObject(id,isStaticIn,layer,world,pic,data,density,friction,restitution)
{
    //创建刚体描述
	b2BodyDef bodyDef;
	//设置为可运动刚体
	if(!isStaticIn)
	{
		bodyDef.type = b2_dynamicBody;
	}
	//设置刚体位置
	bodyDef.position.Set(data[0]/pixToMeter,data[1]/pixToMeter);
	//创建刚体
	body = world->CreateBody(&bodyDef);
	//在刚体中记录对应的包装对象指针
	body->SetUserData(id);

	//创建可以运动的刚体的形状
	int vcount=((int)data[2]);
	//b2Vec2 verteics[vcount];
//	for(int i=0;i<vcount;i++)
//	{
//		verteics[i].Set(data[i*2+3]/pixToMeter,data[i*2+4]/pixToMeter);
//	}
	int32 count=vcount;

	b2PolygonShape dynamicBox;
//	dynamicBox.Set(verteics, count);

	if(!isStaticIn)
	{
		//创建刚体物理描述
		b2FixtureDef fixtureDef;
		//设置形状
		fixtureDef.shape = &dynamicBox;
		//设置密度
		fixtureDef.density = density;
		//设置摩擦系数
		fixtureDef.friction = friction;
		//设置恢复系数
		fixtureDef.restitution=restitution;
		//将物理描述与刚体结合
		body->CreateFixture(&fixtureDef);
	}
	else
	{
		//将形状与刚体结合
		body->CreateFixture(&dynamicBox, 0.0f);
	}

	dSp = Sprite::create(pic);
	//将精灵添加到布景中
	layer->addChild(dSp, 1);
	dSp->setAnchorPoint(Point(0, 0));
}
