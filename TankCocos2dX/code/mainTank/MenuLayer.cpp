#include "MenuLayer.h"
#include "Constant.h"
#include "AppMacros.h"

USING_NS_CC;

bool MenuLayer::init()
{
	//调用父类的初始化
	if(!Layer::init())
	{
		return false;
	}
	//添加背景
	this->addChild(TankSceneManager::getGround(),0);
	initTitle(this);
	initMenu();
	init3D();
	//设置定时回调指定方法干活
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//定时回调update的方法
	sched->schedule(SEL_SCHEDULE(&MenuLayer::update), this, 0.1, false);
	return true;
}

void MenuLayer::init3D()
{
	//获取可见区域尺寸
	Size s = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->removeChildByTag(2);
	sp3=Sprite3D::create(OBJ_PATH+std::string("3DTank.obj"),OBJ_PATH+std::string("3DTank.png"));
	sp3->setScale(0.075);
	sp3->setPosition(Point(origin.x+s.width/3+30,origin.y+130));
	this->addChild(sp3, 5);
}

void MenuLayer::update()
{
	degree+=2;
	sp3->setRotation3D(Vertex3F(0, -degree, 0));
}

void MenuLayer::initTitle(Layer *layer)
{
	//获取可见区域尺寸
	Size s = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();

	//title精灵
	Sprite *titleSprite=Sprite::create(PIC_PATH+std::string("title.png"));
	titleSprite->setPosition(Point(origin.x+s.width/3+20,origin.y+450));
	titleSprite->setScale(1.2);
	layer->addChild(titleSprite,1);

	//概览图精灵
	Sprite *picSprite=Sprite::create(PIC_PATH+std::string("decoration.png"));
	picSprite->setPosition(Point(origin.x+s.width/3+20,origin.y+200));
	picSprite->setScale(1.2);
	layer->addChild(picSprite,2,2);
}

void MenuLayer::initMenu()
{
	//创建菜单项
	MenuItemImage* startItem = MenuItemImage::create
	(
			PIC_PATH+std::string("start_game.png"),
			PIC_PATH+std::string("start_game_select.png"),
			CC_CALLBACK_0(MenuLayer::gameStart,this)
	);
	startItem->setPosition(Point(780,380));
	MenuItemImage* helpItem = MenuItemImage::create
	(
			PIC_PATH+std::string("help.png"),
			PIC_PATH+std::string("help_select.png"),
			CC_CALLBACK_0(MenuLayer::gameHelp,this)
	);
	helpItem->setPosition(Point(780,300));
	MenuItemImage* soundItem = MenuItemImage::create
	(
			PIC_PATH+std::string("soundset.png"),
			PIC_PATH+std::string("soundset_select.png"),
			CC_CALLBACK_0(MenuLayer::setSound,this)
	);
	soundItem->setPosition(Point(780,220));
	MenuItemImage* exitItem = MenuItemImage::create
	(
			PIC_PATH+std::string("exit_game.png"),
			PIC_PATH+std::string("exit_game_select.png"),
			CC_CALLBACK_0(MenuLayer::gameExit,this)
	);
	exitItem->setPosition(Point(780,140));
	//设置菜单位置

	//创建菜单容器
	Menu* menu = Menu::create(startItem,helpItem,soundItem,exitItem,NULL);
	//设置惨淡原点位置
	menu->setPosition(Point::ZERO);

	this->addChild(menu,4);
}

void MenuLayer::gameStart()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	tsm->toSelectLayer();
}
void MenuLayer::gameHelp()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	tsm->toHelpLayer();
}
void MenuLayer::setSound()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	tsm->toSoundsetLayer();
}
void MenuLayer::gameExit()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}
