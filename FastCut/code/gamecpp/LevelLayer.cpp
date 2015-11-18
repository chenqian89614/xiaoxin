#include "LevelLayer.h"
#include "SimpleAudioEngine.h"
#include "WelcomeLayer.h"
#include "ChoiceLayer.h"
#include "SetLayer.h"
#include "SetUtil.h"
#include "AppConstant.h"
using namespace std;
using namespace cocos2d;
LevelLayer::~LevelLayer()
{

}

bool LevelLayer::init()
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
	bgSprite=Sprite::create(levelSetPic_PATH+"level_bg.jpg");//创建背景精灵对象
	//设置背景精灵位置
	bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bgSprite,0);

	auto set1Item = MenuItemImage::create
	(
			levelSetPic_PATH+"set1_a.png",	//平时的图片
			levelSetPic_PATH+"set1_b.png",	//选中时的图片
		   CC_CALLBACK_1(LevelLayer::set1, this) //点击时执行的回调方法
	);
	//设置系列1菜单项的位置
	set1Item->setPosition
	(
		Point
		(
			origin.x + 210,//X坐标210
			origin.y + 700	//Y坐标
		)
	);

	//创建菜单对象
	menu1 = Menu::create(set1Item, NULL);
	//设置菜单位置
	menu1->setPosition(Point::ZERO);

//	menu1->runAction(Sequence::create(//执行动作
//			MoveBy::create(0.2,Point(1000,0)),
//			MoveTo::create(0.2,Point::ZERO),
//			NULL
//	));
	//将菜单添加到布景中
	this->addChild(menu1, 1);

	auto set2Item = MenuItemImage::create
	(
			levelSetPic_PATH+"set2_a.png",	//平时的图片
			levelSetPic_PATH+"set2_b.png",	//选中时的图片
		   CC_CALLBACK_1(LevelLayer::set2, this) //点击时执行的回调方法
	);
	//设置系列2菜单项的位置
	set2Item->setPosition
	(
		Point
		(
			origin.x + 300,//X坐标300
			origin.y + 450	//Y坐标
		)
	);

	//创建菜单对象
	menu2 = Menu::create(set2Item, NULL);
	//设置菜单位置
	menu2->setPosition(Point::ZERO);

//	menu2->runAction(Sequence::create(
//			MoveBy::create(0.2,Point(-1000,0)),
//			MoveTo::create(0.2,Point::ZERO),
//			NULL
//	));

	//将菜单添加到布景中
	this->addChild(menu2, 1);

	auto set3Item = MenuItemImage::create
	(
			levelSetPic_PATH+"set3_a.png",	//平时的图片
			levelSetPic_PATH+"set3_b.png",	//选中时的图片
		   CC_CALLBACK_1(LevelLayer::set3, this) //点击时执行的回调方法
	);
	//设置系列3菜单项的位置
	set3Item->setPosition
	(
		Point
		(
			origin.x + 210,//X坐标210
			origin.y + 200	//Y坐标
		)
	);

	//创建菜单对象
	menu3 = Menu::create(set3Item, NULL);

