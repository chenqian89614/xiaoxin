#include "ChoiceLayer.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
#include "MusicFlag.h"
#include "AppConstant.h"
using namespace std;

bool ChoiceLayer::isMusic=true;
bool ChoiceLayer::isSound=true;
int ChoiceLayer::escChoiceCount=0;
ChoiceLayer::~ChoiceLayer()
{

}

//ʵ�����е�init��������ʼ������
bool ChoiceLayer::init()
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

    //����һ��������󣬰���bg.pngͼƬ
    bgSprite = Sprite::create(pic_PATH+"bg.jpg");
    //���þ�������λ��
    bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //��������ӵ�������
    this->addChild(bgSprite, 0);

    dibanSprite = Sprite::create(shezhiPic_PATH+"diban.png");//����һ��������󣬳䵱�װ�
    dibanSprite->setScale(1.2);
    //���õװ徫��λ��
    dibanSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(dibanSprite,0);//���װ徫����ӵ�������

    isMusic=loadMusicFlag();
	isSound=loadSoundFlag();

    //�������ֿ���ť����
    if(isMusic)
    {
    	music = Sprite::create(shezhiPic_PATH+"musicOn.png");
    }else
    {
    	music = Sprite::create(shezhiPic_PATH+"musicOff.png");
    }

	//���þ���λ��
    music->setPosition(Point( origin.x+200, origin.y+245));
    dibanSprite->addChild(music,0);//�����־�����ӵ��װ徫����
    //������������ť����
    if(isSound)
    {
    	sound = Sprite::create(shezhiPic_PATH+"soundOn.png");
    }else
    {
    	sound = Sprite::create(shezhiPic_PATH+"soundOff.png");
    }

	//���þ���λ��
	sound->setPosition(Point( origin.x+200, origin.y+105));
	dibanSprite->addChild(sound,0);//������������ӵ��װ徫����

	auto backItem = MenuItemImage::create
	(
			pic_PATH+"back.png",
			pic_PATH+"back.png",
			CC_CALLBACK_0(ChoiceLayer::onBack, this)//���ʱִ�еĻص�����
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

	//�������㴥������
	EventListenerTouchOneByOne* listenerMusic = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerMusic->setSwallowTouches(true);
	//��ʼ����ʱ�ص�controlMusic����
	listenerMusic->onTouchBegan = CC_CALLBACK_2(ChoiceLayer::controlMusic, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMusic, music);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMusic->clone(), sound);

    return true;
}

bool ChoiceLayer::controlMusic(Touch* touch,Event* event)
{
	//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//��ȡ��ǰ����
	auto location = target->convertToNodeSpace(touch->getLocation());
	//��ȡ����Ĵ�С
	auto size = target->getContentSize();
	//����һ�����ζ������С�뾫����ͬ
	auto rect = Rect(0, 0, size.width, size.height);
	if(rect.containsPoint(location)&&target==music)
	{
		if(isMusic)
		{
			if(isSound)
			{
				wl->playClickSound();//���ŵ������
			}
			wl->pauseBgMusic();//��ͣ���ű�������
			music->setTexture(shezhiPic_PATH+"musicOff.png");
			isMusic=false;

			UserDefault::getInstance()->setBoolForKey("bool1",false);	//�洢�Ƿ�����������
			UserDefault::getInstance()->flush();								//��ʵд��

		}else
		{
			if(isSound)
			{
				wl->playClickSound();//���ŵ������
			}
//			wl->resumeBgMusic();//�������ű�������
			wl->playBgMusic();//���ű�������
			music->setTexture(shezhiPic_PATH+"musicOn.png");
			isMusic=true;

			UserDefault::getInstance()->setBoolForKey("bool1",true);	//�洢�Ƿ�����������
			UserDefault::getInstance()->flush();								//��ʵд��
		}
		return true;
	}else if(target==sound&&rect.containsPoint(location))
	{
		if(isSound)
		{
			wl->pauseSound();//��ͣ������Ч
			wl->playClickSound();//���ŵ������
			sound->setTexture(shezhiPic_PATH+"soundOff.png");
			isSound=false;

			UserDefault::getInstance()->setBoolForKey("bool2",false);//�洢�Ƿ���������Ч
			UserDefault::getInstance()->flush();								//��ʵд��

		}else
		{
			wl->resumeSound();//����������Ч
			sound->setTexture(shezhiPic_PATH+"soundOn.png");
			isSound=true;

			UserDefault::getInstance()->setBoolForKey("bool2",true);//�洢�Ƿ���������Ч
			UserDefault::getInstance()->flush();								//��ʵд��
		}
		return true;
	}else{
		return false;
	}

	return true;
}

void ChoiceLayer::onBack()
{
	if(isSound)
	{
		wl->playSwitchSound();//�����л���Ч
	}
	++escChoiceCount;
	gsm->goWelcomeScene();
}
