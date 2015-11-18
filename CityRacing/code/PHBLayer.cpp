#include "cocos2d.h"
#include "PHBLayer.h"
#include "Constant.h"

using namespace cocos2d ;

bool PHBLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	bgSpriteO = Sprite::create("scene1.jpg");
	bgSpriteO->setPosition(270,480);
	this->addChild(bgSpriteO,0);

	bgSpriteT = Sprite::create("scene1.jpg");
	bgSpriteT->setPosition(270,-480);
	this->addChild(bgSpriteT,0);

	//创建下一个菜单项
	MenuItemImage* backMenu = MenuItemImage::create(
			   "goback.png",	//平时的图片
			   "gobackp.png",	//选中时的图片
			   CC_CALLBACK_0(PHBLayer::backMenuCallback, this) //点击时执行的回调方法
		);
	//设置下一个菜单项的位置
	backMenu->setPosition(Point(40,920));

	//创建下一个菜单项
	MenuItemImage* resetBt = MenuItemImage::create(
			   "reset.png",	//平时的图片
			   "resetp.png",	//选中时的图片
			   CC_CALLBACK_0(PHBLayer::reSetRecord, this) //点击时执行的回调方法
		);
	//设置下一个菜单项的位置
	resetBt->setPosition(Point(270,100));


	//创建菜单对象
	auto menu = Menu::create(backMenu,resetBt,NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(menu, 1);

	Sprite* rank = Sprite::create("rank.png");
	rank->setPosition(Point(270,750));
	this->addChild(rank,2);

	Sprite* jilu = Sprite::create("jilu.png");
	jilu->setPosition(Point(270,750));
	this->addChild(jilu,3);

	Sprite* backBg = Sprite::create("back.png");
	backBg->setPosition(Point(270,400));
	this->addChild(backBg,2);

	Label* zyjl= Label::createWithTTF("\u884c\u9a76\u6700\u8fdc\u8ddd\u79bb:","FZKATJW.ttf",30);
	zyjl->setPosition(Point(110,540));
	this->addChild(zyjl,2);

	getRecord();
	for(int i=0;i<5;i++)
	{
		noLabel[i] = LabelAtlas::create(						//创建一个LabelAtlas对象
				StringUtils::format("%d..%d",i+1,record[i]),"upNum.png",20,23,'0');
		noLabel[i]->setPosition(Point(180,500-i*50));
		noLabel[i]->setAnchorPoint(Point(0,0.5));
		this->addChild(noLabel[i],2);
	}

	//设置定时回调指定方法干活
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//背景滚屏定时回调
	sched->scheduleSelector(SEL_SCHEDULE(&PHBLayer::bgUpdate),this,0.005,false);

	return true;

}
void PHBLayer::getRecord()
{
	for(int i = 0;i <5;i++)
	{
		record[i] = UserDefault::getInstance()->getIntegerForKey(Constant::userRecord[i].c_str());
	}
}
void PHBLayer::reSetRecord()
{
	for(int i = 0;i <5;i++)
	{
		UserDefault::getInstance()->setIntegerForKey(Constant::userRecord[i].c_str(),0);
		noLabel[i]->setString(StringUtils::format("%d..0",i+1));
	}
}
void PHBLayer::bgUpdate()
{
	if(bgSpriteO->getPosition().y==1440)
	{
		bgSpriteO->setPosition(Point(270,-480));
	}else
	{
		bgSpriteO->setPosition(Point(270,bgSpriteO->getPosition().y+1));
	}
	if(bgSpriteT->getPosition().y==1440)
	{
		bgSpriteT->setPosition(Point(270,-480));
	}else
	{
		bgSpriteT->setPosition(Point(270,bgSpriteT->getPosition().y+1));
	}
}
void PHBLayer::backMenuCallback()
{
	crsm->goStartLyaer();
}