//	menu3->runAction(Sequence::create(
//			MoveBy::create(0.2,Point(1000,0)),
//			MoveTo::create(0.2,Point::ZERO),
//			NULL
//	));
	//设置菜单位置
	menu3->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(menu3, 1);

	auto backItem = MenuItemImage::create
	(
			pic_PATH+"back.png",
			pic_PATH+"back.png",
			CC_CALLBACK_0(LevelLayer::onBack, this)//点击时执行的回调方法
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

//	ParticleSystemQuad*  psq = ParticleFlower::create();		//创建绽放粒子系统效果
//	psq->retain();										//保持引用
//	psq->setTexture( Director::getInstance()->getTextureCache()->addImage(levelSetPic_PATH+"stars.png") );	//为粒子系统设置图片
//	psq->setPosition( Point(270, 850) );						//设置粒子系统的位置
//	bgSprite->addChild(psq, 0);								//将粒子系统添加到精灵中

	ParticleSystemQuad* psq = ParticleSnow::create();			//创建下雪粒子系统效果
	psq->retain();										//保持引用
	psq->setTexture( Director::getInstance()->getTextureCache()->addImage(levelSetPic_PATH+"snow.png") );	//为粒子系统设置图片
	psq->setPosition( Point(270, 960) );						//设置粒子系统的坐标
	psq->setLife(3);										//设置粒子系统的生命值
	psq->setLifeVar(1);   								//设置粒子系统的生命变化值
	psq->setGravity(Point(0,-10));							//设置粒子系统的重力向量
	psq->setSpeed(130);									//设置粒子系统的速度值
	psq->setSpeedVar(30);    							//设置粒子系统的速度变化值
	psq->setStartColor((Color4F){0.9,0.9,0.9,1});				//设置粒子系统的开始颜色值
	psq->setStartColorVar((Color4F){0,0,0.1,1});				//设置粒子系统的开始颜色变化值
	psq->setEmissionRate(psq->getTotalParticles()/psq->getLife());	//设置粒子系统的发射速率
	this->addChild(psq, 0);								//将粒子系统添加到精灵中

//	ParticleSystemQuad*  psq = ParticleGalaxy::create();		//创建星系粒子系统效果
//	psq->retain();										//保持引用
//	psq->setTexture( Director::getInstance()->getTextureCache()->addImage(levelSetPic_PATH+"fire.png") );	//为粒子系统设置图片
//	psq->setPosition( Point(270, 300) );						//设置粒子系统的位置
//	this->addChild(psq, 0);								//将粒子系统添加到精灵中

//	ParticleSystemQuad*  psq = ParticleFire ::create();		//创建焰火粒子系统效果ParticleFireworks
//	psq->retain();										//保持引用
//	psq->setTexture( Director::getInstance()->
//				getTextureCache()->addImage(levelSetPic_PATH+"fire.png") );	//为粒子系统设置图片
//	psq->setPosition( Point(270, 360) );						//设置粒子系统的位置
//	this->addChild(psq, 0);								//将粒子系统添加到精灵中

//	//开启定时回调*************************************
//	auto director = Director::getInstance();
//	auto sched = director->getScheduler();
//	sched->scheduleSelector(SEL_SCHEDULE(&LevelLayer::update),this,0.7f,false);
//	//***********************************************
    if(ChoiceLayer::isMusic==false)
	{
		wl->pauseBgMusic();//暂停播放背景音乐
	}else
	{
		wl->resumeBgMusic();//继续播放背景
	}
	return true;
}

void LevelLayer::set1(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();//停止播放音效
	}else
	{
		wl->playSwitchSound();//播放切换的音效
		wl->playClickSound();//播放点击的音效
	}
//	gsm->goSet1Scene();//去系列1场景
	SetLayer::bgIdx=0;
	SetLayer::mark1Idx=0;
	SetLayer::mark2Idx=0;
	gsm->goSetScene();//去系列场景
}

void LevelLayer::set2(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();//停止播放音效
	}else
	{
		wl->playSwitchSound();//播放切换的音效
		wl->playClickSound();//播放点击的音效
	}
//	gsm->goSet2Scene();//去系列2场景
	SetLayer::bgIdx=1;
	SetLayer::mark1Idx=1;
	SetLayer::mark2Idx=1;
	gsm->goSetScene();//去系列场景
}

void LevelLayer::set3(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();//停止播放音效
	}else
	{
		wl->playSwitchSound();//播放切换的音效
		wl->playClickSound();//播放点击的音效
	}
//	gsm->goSet3Scene();//去系列3场景
	SetLayer::bgIdx=2;
	SetLayer::mark1Idx=2;
	SetLayer::mark2Idx=2;
	gsm->goSetScene();//去系列场景
}

void LevelLayer::onBack()
{
	if(ChoiceLayer::isSound)
	{
		wl->playSwitchSound();//播放切换音效
	}
	gsm->goWelcomeScene();
}

//void LevelLayer::update()
//{
//	if(isScale==false)
//	{
//		menu1->setScale(1.01f);
//		menu2->setScale(0.99f);
//		menu3->setScale(1.01f);
//		isScale=true;
//	}else
//	{
//		menu1->setScale(0.99f);
//		menu2->setScale(1.01f);
//		menu3->setScale(0.99f);
//		isScale=false;
//	}
//}
