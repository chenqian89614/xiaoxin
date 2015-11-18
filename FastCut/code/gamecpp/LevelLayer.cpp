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
	//���ø���ĳ�ʼ��
	if ( !Layer::init() )
	{
		return false;
	}
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Point origin = Director::getInstance()->getVisibleOrigin();
	bgSprite=Sprite::create(levelSetPic_PATH+"level_bg.jpg");//���������������
	//���ñ�������λ��
	bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bgSprite,0);

	auto set1Item = MenuItemImage::create
	(
			levelSetPic_PATH+"set1_a.png",	//ƽʱ��ͼƬ
			levelSetPic_PATH+"set1_b.png",	//ѡ��ʱ��ͼƬ
		   CC_CALLBACK_1(LevelLayer::set1, this) //���ʱִ�еĻص�����
	);
	//����ϵ��1�˵����λ��
	set1Item->setPosition
	(
		Point
		(
			origin.x + 210,//X����210
			origin.y + 700	//Y����
		)
	);

	//�����˵�����
	menu1 = Menu::create(set1Item, NULL);
	//���ò˵�λ��
	menu1->setPosition(Point::ZERO);

//	menu1->runAction(Sequence::create(//ִ�ж���
//			MoveBy::create(0.2,Point(1000,0)),
//			MoveTo::create(0.2,Point::ZERO),
//			NULL
//	));
	//���˵���ӵ�������
	this->addChild(menu1, 1);

	auto set2Item = MenuItemImage::create
	(
			levelSetPic_PATH+"set2_a.png",	//ƽʱ��ͼƬ
			levelSetPic_PATH+"set2_b.png",	//ѡ��ʱ��ͼƬ
		   CC_CALLBACK_1(LevelLayer::set2, this) //���ʱִ�еĻص�����
	);
	//����ϵ��2�˵����λ��
	set2Item->setPosition
	(
		Point
		(
			origin.x + 300,//X����300
			origin.y + 450	//Y����
		)
	);

	//�����˵�����
	menu2 = Menu::create(set2Item, NULL);
	//���ò˵�λ��
	menu2->setPosition(Point::ZERO);

//	menu2->runAction(Sequence::create(
//			MoveBy::create(0.2,Point(-1000,0)),
//			MoveTo::create(0.2,Point::ZERO),
//			NULL
//	));

	//���˵���ӵ�������
	this->addChild(menu2, 1);

	auto set3Item = MenuItemImage::create
	(
			levelSetPic_PATH+"set3_a.png",	//ƽʱ��ͼƬ
			levelSetPic_PATH+"set3_b.png",	//ѡ��ʱ��ͼƬ
		   CC_CALLBACK_1(LevelLayer::set3, this) //���ʱִ�еĻص�����
	);
	//����ϵ��3�˵����λ��
	set3Item->setPosition
	(
		Point
		(
			origin.x + 210,//X����210
			origin.y + 200	//Y����
		)
	);

	//�����˵�����
	menu3 = Menu::create(set3Item, NULL);

//	menu3->runAction(Sequence::create(
//			MoveBy::create(0.2,Point(1000,0)),
//			MoveTo::create(0.2,Point::ZERO),
//			NULL
//	));
	//���ò˵�λ��
	menu3->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(menu3, 1);

	auto backItem = MenuItemImage::create
	(
			pic_PATH+"back.png",
			pic_PATH+"back.png",
			CC_CALLBACK_0(LevelLayer::onBack, this)//���ʱִ�еĻص�����
	);
	backItem->setPosition(
			Point(
				origin.x - backItem->getContentSize().width/2+520,	//X����
				origin.y -backItem->getContentSize().height/2+940		//Y����
			)
			);
	//�����˵�����
	auto backMenu = Menu::create(backItem, NULL);
	//���ò˵�λ��
	backMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(backMenu, 1);

