#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"
#include "ChoiceLayer.h"
#include "GameLayer.h"
#include "AppConstant.h"
using namespace std;

//USING_NS_CC;
using namespace cocos2d;
bool WelcomeLayer::playBgM=false;

WelcomeLayer::~WelcomeLayer()
{

}

//ʵ��WelcomeLayer���е�init��������ʼ������
bool WelcomeLayer::init()
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

    //����ѡ��˵���
    auto choiceItem = MenuItemImage::create
    (
    		welcomePic_PATH+"option_button_a.png",	//ƽʱ��ͼƬ
    		welcomePic_PATH+"option_button_b.png",	//ѡ��ʱ��ͼƬ
		    CC_CALLBACK_1(WelcomeLayer::menuChoiceCallback, this) //���ʱִ�еĻص�����
	);
    //����ѡ��˵����λ��
    choiceItem->setPosition
	(
		Point
		(
			origin.x + choiceItem->getContentSize().width/2+20 ,//X����
            origin.y + visibleSize.height - choiceItem->getContentSize().height*2-35//Y����
        )
    );

	//�����˵�����
    auto menu = Menu::create(choiceItem, NULL);
    //���ò˵�λ��
    menu->setPosition(Point::ZERO);
    //���˵���ӵ�������
    this->addChild(menu, 1);
	//������ʼ�˵���
	auto startItem = MenuItemImage::create
	(
			welcomePic_PATH+"play_button_a.png",	//ƽʱ��ͼƬ
			welcomePic_PATH+"play_button_b.png",	//ѡ��ʱ��ͼƬ
		    CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this) //���ʱִ�еĻص�����
	);

	//���ò��Ų˵����λ��
	startItem->setPosition
	(
		Point
		(
			origin.x + visibleSize.width /2 ,	//X����
			origin.y + visibleSize.height/2		//Y����
		)
	);
	//�����˵�����
	auto startMenu = Menu::create(startItem, NULL);
	//���ò˵�λ��
	startMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(startMenu, 2);

    //���������˵���
	auto helpItem = MenuItemImage::create
	(
		welcomePic_PATH+"help_button_a.png",
		welcomePic_PATH+"help_button_b.png",
		CC_CALLBACK_1(WelcomeLayer::menuHelpCallback, this) //���ʱִ�еĻص�����
	);
	helpItem->setPosition(
		Point(
			origin.x + helpItem->getContentSize().width/2+20,	//X����
			origin.y +helpItem->getContentSize().height/2+105		//Y����
		)
	);
	//�����˵�����
	auto helpMenu = Menu::create(helpItem, NULL);
	//���ò˵�λ��
	helpMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(helpMenu, 1);

	auto exitItem = MenuItemImage::create
	(
			welcomePic_PATH+"exit1.png",
			welcomePic_PATH+"exit2.png",
			CC_CALLBACK_1(WelcomeLayer::onExit, this)//���ʱִ�еĻص�����
	);
	exitItem->setPosition(
			Point(
				origin.x + exitItem->getContentSize().width/2+300,	//X����
				origin.y + exitItem->getContentSize().height/2+200		//Y����
			)
			);
	//�����˵�����
	auto exitMenu = Menu::create(exitItem, NULL);
	//���ò˵�λ��
	exitMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(exitMenu, 1);

    //����һ��������󣬰���background.pngͼƬ
    auto bgSprite = Sprite::create(welcomePic_PATH+"bg_01.png");
    //���þ�������λ��
    bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //��������ӵ�������
    this->addChild(bgSprite, 0);

    preloadBgMusic();//���ر�������
    ChoiceLayer::isMusic=UserDefault::getInstance()->getBoolForKey("bool1",true);
    ChoiceLayer::isSound=UserDefault::getInstance()->getBoolForKey("bool2",true);

    if(ChoiceLayer::isMusic==false)
	{
		pauseBgMusic();//��ͣ���ű�������
	}else if(ChoiceLayer::isMusic==true&&playBgM==false)
	{
		playBgMusic();//���ű�������
		playBgM=true;//���������Ѳ��Ź�

	}else if((playBgM==true&&ChoiceLayer::isMusic==true)||(playBgM==true&&ChoiceLayer::isMusic==true))
	{
		resumeBgMusic();//�������ű���
	}


    if(ChoiceLayer::isSound==false)
    {
    	pauseSound();//ֹͣ������Ч
    }
    preloadSwitchSound();//�����л�����Ч
    preloadClickSound();//���ص������Ч

    return true;
}

void WelcomeLayer::menuChoiceCallback(Object* pSender)
{
	if(ChoiceLayer::isSound==false)
	{
		pauseSound();//ֹͣ������Ч
	}else
	{
		playSwitchSound();//�����л�����Ч
		playClickSound();//���ŵ������Ч
	}
	gsm->goChoiceScene();
}

void WelcomeLayer::menuStartCallback(Object* pSender)
{
	if(ChoiceLayer::isSound==false)
	{
		pauseSound();//ֹͣ������Ч
	}else
	{
		playSwitchSound();//�����л�����Ч
		playClickSound();//���ŵ������Ч
	}
	gsm->goLevelScene();

}

void WelcomeLayer::menuHelpCallback(Object* pSender)
{
	if(ChoiceLayer::isSound==false)
	{
		pauseSound();//ֹͣ������Ч
	}else
	{
		playSwitchSound();//�����л�����Ч
		playClickSound();//���ŵ������Ч
	}
	gsm->goHelpScene();
}

void WelcomeLayer::preloadBgMusic()//���ر�������
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
			(sound_PATH+"background.mp3").c_str()					//���ر�������
	);
}
void WelcomeLayer::playBgMusic()//���ű�������
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
			(sound_PATH+"background.mp3").c_str(),				//���ű�������
						true
	);
}
void WelcomeLayer::pauseBgMusic()//��ͣ���ű�������
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();	//��ͣ����
}
void WelcomeLayer::resumeBgMusic()//�������ű�������
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();//��������
}

void WelcomeLayer::preloadSwitchSound()//�����л���Ч
{
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
			(sound_PATH+"switchpane.mp3").c_str()
	);
}
void WelcomeLayer::playSwitchSound()//�����л���Ч
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((sound_PATH+"switchpane.mp3").c_str());
}
void WelcomeLayer::preloadClickSound()//���ص����Ч
{
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
			(sound_PATH+"click.mp3").c_str()
	);
}
void WelcomeLayer::playClickSound()//���ŵ����Ч
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((sound_PATH+"click.mp3").c_str());
}

void WelcomeLayer::pauseSound()//��ͣ������Ч
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();	//��ͣ����
}
void WelcomeLayer::resumeSound()//����������Ч
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();//��������
}

void WelcomeLayer::onExit(Object* pSender)
{
	Director::getInstance()->end();//��Ϸ����
}
