#include "DialogLayer.h"
#include "AppMacros.h"
#include "GameSceneManager.h"
#include "GameLayer.h"

//��ʼ��������־λΪtrue
bool DialogLayer::isMusic = true;
//��ʼ������Ч���ı�־λΪtrue
bool DialogLayer::isParticle = true;

using namespace cocos2d;
//��ʼ������
bool DialogLayer::init()
{
	//��ʼ����ʾ��ͣ����ı�־λΪfalse
    bool bRet = false;
    do {
    	//������Ļ��͸����
        CC_BREAK_IF(!LayerColor::initWithColor(ccc4(0, 0, 0, 160),800,480));
        //����initDialog����
        this->initDialog();
        //����־λ��Ϊtrue
        bRet = true;
    }
    //�ж�
    while (0);

    return bRet;
}

void DialogLayer::initDialog()
{
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_button_press.mp3"
	);
	//����һ��������󣬰�����ͣ��Ϸ�������䵱����
    Sprite* plabel = Sprite::create("plabel.png");
    //���þ�������λ��
    plabel->setPosition(Point(105, 240));
    //������������ӵ�������
    this->addChild(plabel, BACKGROUND_LEVEL_CGQ+1);

    //��š���1
	x_1 = Sprite::create("x.png");
	//���þ�������λ��
	x_1->setPosition(Point(400,150));
	if(isParticle)
	{
		x_1->setVisible(false);
	}else{
		x_1->setVisible(true);
	}
	//��X�ž��������ӵ�������
	this->addChild(x_1, DASHBOARD_LEVEL_CGQ+1);

	//��š���2
	x_2 = Sprite::create("x.png");
	//���þ�������λ��
	x_2->setPosition(Point(400,330));
	if(isMusic)
	{
		x_2->setVisible(false);
	}else{
		x_2->setVisible(true);
	}

	//��X�ž��������ӵ�������
	this->addChild(x_2, DASHBOARD_LEVEL_CGQ+1);

	//����������Ϸ�Ĳ˵���ť
    MenuItemImage *resume = MenuItemImage::create
	(
		 "resume.png", 		//ƽʱ��ͼƬ
		 "resume3.png",  	//ѡ��ʱ��ͼƬ
		 //����˵���ťʱִ�еĻص�����
		 CC_CALLBACK_1(DialogLayer::menuCallbackContinueGame,this)
	);
	//���ü�����Ϸ�˵���ť��λ��
    resume->setPosition(Point(250,240));

    //������ʾ����Ч���ľ���
	MenuItemImage *par = MenuItemImage::create
	(
		 "p.png", 	//ƽʱ��ͼƬ
		 "p.png",  	//ѡ��ʱ��ͼƬ
		 //���ʱִ�еĻص�����
		 CC_CALLBACK_0(DialogLayer::parused,this)
	);
	//���ñ�ʾ����Ч���Ĳ˵���ť��λ��
	par->setPosition(Point(400,150));

	//������ʾ�����ľ���
	MenuItemImage *sound = MenuItemImage::create
	(
		 "s.png", 	//ƽʱ��ͼƬ
		 "s.png" , 	//ѡ��ʱ��ͼƬ
		 //���ʱִ�еĻص�����
		 CC_CALLBACK_0(DialogLayer::sounded,this)
	);
	//���������˵���ť��λ��
	sound->setPosition(Point(400,330));

    //���������˵��ľ���
   	MenuItemImage *saveExit = MenuItemImage::create
   	(
   		"exit.png", 	//ƽʱ��ͼƬ
   		"exit3.png",  	//ѡ��ʱ��ͼƬ
   		//���ʱִ�еĻص�����
   		CC_CALLBACK_1(DialogLayer::homeSence,this)
   	);
   	//�����˳��˵���ť��λ��
  	saveExit->setPosition(Point(550,240));

	//�����˵�����
	m_pMenu = Menu::create(resume,saveExit,sound,par, NULL);
	//���ò˵�λ��
	m_pMenu->setPosition(Point(0,0));
	//���˵���ť��ӵ�������
	this->addChild(m_pMenu, DASHBOARD_LEVEL_CGQ);
}

//ȥ���˵������Ļص�����
void DialogLayer::homeSence(Object* pSender)
{
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	//��Ϸ��ͣ�ı�־Ϊ��Ϊfalse
	GameLayer::isPause=false;
	//��sprite����Ļ��ɾ����������ִ�еĶ���Ҳɾ��
	this->removeFromParentAndCleanup(true);
	//��ȡDirector�����ݣ�
	Director* pDirector = Director::getInstance();
	//���л�����������
	pDirector->resume();
	//���л������˵�����
	man->toBeginLayer();
}

//�����Ļص�����
void DialogLayer::sounded()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	isMusic = !isMusic;
	if(isMusic)
	{
		x_2->setVisible(false);
	}else{
		x_2->setVisible(true);
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}

//paused�Ļص�����
void DialogLayer::parused()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	isParticle=!isParticle;
	x_1->setVisible(!isParticle);
}

//������Ϸ�Ļص�����
void DialogLayer::menuCallbackContinueGame(Object *pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	//��Ϸ��ͣ�ı�־λ��Ϊfalse
	GameLayer::isPause=false;
	//��sprite����Ļ��ɾ����������ִ�еĶ���Ҳɾ��
    this->removeFromParentAndCleanup(true);
    //��ȡCCDirector�����ݣ�
	Director* director = Director::getInstance();
	//�л���������Ϸ����
	director->resume();
	//�ж������ı�־λ
	if(isMusic)
	{
		//��������
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