//	ParticleSystemQuad*  psq = ParticleFlower::create();		//������������ϵͳЧ��
//	psq->retain();										//��������
//	psq->setTexture( Director::getInstance()->getTextureCache()->addImage(levelSetPic_PATH+"stars.png") );	//Ϊ����ϵͳ����ͼƬ
//	psq->setPosition( Point(270, 850) );						//��������ϵͳ��λ��
//	bgSprite->addChild(psq, 0);								//������ϵͳ��ӵ�������

	ParticleSystemQuad* psq = ParticleSnow::create();			//������ѩ����ϵͳЧ��
	psq->retain();										//��������
	psq->setTexture( Director::getInstance()->getTextureCache()->addImage(levelSetPic_PATH+"snow.png") );	//Ϊ����ϵͳ����ͼƬ
	psq->setPosition( Point(270, 960) );						//��������ϵͳ������
	psq->setLife(3);										//��������ϵͳ������ֵ
	psq->setLifeVar(1);   								//��������ϵͳ�������仯ֵ
	psq->setGravity(Point(0,-10));							//��������ϵͳ����������
	psq->setSpeed(130);									//��������ϵͳ���ٶ�ֵ
	psq->setSpeedVar(30);    							//��������ϵͳ���ٶȱ仯ֵ
	psq->setStartColor((Color4F){0.9,0.9,0.9,1});				//��������ϵͳ�Ŀ�ʼ��ɫֵ
	psq->setStartColorVar((Color4F){0,0,0.1,1});				//��������ϵͳ�Ŀ�ʼ��ɫ�仯ֵ
	psq->setEmissionRate(psq->getTotalParticles()/psq->getLife());	//��������ϵͳ�ķ�������
	this->addChild(psq, 0);								//������ϵͳ��ӵ�������

//	ParticleSystemQuad*  psq = ParticleGalaxy::create();		//������ϵ����ϵͳЧ��
//	psq->retain();										//��������
//	psq->setTexture( Director::getInstance()->getTextureCache()->addImage(levelSetPic_PATH+"fire.png") );	//Ϊ����ϵͳ����ͼƬ
//	psq->setPosition( Point(270, 300) );						//��������ϵͳ��λ��
//	this->addChild(psq, 0);								//������ϵͳ��ӵ�������

//	ParticleSystemQuad*  psq = ParticleFire ::create();		//�����������ϵͳЧ��ParticleFireworks
//	psq->retain();										//��������
//	psq->setTexture( Director::getInstance()->
//				getTextureCache()->addImage(levelSetPic_PATH+"fire.png") );	//Ϊ����ϵͳ����ͼƬ
//	psq->setPosition( Point(270, 360) );						//��������ϵͳ��λ��
//	this->addChild(psq, 0);								//������ϵͳ��ӵ�������

//	//������ʱ�ص�*************************************
//	auto director = Director::getInstance();
//	auto sched = director->getScheduler();
//	sched->scheduleSelector(SEL_SCHEDULE(&LevelLayer::update),this,0.7f,false);
//	//***********************************************
    if(ChoiceLayer::isMusic==false)
	{
		wl->pauseBgMusic();//��ͣ���ű�������
	}else
	{
		wl->resumeBgMusic();//�������ű���
	}
	return true;
}

void LevelLayer::set1(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();//ֹͣ������Ч
	}else
	{
		wl->playSwitchSound();//�����л�����Ч
		wl->playClickSound();//���ŵ������Ч
	}
//	gsm->goSet1Scene();//ȥϵ��1����
	SetLayer::bgIdx=0;
	SetLayer::mark1Idx=0;
	SetLayer::mark2Idx=0;
	gsm->goSetScene();//ȥϵ�г���
}

void LevelLayer::set2(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();//ֹͣ������Ч
	}else
	{
		wl->playSwitchSound();//�����л�����Ч
		wl->playClickSound();//���ŵ������Ч
	}
//	gsm->goSet2Scene();//ȥϵ��2����
	SetLayer::bgIdx=1;
	SetLayer::mark1Idx=1;
	SetLayer::mark2Idx=1;
	gsm->goSetScene();//ȥϵ�г���
}

void LevelLayer::set3(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();//ֹͣ������Ч
	}else
	{
		wl->playSwitchSound();//�����л�����Ч
		wl->playClickSound();//���ŵ������Ч
	}
//	gsm->goSet3Scene();//ȥϵ��3����
	SetLayer::bgIdx=2;
	SetLayer::mark1Idx=2;
	SetLayer::mark2Idx=2;
	gsm->goSetScene();//ȥϵ�г���
}

void LevelLayer::onBack()
{
	if(ChoiceLayer::isSound)
	{
		wl->playSwitchSound();//�����л���Ч
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
