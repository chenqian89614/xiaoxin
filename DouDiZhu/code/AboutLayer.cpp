#include "AboutLayer.h"
#include "AppMacros.h"
#include "cocos2d.h"
#include <string>

using namespace cocos2d;

bool AboutLayer::init()
{
	//调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }

	//最大的背景
	Sprite *background = Sprite::create(PIC_PATH+std::string("background.png"));
	background->setPosition(Point(480,270));
	this->addChild(background,0);
	//菜单背景
	Sprite *aboutGame = Sprite::create(PIC_PATH+std::string("aboutGame.png"));
	aboutGame->setPosition(Point(480,270));
	this->addChild(aboutGame,1);

	MenuItemImage* backItem = MenuItemImage::create(
		PIC_PATH+std::string("choose_game_exit_btn.png"),
		PIC_PATH+std::string("choose_game_exit_btn.png"),
		 CC_CALLBACK_1(AboutLayer::menuReturnCallback, this) //点击时执行的回调方法

	);
	backItem->setPosition(Point(60,485));
	auto backMenu = Menu::create(backItem,NULL);
	//设置菜单位置
	backMenu->setPosition(Point::ZERO);
	this->addChild(backMenu,3);

	return true;
}
//返回
void AboutLayer::menuReturnCallback(Ref* sende)
{
	psm->goWelcome();
}
