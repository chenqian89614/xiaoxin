#include "WelcomeLayer.h"
#include "AppMacros.h"

USING_NS_CC;

//实现WelcomeLayer类中的init方法，初始化布景
bool WelcomeLayer::init()
{
	//调用父类的初始化
	if(!Layer::init())
	{
		return false;
	}
	//获取可见区域尺寸
	Size s = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	this->addChild(TankSceneManager::getGround(),0);

	//创建图片精灵
	Sprite *picSprite=Sprite::create(PIC_PATH+std::string("decoration.png"));
	//设置图片精灵的位置
	picSprite->setPosition(Point(origin.x+s.width/2,origin.y+320));
	//将图片放大
	picSprite->setScale(1.2);
	//添加进布景
	this->addChild(picSprite,1);

	//加载中
	Sprite *loadSprite=Sprite::create(PIC_PATH+std::string("load.png"));
	loadSprite->setPosition(Point(origin.x+s.width/2,origin.y+70));
	loadSprite->setScale(1.2);
	this->addChild(loadSprite,2);

	//设置单独动画
	ActionInterval *in=FadeIn::create(0.8f);
	ActionInterval *out=FadeOut::create(0.8f);
	//设置系列动画
	ActionInterval *fade=Repeat::create(Sequence::create(in,out,NULL),2);
	//设置重复动画
	ActionInterval *loadAction=Sequence::create
			(fade,
			CallFunc::create(this,callfunc_selector(WelcomeLayer::toMenuLayer)),
			NULL);
	//给精灵设置动画
	loadSprite->runAction(loadAction);

	return true;
}

void WelcomeLayer::toMenuLayer()
{
	tsm->toMenuLayer();
}
