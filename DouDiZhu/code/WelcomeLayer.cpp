#include "WelcomeLayer.h"
#include "GameLayer.h"
#include "AppMacros.h"
#include "BNSocketUtil.h"
#include "Constant.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <string>


//USING_NS_CC;
using namespace cocos2d;
using namespace std;

bool WelcomeLayer::init()
{
	//���ø���ĳ�ʼ��
    if ( !Layer::init() )
    {
        return false;
    }

    addMenu();
    //����һ��������󣬰���background.pngͼƬ
    Sprite  *background = Sprite::create(PIC_PATH+std::string("background.png"));
    background->setPosition(Point(480,270));
    //��������ӵ�������
    this->addChild(background, BACKGROUD_LEVEL);
    
    startImage=Sprite::create(PIC_PATH+std::string("start_disable_btn.png"));
    startImage->setPosition(Point(750,400));
    this->addChild(startImage,PROP_LEVEL);
    startImage->setVisible(false);

    Sprite  *logo = Sprite::create(PIC_PATH+std::string("logo.png"));
    logo->setPosition(Point(260,270));
    this->addChild(logo, PROP_LEVEL);

    //��ʾ������Ϣ�ı�ǩ
    msgLabel=LabelTTF::create("Msg:", "Arial", 40);
    //���ñ�ǩ�������ɫ
    msgLabel->setFontFillColor(Color3B::YELLOW);
    msgLabel->setPosition(Vec2(750,400));
    this->addChild(msgLabel, PROP_LEVEL+1);
    BNSocketUtil::msgLabel=msgLabel;
    msgLabel->setVisible(false);

    if(Constant::musicFlag)
    {
        backMusic();
    }
   
    
     return true;
}

//��Ӳ˵���
void WelcomeLayer::addMenu()
{
	//startGame
	MenuItemImage *startItem = MenuItemImage::create
	(
		PIC_PATH+std::string("start_blue_btn.png"),
		PIC_PATH+std::string("start_blue_btn_down.png"),
		PIC_PATH+std::string("start_disable_btn.png"),
	   CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this)
	);
	//setDisabledSpriteFrame(startItem);
	//���ùرղ˵����λ��
	startItem->setPosition(Point(750,400));
	//�����˵�����
	startMenu = Menu::create(startItem, NULL);
	//���ò˵�λ��
	startMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(startMenu,BTN_LEVEL);

	//help
	MenuItemImage *helpItem = MenuItemImage::create
	(
			PIC_PATH+std::string("start_green_btn.png"),
			PIC_PATH+std::string("start_green_btn_down.png"),
		   CC_CALLBACK_1(WelcomeLayer::menuHelpCallback, this)
	);
	//���ùرղ˵����λ��
	helpItem->setPosition(Point(750,280));
	//�����˵�����
	Menu *helpMenu = Menu::create(helpItem, NULL);
	//���ò˵�λ��
	helpMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(helpMenu,BTN_LEVEL);

	//about
	MenuItemImage *aboutItem = MenuItemImage::create
	(
			PIC_PATH+std::string("start_red_btn.png"),
			PIC_PATH+std::string("start_red_btn_down.png"),
		   CC_CALLBACK_1(WelcomeLayer::menuAboutCallback, this)
	);
	//���ùرղ˵����λ��
	aboutItem->setPosition(Point(750,160));
	//�����˵�����
	Menu *aboutMenu = Menu::create(aboutItem, NULL);
	//���ò˵�λ��
	aboutMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(aboutMenu,BTN_LEVEL);

	//exitGame
	MenuItemImage *exitItem = MenuItemImage::create
	(
			PIC_PATH+std::string("choose_game_exit_btn.png"),
			PIC_PATH+std::string("choose_game_exit_btn.png"),
		   CC_CALLBACK_1(WelcomeLayer::menuExitCallback, this)
	);
	//���ùرղ˵����λ��
	exitItem->setPosition(Point(60,485));
	//�����˵�����
	Menu *exitMenu = Menu::create(exitItem, NULL);
	//���ò˵�λ��
	exitMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(exitMenu,BTN_LEVEL);
}
//��������
void WelcomeLayer::backMusic()
{
	//���ر�������
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic
	(
		(SOUND_PATH+string("MusicEx_Welcome.mp3")).c_str()
	);
	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		(SOUND_PATH+string("MusicEx_Welcome.mp3")).c_str(),
		true
	);
}
void WelcomeLayer::menuStartCallback(Ref* sender)
{
	/*
	 * ��ҵ����ʼ��Ϸ����Ϸ���ӷ����������߷�������������ѽ�����Ϸ����
	 */
	if(!BNSocketUtil::connectFlag)
	{
		//���ӷ�����IP fs
		BNSocketUtil::connect("192.168.253.1",9999);
	}
	removeChild(startMenu);
	startImage->setVisible(true);
	msgLabel->setVisible(true);
	//���ö�ʱ�ص�
	schedule(schedule_selector(WelcomeLayer::jinruGame), 0.5);
}
void WelcomeLayer::gotoGame()
{

	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	psm->goGame();
}
void WelcomeLayer::jinruGame(float ft)
{
	//�����ӵ������������л����沢ֹͣ����
	if(BNSocketUtil::connectFlag)
	{
		this->unschedule(SEL_SCHEDULE(&WelcomeLayer::jinruGame));
		MenuItemImage *gotoGame=MenuItemImage::create(
				PIC_PATH+std::string("go_game_btn.png"),
				PIC_PATH+std::string("go_game_btn_down.png"),
			CC_CALLBACK_0(WelcomeLayer::gotoGame,this)
			);
			gotoGame->setPosition(Point(750,400));

			Menu *gotoGameMenu=Menu::create(gotoGame,NULL);

			gotoGameMenu->setPosition(Point::ZERO);
			this->addChild(gotoGameMenu,BTN_LEVEL);

			startImage->setVisible(false);
			msgLabel->setVisible(false);
	}
}
//��Ϸ����
void WelcomeLayer::menuHelpCallback(Ref* sender)
{
	psm->goHelp();
}
//��Ϸ����
void WelcomeLayer::menuAboutCallback(Ref* sender)
{
	psm->goAbout();
}
//�˳���Ϸ
void WelcomeLayer::menuExitCallback(Ref* sender)
{
	Director::getInstance()->end();
}
