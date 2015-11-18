#include "WelcomeLayer.h"
#include "AppMacros.h"

USING_NS_CC;

//ʵ��WelcomeLayer���е�init��������ʼ������
bool WelcomeLayer::init()
{
	//���ø���ĳ�ʼ��
	if(!Layer::init())
	{
		return false;
	}
	//��ȡ�ɼ�����ߴ�
	Size s = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Point origin = Director::getInstance()->getVisibleOrigin();

	//��ӱ���
	this->addChild(TankSceneManager::getGround(),0);

	//����ͼƬ����
	Sprite *picSprite=Sprite::create(PIC_PATH+std::string("decoration.png"));
	//����ͼƬ�����λ��
	picSprite->setPosition(Point(origin.x+s.width/2,origin.y+320));
	//��ͼƬ�Ŵ�
	picSprite->setScale(1.2);
	//��ӽ�����
	this->addChild(picSprite,1);

	//������
	Sprite *loadSprite=Sprite::create(PIC_PATH+std::string("load.png"));
	loadSprite->setPosition(Point(origin.x+s.width/2,origin.y+70));
	loadSprite->setScale(1.2);
	this->addChild(loadSprite,2);

	//���õ�������
	ActionInterval *in=FadeIn::create(0.8f);
	ActionInterval *out=FadeOut::create(0.8f);
	//����ϵ�ж���
	ActionInterval *fade=Repeat::create(Sequence::create(in,out,NULL),2);
	//�����ظ�����
	ActionInterval *loadAction=Sequence::create
			(fade,
			CallFunc::create(this,callfunc_selector(WelcomeLayer::toMenuLayer)),
			NULL);
	//���������ö���
	loadSprite->runAction(loadAction);

	return true;
}

void WelcomeLayer::toMenuLayer()
{
	tsm->toMenuLayer();
}
