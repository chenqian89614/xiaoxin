#include "BeginLayer.h"
#include "AppDelegate.h"
#include "ChooseLayer.h"

#include "cocos2d.h"

#define pic_PRE_PATH_BeginLayer string("")
using namespace cocos2d;

//ʵ��BeginLayer���е�init��������ʼ������
bool BeginLayer::init()
{
	//���ø���ĳ�ʼ��
    if ( !Layer::init() )
    {
        return false;
    }
    
    //��ȡ�ɼ�����ߴ�
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ�ɼ�����ԭ������
    Point origin = Director::getInstance()->getVisibleOrigin();

    //����һ��������󣬰���background.pngͼƬ
    auto sprite = Sprite::create(pic_PRE_PATH_BeginLayer+string("background.png"));
    //���þ�������λ��
    sprite->setPosition(Point(400,240));
    //��������ӵ�������
    this->addChild(sprite,BACKGROUND_LEVEL_CGQ);
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sound/sf_button_press.mp3"
	);
    
	//��������ʼ��Ϸ������
	MenuItemImage *onePlayer = MenuItemImage::create(
        pic_PRE_PATH_BeginLayer+string("onePlayer.png"),("onePlayer3.png"),
		CC_CALLBACK_1(BeginLayer::oneMode, this)
     );
	//���þ���˵���ť��λ��
	onePlayer->setPosition(Point(270,240));

	//�������˳�������
	MenuItemImage *twoPlayer = MenuItemImage::create(
        pic_PRE_PATH_BeginLayer+string("exit.png"),("exit.png"),
		CC_CALLBACK_1(BeginLayer::twoMode, this)
	);
	//���ò˵���ť��λ��
	twoPlayer->setPosition(Point(660,240));

	//��������߷֡��ľ���
	MenuItemImage *set = MenuItemImage::create(
        pic_PRE_PATH_BeginLayer+string("seclect.png"),("seclect3.png"),
		CC_CALLBACK_1(BeginLayer::setSence, this)
	 );
	//������߷ֲ˵���ť��λ��
	set->setPosition(Point(530,240));

	//����������������
	MenuItemImage *help = MenuItemImage::create(
		pic_PRE_PATH_BeginLayer+string("help.png"),("help33.png"),
		CC_CALLBACK_1(BeginLayer::helpSence, this)
	);
	//���ð����˵���ť��λ��
	help->setPosition(Point(400,240));

	//�������˵��е�4���˵�����
	pMenu = Menu::create(onePlayer,twoPlayer,set,help,NULL);
	//���ò˵���λ��
	pMenu->setPosition(Point(0,0));
	//���˵���ӵ�������
	this->addChild(pMenu,GAME_LEVEL_CGQ);

	return true;
}

void BeginLayer::oneMode(Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sf_button_press.mp3");
	//�л����ؿ�ѡ�����
	man->toChooseLayer();
}
void BeginLayer::twoMode(Object* pSender)
{
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sf_button_press.mp3");
	//�˳���Ϸ
	Director::getInstance()->end();
}
void BeginLayer::setSence(Object* pSender)
{
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sf_button_press.mp3");
	//��߷ֽ���
	man->toAchieveLayer();
}
void BeginLayer::helpSence(Object* pSender)
{
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sf_button_press.mp3");
	//��������
	man->toHelpLayer();
}
