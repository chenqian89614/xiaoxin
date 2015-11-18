#include "PhyObject.h"

//data是刚体数据,单位为像素
//data[0],[1] 一个顶点的坐标  [2],[3] 另一个顶点的坐标
EdgePhyObject::EdgePhyObject
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
	float positionX=(data[0]+data[2])/2;//计算刚体中心位置的X坐标
	float positionY=(data[1]+data[3])/2;//计算刚体中心位置的Y坐标
	//设置刚体位置
	bodyDef.position.Set(positionX/pixToMeter,positionY/pixToMeter);
	//创建刚体对象
	body = world->CreateBody(&bodyDef);
	//在刚体中记录对应的包装对象指针
	body->SetUserData(id);

	//创建线形物体类对象
	b2EdgeShape shape;
	//设置位置
	shape.Set(b2Vec2((data[0]-positionX)/pixToMeter,(data[1]-positionY)/pixToMeter), b2Vec2((data[2]-positionX)/pixToMeter,(data[3]-positionY)/pixToMeter));

	if(!isStaticIn)
	{
		//创建刚体物理描述
		b2FixtureDef fixtureDef;
		//设置形状
		fixtureDef.shape = &shape;
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
		body->CreateFixture(&shape, 0.0f);
	}

	dSp = Sprite::create(pic);
	//将精灵添加到布景中
	layer->addChild(dSp, 1);
	//获取精灵的尺寸
	Size size=dSp->getContentSize();
	
	b2Vec2 v1=shape.m_vertex1;//v1赋值为线形第一个顶点
	b2Vec2 v2=shape.m_vertex2;//v2赋值为线形第二个顶点
	b2Vec2 v3=v2-v1;	
	
	//计算出精灵X方向缩放比
	float scaleX=v3.Length()*pixToMeter/size.width;
	//计算出精灵Y方向缩放比
	float scaleY=3/size.height;
	//设置精灵X方向缩放比
	dSp->setScaleX(scaleX);
	//设置精灵Y方向缩放比
	dSp->setScaleY(scaleY);
	r.s=(v2.y-v1.y)/v3.Length();
	r.c=(v2.x-v1.x)/v3.Length();
}


void EdgePhyObject::refresh()
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
	dSp->setRotation(-angle*180.0/b2_pi-r.GetAngle()*180.0/b2_pi);
}
