#include "AppDelegate.h"
#include "AchieveLayer.h"
#include "AppMacros.h"

#define pic_PRE_PATH_AchieveLayer string("")

using namespace cocos2d;

//ʵ��AchieveLayer���е�init��������ʼ������
bool AchieveLayer::init()
{
    //���ø���ĳ�ʼ��
    if ( !Layer::init() )
    {
        return false;
    }
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_button_press.mp3"
	);

    //��ȡ�ɼ�����ߴ�
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    //��ȡ�ɼ�����ԭ������
    Point origin = Director::sharedDirector()->getVisibleOrigin();

    //����һ��������󣬳䵱��ӭ����ı���
    backSprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("background.png"));
    //���þ�������λ��
    backSprite->setPosition(Point(400,240));
    //������������ӵ�������
    this->addChild(backSprite,BACKGROUND_LEVEL_CGQ);

    //����һ��������󣬡����а�
    Sprite *playSprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paihang.png"));
	//���þ�������λ��
    playSprite->setPosition(Point(260,290));
	//������������ӵ�������
	this->addChild(playSprite,BACKGROUND_LEVEL_CGQ);

    //����һ����ʾ�佱̨�ľ������
    Sprite *paihangSprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paihang1.png"));
	//���þ�������λ��
    paihangSprite->setPosition(Point(260,110));
	//������������ӵ�������
	this->addChild(paihangSprite,BACKGROUND_LEVEL_CGQ);

    //����һ��������󣬡���߷�����
    Sprite *paih1Sprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paih1.png"));
	//���þ�������λ��
    paih1Sprite->setPosition(Point(360,110));
	//������������ӵ�������
	this->addChild(paih1Sprite,BACKGROUND_LEVEL_CGQ);

    //����һ��������󣬡���߷�����
	Sprite *paih2Sprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paih2.png"));
	//���þ�������λ��
	paih2Sprite->setPosition(Point(500,110));
	//������������ӵ�������
	this->addChild(paih2Sprite,BACKGROUND_LEVEL_CGQ);

    //����һ��������󣬡���߷�����
	Sprite *paih3Sprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paih3.png"));
	//���þ�������λ��
	paih3Sprite->setPosition(Point(640,110));
	//������������ӵ�������
	this->addChild(paih3Sprite,BACKGROUND_LEVEL_CGQ);

	//�������а�--�Ʒְ�
	//������ʱ����
	int *tempScore = new int[3];

	readScore();
	//��ȡ������--����ӡ������
	for(int i = 0; i<3; i++)
	{
		string score;//��¼������-���ķ���
		tempScore[i] = atoi(glareScore[i].c_str());
		//�ж�
		if(tempScore[i] == 0)
		{
			score = "0";
		}else
		{
			score = glareScore[i];
		}
		//����
		labels = Label::createWithTTF (score, "Marker Felt.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		labels->setRotation(-90);
		labels->setColor(Color3B(255,255,255));
		backSprite->addChild(labels);
		labels->setPosition(Point(355+140*i, 290));
	}

	MenuItemImage *fanhuiItem = MenuItemImage::create(
        pic_PRE_PATH_AchieveLayer+string("fanhui.png"),("fanhui.png"),
		CC_CALLBACK_1(AchieveLayer::menuCallBack, this)
	);
	fanhuiItem->setPosition(Point(740,420));
	pMenu = Menu::create(fanhuiItem,NULL);
	pMenu->setPosition(Point(0,0));
	this->addChild(pMenu,GAME_LEVEL_CGQ+1);

	return true;
}

void AchieveLayer::menuCallBack(Object* pSende)
{
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	//����������
	man->toBeginLayer();
}
//��¼����
void AchieveLayer::saveScore(int newScore)
{
	//��¼newScore����
	string score;
	//֮ǰ�ķ���
	string oldScore;
	//��ȡԭ���ķ���--5��
	int *tempScore = new int[3];
	//��ȡ����
	readScore();
	//��ȡ������
	for(int i=0; i<3; i++)
	{
		tempScore[i] = atoi(glareScore[i].c_str());//�ַ���ת��Ϊ����
	}

	for(int i=2; i>=0; i--)
	{
		if(newScore>=tempScore[i])
		{
			score = StringUtils::format("%d", newScore);//ת��Ϊ�ַ���
			if(i!=2)
			{
				oldScore = StringUtils::format("%d", tempScore[i]);
				UserDefault::getInstance()->setStringForKey(StringUtils::format("%d", (i+1)).c_str(), oldScore);
			}
			UserDefault::getInstance()->setStringForKey(StringUtils::format("%d", i).c_str(), score);
		}else
		{
			break;
		}
	}
	//ˢ��
	UserDefault::getInstance()->flush();
}
//��ȡ����
void AchieveLayer::readScore()
{
	for(int i=0; i<3; i++)
	{
		glareScore[i] = UserDefault::getInstance()->getStringForKey(StringUtils::format("%d", i).c_str(), "0");
	}
}

