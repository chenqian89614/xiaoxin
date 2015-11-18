#include "AboutLayer.h"
#include "AppMacros.h"
#include "cocos2d.h"
#include <string>

using namespace cocos2d;

bool AboutLayer::init()
{
	//���ø���ĳ�ʼ��
    if ( !Layer::init() )
    {
        return false;
    }

	//���ı���
	Sprite *background = Sprite::create(PIC_PATH+std::string("background.png"));
	background->setPosition(Point(480,270));
	this->addChild(background,0);
	//�˵�����
	Sprite *aboutGame = Sprite::create(PIC_PATH+std::string("aboutGame.png"));
	aboutGame->setPosition(Point(480,270));
	this->addChild(aboutGame,1);

	MenuItemImage* backItem = MenuItemImage::create(
		PIC_PATH+std::string("choose_game_exit_btn.png"),
		PIC_PATH+std::string("choose_game_exit_btn.png"),
		 CC_CALLBACK_1(AboutLayer::menuReturnCallback, this) //���ʱִ�еĻص�����

	);
	backItem->setPosition(Point(60,485));
	auto backMenu = Menu::create(backItem,NULL);
	//���ò˵�λ��
	backMenu->setPosition(Point::ZERO);
	this->addChild(backMenu,3);

	return true;
}
//����
void AboutLayer::menuReturnCallback(Ref* sende)
{
	psm->goWelcome();
}
