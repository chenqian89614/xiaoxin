#include "BNJoyStick.h"
#include "Constant.h"
#include <cmath>

BNJoyStick::BNJoyStick(){}

BNJoyStick::~BNJoyStick(){}

//获取矩形区域
Rect BNJoyStick::getRect()
{
	//获取纹理图的尺寸大小
	auto s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

//判断触点的位置方法
bool BNJoyStick::containsTouchLocation(Touch* touch)
{
	//判断触摸点是否在矩形区域内
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

//每次精灵进入时被回调
void BNJoyStick::onEnter()
{
	//调用父类的onEnter方法
	Sprite::onEnter();

	//创建一个单点触控监听
	auto listener = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listener->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
    listener->onTouchBegan = CC_CALLBACK_2(BNJoyStick::onTouchBegan, this);
    //触摸移动时回调onTouchMoved方法
    listener->onTouchMoved = CC_CALLBACK_2(BNJoyStick::onTouchMoved, this);
    //触摸结束时回调onTouchEnded方法
    listener->onTouchEnded = CC_CALLBACK_2(BNJoyStick::onTouchEnded, this);
    //添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//每次精灵退出时被回调
void BNJoyStick::onExit()
{
	//调用父类的onExit方法
	Sprite::onExit();
}

//开始触控事件的处理方法
bool BNJoyStick::onTouchBegan(Touch* touch, Event* event)
{
	if (Constant::state!=2) return false;
    if ( !containsTouchLocation(touch)) return false;
    touchFlag=true;
    return true;
}

//触控移动事件的处理方法
void BNJoyStick::onTouchMoved(Touch* touch, Event* event)
{
	//限制移动事件，没两次才调用一次，以提高游戏速度
	if(yhCount%2==0)
	{
		//获取触控点的位置
		Point tp = touch->getLocation();
		//调用calCenterPosition方法
		calCenterPosition(tp.x,tp.y);
		yhCount=0;
	}
	yhCount++;
}

//触控结束事件的处理方法
void BNJoyStick::onTouchEnded(Touch* touch, Event* event)
{
	//重置标志位
	touchFlag=false;
	//调用calCenter方法
	calCenter();
	//重置摇杆中心横坐标
	vx=0;
	//重置摇杆中心纵坐标
	vy=0;
}

//计算摇杆中心在纹理图的坐标方法
void BNJoyStick::calCenterPosition(float tx,float ty)
{
	//获取精灵锚点在屏幕内的位置
	Point p=getPosition();
	//获取精灵锚点坐标
	Point a=getAnchorPoint();
	//获取纹理图的尺寸大小
	Size s=getTexture()->getContentSize();
	//矩形区域中心的横坐标
	float centerX=p.x-a.x*s.width+s.width/2.0f;
	//矩形区域中心的纵坐标
	float centerY=p.y-a.y*s.height+s.height/2.0f;
	//矩形区域内触控点到中心的横坐标
	float dx=tx-centerX;
	//矩形区域内触控点到中心的纵坐标
	float dy=ty-centerY;

	//当前坐标与坐标原点的距离
	float spanP2=dx*dx+dy*dy;
	//判断当前坐标点的距离是否超出范围
	if(spanP2>rRange*rRange)
	{
		float span=sqrt(spanP2);
		//设置矩形区域内的横坐标
		dx=dx*rRange/span;
		//设置矩形区域内的纵坐标
		dy=dy*rRange/span;
	}
	//设置摇杆移动的横坐标
	vx=dx;
	//设置摇杆移动的纵坐标
	vy=dy;

	//设置摇杆中心摇杆坐标
	centerPoint->setPosition(Point(dx+s.width/2.0f,dy+s.height/2.0f));
}

//设置中心摇杆位置及获取半径
void BNJoyStick::calCenter()
{
	if(!centerPoint)
	{
		return;
	}
	//获取纹理图的尺寸大小
	Size s=getTexture()->getContentSize();
	//获取纹理图的中心摇杆的x坐标
	float centerXTemp=s.width/2.0f;
	//获取纹理图的中心摇杆的y坐标
	float centerYTemp=s.height/2.0f;
	//设置中心摇杆的位置
    centerPoint->setPosition(Point(centerXTemp,centerYTemp));
    //获取纹理图半径
    rRange=s.width/2.0f;
}

//百纳摇杆的创建方法
BNJoyStick* BNJoyStick::create(const std::string& basefilename,const std::string& centerfilename)
{
	//创建一个百纳摇杆对象
	BNJoyStick *bnjs = new BNJoyStick();
	//判断精灵是否存在并初始化
	if (bnjs && bnjs->initWithFile(basefilename))
	{
		//自动释放
		bnjs->autorelease();
		//初始化摇杆x坐标
		bnjs->vx=0;
		//初始化摇杆y坐标
		bnjs->vy=0;
		//创建一个精灵对象
		bnjs->centerPoint=Sprite::create(centerfilename);
		//将精灵添加到摇杆布景中
		bnjs->addChild(bnjs->centerPoint, 1,0);
		//调用calCenter方法
		bnjs->calCenter();
		return bnjs;
	}
	CC_SAFE_DELETE(bnjs);
	return nullptr;
}

