#include "HelpLayer.h"
#include "SimpleAudioEngine.h"
#include "WelcomeLayer.h"
#include "ChoiceLayer.h"
#include "AppConstant.h"//常量类
using namespace std;
using namespace cocos2d;
HelpLayer::~HelpLayer()
{

}

bool HelpLayer::init()
{
	//调用父类的初始化
	if ( !Layer::init() )
	{
		return false;
	}
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto backItem = MenuItemImage::create
	(
			pic_PATH+"back.png",
			pic_PATH+"back.png",
			CC_CALLBACK_0(HelpLayer::onBack, this)//点击时执行的回调方法
	);
	backItem->setPosition(
			Point(
				origin.x - backItem->getContentSize().width/2+520,	//X坐标
				origin.y -backItem->getContentSize().height/2+940		//Y坐标
			)
			);
	//创建菜单对象
	auto backMenu = Menu::create(backItem, NULL);
	//设置菜单位置
	backMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(backMenu, 1);
	 //创建一个精灵对象，包含bg.png图片
	bgSprite = Sprite::create(pic_PATH+"bg.jpg");
	//设置精灵对象的位置
	bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//将精灵添加到布景中
	this->addChild(bgSprite, 0);

	for(int i=0;i<3;i++)
	{
		spIntro[i] = Sprite::create(helpPic_PATH+StringUtils::format("dibanHelp%d.png",i));//创建显示精灵
		spIntro[i]->setAnchorPoint(Point(0,0));//设置显示精灵锚点
		spIntro[i]->setPosition(0+i*350,0);//设置显示精灵位置
		TBGPoint[i] = spIntro[i]->getPosition();//获取显示精灵位置
	}

	Point pp[4];//创建一个坐标点数组，用于描绘多边形
	pp[0] = Point(0, 0);//设置坐标点数值
	pp[1] = Point(350, 0);//设置坐标点数值
	pp[2] = Point(350, 622);//设置坐标点数值
	pp[3] = Point(0, 622);//设置坐标点数值
	Color4F green(0, 1, 0, 0);//多边形填充颜色
	Color4F red(1, 0, 0, 0);//多边形边框颜色
	//创建剪裁用DrawNode
	DrawNode* shape = DrawNode::create();
	shape->drawPolygon(pp ,4, green, 1,red);//绘制多边形
	//创建剪裁节点
	ClippingNode* clipper=ClippingNode::create();
	//设置剪裁模板
	clipper->setStencil(shape);
	//设置被剪裁节点
	for(int j=0; j<3; j++)
	{
		clipper->addChild(spIntro[j],1);//将显示精灵添加到剪裁节点中
	}
	clipper->setPosition(Point(90,200));//设置剪裁节点位置
	//将被剪裁节点放置到层中
	this->addChild(clipper, 0);

	for(int i=0;i<3;i++)
	{
		if(i == 0)
		{
			bSprite[i] = Sprite::create(helpPic_PATH+"white.png");//创建白点精灵
		}else
		{
			bSprite[i] = Sprite::create(helpPic_PATH+"black.png");//创建黑点精灵
		}
		bSprite[i]->setPosition(Point(230+i*30,135));//设置黑白点精灵位置
		this->addChild(bSprite[i],4);//将黑白点精灵添加到布景中
	}
	//创建一个单点触摸监听
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerTouch->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchBegan = CC_CALLBACK_2(HelpLayer::onMyTouchBegan, this);
	//开始触摸时回调onTouchMoved方法
	listenerTouch->onTouchMoved = CC_CALLBACK_2(HelpLayer::onMyTouchMoved, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouch->onTouchEnded = CC_CALLBACK_2(HelpLayer::onMyTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, spIntro[0]);
	for(int i=0;i<3;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch->clone(), spIntro[i]);
	}

	return true;
}

bool HelpLayer::onMyTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(	event->getCurrentTarget());//获取当前触摸对象，并转化为精灵类型
	currPoint = touch->getLocation();//当前触摸点位置
	Point location = target->convertToNodeSpace(currPoint);//获取当前坐标
	auto size = target->getContentSize();			//获取精灵的大小
	auto rect = Rect(0, 0, size.width, size.height);//创建一个矩形对象，其大小与精灵相同
	if( rect.containsPoint(location)){	//判断触摸点是否在目标的范围内
		return true;
	}else{
		return false;
	}
}

void HelpLayer::onMyTouchMoved(Touch *touch, Event *event)
{
	for(int i=0;i<3;i++)
	{
		spIntro[i]->setPosition(
				TBGPoint[i].x+(touch->getLocation().x-currPoint.x),
				TBGPoint[i].y
		);
	}
}

void HelpLayer::onMyTouchEnded(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(				//获取的当前触摸的对象，并转化为精灵类型
									event->getCurrentTarget());
	Point location = target->convertToNodeSpace(touch->getLocation());//获取当前坐标
	for(int i=0;i<3;i++)
	{
		TBGPoint[i] = spIntro[i]->getPosition();
	}

	float jlMin = MAX_INT;

	for(int i=0;i<3;i++)
	{
		if(fabs(TBGPoint[i].x)<jlMin)
		{
			jlMin = fabs(TBGPoint[i].x);

			currIntroIndex = i;
		}
	}


	int tempNum = currIntroIndex;
	for(int i=0;i<2;i++)
	{
		if(tempNum == 3)
		{
			tempNum = 0;
		}
		spIntro[tempNum]->setPosition(
						0+i*350,
						spIntro[tempNum]->getPosition().y
				);
		tempNum ++;
	}

	tempNum =currIntroIndex;
	for(int i=0;i<2;i++)
	{
		if(tempNum == -1)
		{
			tempNum = 2;
		}
		spIntro[tempNum]->setPosition(
						0-i*350,
						spIntro[tempNum]->getPosition().y
				);
		tempNum --;
	}

	for(int i=0;i<3;i++)
	{
		TBGPoint[i] = spIntro[i]->getPosition();
	}
	setBWPosition();
}

void HelpLayer::setBWPosition()
{
	int tempNUM  = 1;
	for(int i=0;i<3;i++)
	{
		if(i == currIntroIndex)
		{
			bSprite[0]->setPosition(Point(230+i*30,135));
		}else
		{
			bSprite[tempNUM ]->setPosition(Point(230+i*30,135));
			tempNUM  ++;
		}
	}
}

void HelpLayer::onBack()
{
	if(ChoiceLayer::isSound)
	{
		wl->playSwitchSound();//播放切换音效
	}
	gsm->goWelcomeScene();
}
