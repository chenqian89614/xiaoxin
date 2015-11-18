#include "SetLayer.h"
#include "SimpleAudioEngine.h"
#include "WelcomeLayer.h"
#include "ChoiceLayer.h"
#include "SetUtil.h"
#include "AppConstant.h"
using namespace std;
using namespace cocos2d;
int SetLayer::bgIdx=0;
int SetLayer::mark1Idx=0;
int SetLayer::mark2Idx=0;
SetLayer::~SetLayer()
{

}

bool SetLayer::init()
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
	createBgSp(bgIdx);//创建背景精灵对象
	//设置背景精灵位置
	bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bgSprite,0);


	createRound1MarkSp(mark1Idx);//创建第一关标记精灵对象
	round1Marksprite->setScale(1.6);//设置精灵对象缩放比
	if(bgIdx==0)//根据索引选择系列
	{
		round1Marksprite->setPosition(Point(origin.x+200,origin.y+610));//设置精灵位置
	}else if(bgIdx==1)
	{
		round1Marksprite->setPosition(Point(origin.x+350,origin.y+560));//设置精灵位置
	}else if(bgIdx==2)
	{
		round1Marksprite->setPosition(Point(origin.x+200,origin.y+570));//设置精灵位置
	}
	bgSprite->addChild(round1Marksprite,0);//将第一关标记精灵添加到选关标记底板精灵中

	createRound2MarkSp(mark2Idx);//创建第二关标记精灵对象
	round2Marksprite->setScale(1.6);//设置精灵对象缩放比
	if(bgIdx==0)
	{
		round2Marksprite->setPosition(Point(origin.x+320,origin.y+350));//设置精灵位置
	}else if(bgIdx==1)
	{
		round2Marksprite->setPosition(Point(origin.x+200,origin.y+270));//设置精灵位置
	}else if(bgIdx==2)
	{
		round2Marksprite->setPosition(Point(origin.x+350,origin.y+260));//设置精灵位置
	}
	bgSprite->addChild(round2Marksprite,0);//将第二关标记精灵添加到选关标记底板精灵中

	auto backItem = MenuItemImage::create
	(
			pic_PATH+"back.png",
			pic_PATH+"back.png",
			CC_CALLBACK_0(SetLayer::onBack, this)//点击时执行的回调方法
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

	//创建单点触摸监听
	EventListenerTouchOneByOne* guanQia = EventListenerTouchOneByOne::create();
	//设置下传触摸
	guanQia->setSwallowTouches(true);
	//开始触摸时回调enterGame方法
	guanQia->onTouchBegan = CC_CALLBACK_2(SetLayer::enterGame, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(guanQia, round1Marksprite);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(guanQia->clone(), round2Marksprite);

	 if(ChoiceLayer::isMusic==false)
	{
		wl->pauseBgMusic();//暂停播放背景音乐
	}else
	{
		wl->resumeBgMusic();//继续播放背景
	}
	return true;
}
bool SetLayer::enterGame(Touch* touch,Event* event)
{
	//获取的当前触摸的对象，并转化为精灵类型
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	//获取精灵的大小
	auto size = target->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	auto rect = Rect(0, 0, size.width, size.height);
	if(rect.containsPoint(location)&&target==round1Marksprite)
	{
		if(ChoiceLayer::isSound)
		{
			wl->playSwitchSound();//播放切换音效
		}
		switch(bgIdx)
		{
		case 0:
			gsm->gogameScene();
			break;
		case 1:
			gsm->goRound3Scene();
			break;
		case 2:
			gsm->goRound5Scene();
			break;
		}

		return true;
	}else if(rect.containsPoint(location)&&target==round2Marksprite)
	{
		if(ChoiceLayer::isSound)
		{
			wl->playSwitchSound();//播放切换音效
		}
//		gsm->goRound2Scene();
		switch(bgIdx)
		{
		case 0:
			gsm->goRound2Scene();
			break;
		case 1:
			gsm->goRound4Scene();
			break;
		case 2:
			gsm->goRound6Scene();
			break;

		}
		return true;
	}else
	{
		return false;
	}
	return true;
}

void SetLayer::onBack()
{
	if(ChoiceLayer::isSound)
	{
		wl->playSwitchSound();//播放切换音效
	}
	gsm->goLevelScene();
}
